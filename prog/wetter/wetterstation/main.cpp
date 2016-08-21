#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "BMP180.h"
BMP180 druck;

#include "DHT22.h"
DHT22 dht22(2);

/*
 * Timer Compare Match interrupt handler
 *
 * This handler is used to generate host start conditions (Periods P1 and P2).
 * Using a 8bit timer with prescaler such that a timer tick corresponds to 1us (freq. = 1MHz).
 */
ISR(TIMER_CTC_VECTOR){
	
	/* Using a 8bit timer maximum delay is 255us, we need at least 500us in Period P1.
	   Se, we need two timer interrupts. We check this with overflow_cnt and comparing
	   it the the define OVERFLOWS_HOST_START.
	   We make the pin = 0 at the begining of the state machine (function DHT22_StartReading) */
	if((dht22.state == dht22.DHT_HOST_START) && (dht22.overflow_cnt < (OVERFLOWS_HOST_START - 1))){
		dht22.overflow_cnt++;
	}
	/* After Period P1, we need to hold the pin high for aprox. 40us. So, we change timer compare
	   register to 40. */
	else if((dht22.state == dht22.DHT_HOST_START) && (dht22.overflow_cnt >= (OVERFLOWS_HOST_START - 1))){ // 510us have passed.
		PIN_HIGH(DHT22_PORT,DHT22_PIN); // Change pin to High for period P2.
		dht22.overflow_cnt = 0;
		dht22.state = dht22.DHT_HOST_PULLUP;
		TIMER_OCR_REGISTER = 40;
		return;
	}
	/* The Period P2 have passed. We need now to change the pin to input and wait for sensor
	   to respond. External INT is used. Sensor will respond by pulling the line down for aprox. 
	   80us. So, we can measure period P3 at the next rising edge interrupt. */
	else if (dht22.state == dht22.DHT_HOST_PULLUP){ // more 40us have passed
		TIMER_OCR_REGISTER = 255; // Change timer compare to 255, for now on, the timer interrupt should not fire.
		                          // If if fires, too much time has passed and something is wrong. We will clear
					              // the timer counter at the beggining of the external interrupt handler.
		SET_PIN_INPUT(DHT22_DDR,DHT22_PIN); // Set pin as input.
		PIN_HIGH(DHT22_PORT,DHT22_PIN); // Write 1 to enable pullup.
		EXT_INTERRUPT_DISABLE  // Disable external interrupt (in case it is already enable)
		EXT_INTERRUPT_SET_RISING_EDGE // Setting ext. int to rising edge.
		EXT_INTERRUPT_CLEAR_FLAG // Clear flag to avoid spurious firing of ext. int.
		EXT_INTERRUPT_ENABLE  // Re-enable external int.
		TIMER_COUNTER_REGISTER = 0; // Reset counter
		dht22.state = dht22.DHT_WAIT_SENSOR_RESPONSE; // Change state.
		return; // Return of the int. handler.
	}
	/* If the timer interrupt fired while not in the previous states, than too much time
	   has passed and we signal a error. */
	else{ 
		dht22.state = dht22.DHT_ERROR_NOT_RESPOND; // Change to a error state
		TIMER_STOP // Stop timer.
		EXT_INTERRUPT_DISABLE  // Disable external interrupt
		SET_PIN_OUTPUT(DHT22_DDR,DHT22_PIN); // Set pin back to output.
		PIN_HIGH(DHT22_PORT,DHT22_PIN); // Set pin high to disable DHT22.
		dht22.bitcounter = 0; // reset bit counter.
	}
}

/*
 * External interrupt handler
 * 
 * The external interrupt is used to measure the width of a pulse and change
 * the state accordingly.
 */
