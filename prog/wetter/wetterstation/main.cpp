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
	dht22.ISR_TIMER_TOUTINE();
}

/*
 * External interrupt handler
 * 
 * The external interrupt is used to measure the width of a pulse and change
 * the state accordingly.
 */
ISR(EXT_INTERRUPT_VECTOR){
	dht22.ISR_INT_ROUTINE();
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

