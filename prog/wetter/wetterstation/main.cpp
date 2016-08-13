#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "BMP180.h"
BMP180 druck;

extern "C"{
	#include "DHT22int.c"
}

void wait(int number);
void init();
void transmit_values(unsigned char data);
void check_weather();


int main(){
	init();
	
	while(true){
		wait(10);
		PORTB |= (1<<PORTB0);
		PORTB &= ~(1<<PORTB1);
		wait(10);
		PORTB |= (1<<PORTB1);
		PORTB &= ~(1<<PORTB0);
		transmit_values('a');
		transmit_values('\t');
		check_weather();
		transmit_values('\n');
		transmit_values('\r');
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
	UCSR0B = (0<<RXEN0) | (1<<TXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	
	//init dht22
	DHT22_Init();
	DHT22_StartReading();
	
	//init LED Ports
	DDRB = (1<<DDB0) | (1<<DDB1);
	
	//Init BMP180
	druck.bmp180_getcalibration();

	sei();
}

void transmit_values(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0))){};
	
	UDR0 = data;
}

void check_weather(){
	DHT22_STATE_t status;
	DHT22_DATA_t sensor_data;
	status = DHT22_CheckStatus(&sensor_data);
 
	if (status == DHT_DATA_READY){
		druck.bmp180_getaltitude();
		// Do something with the data.
		if(sensor_data.temperature_integral<0){
			transmit_values('-');
			transmit_values('0'+(-1)*sensor_data.temperature_integral/10);
		}
		else{
			transmit_values('0'+sensor_data.temperature_integral/10);
		}
		transmit_values('0'+sensor_data.temperature_integral%10);
		transmit_values('.');
		transmit_values('0'+sensor_data.temperature_decimal);
		transmit_values('\t');
		uint8_t hum = sensor_data.humidity_integral+15; //kompensiere den Drift
		transmit_values('0'+hum/10); 
		transmit_values('0'+hum%10);
		transmit_values('.');
		transmit_values('0'+sensor_data.humidity_decimal);
		transmit_values('\t');
		DHT22_StartReading();
		transmit_values('0'+(int)druck.pressure/1000);
		transmit_values('0'+(int)druck.pressure%1000/100);
		transmit_values('0'+(int)druck.pressure%100/10);
		transmit_values('0'+(int)druck.pressure%10);
		transmit_values('.');
		transmit_values('0'+(int)(druck.pressure*10.0)%10);
		/*
		char buffer[20];
		uint8_t anzahl = sprintf(buffer,"%4.2f",druck.pressure);
		for(int i=0;i<anzahl;i++){
			transmit_values(buffer[i]);
		}*/
   }
   else if (status == DHT_ERROR_CHECKSUM){
		// Do something if there is a Checksum error
   }
   else if (status == DHT_ERROR_NOT_RESPOND){
   	// Do something if the sensor did not respond
   }
	transmit_values('\t');
	transmit_values('0'+status);

}