ISR(EXT_INTERRUPT_VECTOR){
	
	uint8_t counter_us;
	counter_us = TIMER_COUNTER_REGISTER; // Store counter value
	TIMER_COUNTER_REGISTER = 0; // Reset counter.
	
	/* Period P3. Sensor pulls down the line for aprox. 80us.
	   The ext int. was configured to rising edge. If counter is aprox. 80,
	   (or  < 100 in this case) when the line rises it
	   indicates that the sensor responded.
	   Now we have to change interrupt sense to falling edge in order to
	   detect the period P4.
	 */
	if ((dht22.state == dht22.DHT_WAIT_SENSOR_RESPONSE && (counter_us > 40) && counter_us < 100)){ // Sensor responded (Period P3).
		EXT_INTERRUPT_DISABLE  // Disabling interrupt.
		EXT_INTERRUPT_SET_FALLING_EDGE  // Changing interrupt sense to falling edge.
		EXT_INTERRUPT_CLEAR_FLAG  // clearing flag (this prevents interrupt to fire when changing to falling edge).
		EXT_INTERRUPT_ENABLE  // Re-enabling interrupt.
		dht22.state = dht22.DHT_SENSOR_PULLUP; // Changing state.
		return;
	}
	/* Period P4. When the falling edge interrupt occurs, indicating the end of P4,
	   we get the counter register and check it value. If it is less than 100 (period
	   P4 is also aprox. 80us) then the sensor responded pulling up the line. Now the 
	   bit transmission will start and we only need to measure the with of each bit. So,
	   the external interrupt can stay on falling edge. */
	else if((dht22.state == dht22.DHT_SENSOR_PULLUP) && (counter_us > 60) && (counter_us < 100)){ // Sensor responded (Period P4).
		dht22.state = dht22.DHT_TRANSFERING; // Change state
		return;
	}
	/* Period P5. Measuring the with of the pulse in order to determine if it is a 0 or a 1.
	   Bit 0 has a period of 50us + 28us. So we check if it is larger than 50us and smaller than 110. (DHT22 timing is no precise, neither the timer) */
	else if((dht22.state == dht22.DHT_TRANSFERING) && (counter_us > 50) && (counter_us <= 110)){ // Sensor sent a databit 0 (Period P5).
		// If bit is a 0, only increment the bit counter (we need only to shift 1's).
		dht22.bitcounter++; 
	}
	/* Period P5. Bit 1 has a period of 50us + 70us. So, we check if it is lager than 50us and smaller than 160. */
	else if((dht22.state == dht22.DHT_TRANSFERING) && (counter_us > 110) && (counter_us <= 160)){ // Sensor sent a databit 1 (Period P5).
		/* If bit is one, we shift one to the variables rawHumidity, rawTemperature and checkSum according
		   with bit position givem by bitcounter */
		if (dht22.bitcounter < 16) // Humidity
		{
			dht22.rawHumidity |= (1 << (15 - dht22.bitcounter));
		}
		if ((dht22.bitcounter > 15) && (dht22.bitcounter < 32))  // Temperature
		{
			dht22.rawTemperature |= (1 << (31 - dht22.bitcounter));
		}
		if ((dht22.bitcounter > 31) && (dht22.bitcounter < 40))  // CRC data
		{
			dht22.checkSum |= (1 << (39 - dht22.bitcounter));
		}
		dht22.bitcounter++; // Increments bit counter, the state does not change. 
	}
	
	/* Check if all bits arrived. If so, stop the timer and external interrupt. */
	if (dht22.bitcounter > 39){ // Transfer done
		TIMER_STOP // Stop timer.
		TIMER_COUNTER_REGISTER = 0; // Reset counter.
		EXT_INTERRUPT_DISABLE // Disabling interrupt
		SET_PIN_OUTPUT(DHT22_DDR,DHT22_PIN);
		PIN_HIGH(DHT22_PORT,DHT22_PIN);
		dht22.bitcounter = 0; // Reset bit counter.
		dht22.state = dht22.DHT_CHECK_CRC; // Change state.
	}
	
	/* CRC check is done at outside interrupt handler, by the
	function DHT22_CheckStatus. This way, this handler is very fast. */
				
}
/*
extern "C"{
	#include "DHT22int.c"
}*/

void wait(int number);
void init();
void transmit_values(unsigned char data);
void send_weather();

#define KONTUNUIRLICHER_MODUS 0
uint8_t FLAG_REG;
uint8_t status;

ISR(USART_RX_vect){
	uint8_t temp = UDR0;
	static char status;
	static uint8_t counter;
	if(counter == 0){
		switch (temp)
		{
			case 'c': 
				status = temp;
				counter++;
				break;
			case 'd':
				status = temp;
				counter++;
				break;
			case 'p':
				transmit_values('p');
				transmit_values('\n');
				transmit_values('\r');
				break;
			default:
				break;
		}
	}
	else if(counter == 1 && status == 'c'){
		switch (temp)
		{
			case 'c':
				FLAG_REG |= (1<<KONTUNUIRLICHER_MODUS);
				counter = 0;
				break;
			case 's':
				FLAG_REG &= ~(1<<KONTUNUIRLICHER_MODUS);
				counter = 0;
				break;
			default:
				counter = 0;
				break;
		}
	}
	else if(counter == 1 && status == 'd'){
		switch (temp)
		{
			case 'a':
				if(!(FLAG_REG&(1<<KONTUNUIRLICHER_MODUS))){
					send_weather();
				}
				counter = 0;
				break;
			default:
				counter = 0;
				break;
		}
	}
	else {
		counter = 0;
	}
}

int main(){
	init();
	
	while(true){
		wait(10);
		PORTB |= (1<<PORTB0);
		PORTB &= ~(1<<PORTB1);
		wait(10);
		PORTB |= (1<<PORTB1);
		PORTB &= ~(1<<PORTB0);
		if((FLAG_REG&(1<<KONTUNUIRLICHER_MODUS))){
			send_weather();
		}
		status = dht22.DHT22_StartReading();
	}
	return 0;
}

void wait(int number){
	for(int i=0; i<number;i++){
		_delay_ms(50);
	}
}

void init(){
	//init UASART
	UBRR0H = 0;
	UBRR0L = 51; //9600 BAUD
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	
	//init LED Ports
	DDRB = (1<<DDB0) | (1<<DDB1);
	
	//Init BMP180
	druck.bmp180_getcalibration();
	
	//starte erste Messung des dht22
	dht22.DHT22_StartReading();

	FLAG_REG = 0;
	sei();
}

void transmit_values(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0))){};
	
	UDR0 = data;
}

void send_weather(){
	druck.bmp180_getaltitude();
	status = dht22.DHT22_CheckStatus();
	if(status == dht22.DHT_DATA_READY){
		if(dht22.temperature_integral<0){
			transmit_values('-');
			transmit_values('0'+(-1)*dht22.temperature_integral/10);
		}
		else{
			transmit_values('+');
			transmit_values('0'+dht22.temperature_integral/10);
		}
		transmit_values('0'+dht22.temperature_integral%10);
		transmit_values('.');
		transmit_values('0'+dht22.temperature_decimal);
		transmit_values('\t');
		transmit_values('0'+dht22.humidity_integral/100); 
		transmit_values('0'+dht22.humidity_integral/10); 
		transmit_values('0'+dht22.humidity_integral%10);
		transmit_values('.');
		transmit_values('0'+dht22.humidity_decimal);
		transmit_values('\t');
		transmit_values('0'+(int)druck.pressure/1000);
		transmit_values('0'+(int)druck.pressure%1000/100);
		transmit_values('0'+(int)druck.pressure%100/10);
		transmit_values('0'+(int)druck.pressure%10);
		transmit_values('.');
		transmit_values('0'+(int)(druck.pressure*10.0)%10);
		transmit_values('\t');
		transmit_values('a'+status);
		transmit_values('\n');
		transmit_values('\r');
		dht22.DHT22_StartReading();
	}
}

