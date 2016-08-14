

#ifndef __DHT22__
#define __DHT22__
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef DDR_DHT22
	#define DDR_DHT22 DDRB
#endif
#ifndef PORT_DHT22
	#define PORT_DHT22 PORTB
#endif
#ifndef PIN_DHT22
	#define PIN_DHT22 PINB
#endif
class DHT22
{
//Variablem
public:
	float hum;
	float temp;
	int8_t temperature_integral;
	uint8_t temperature_decimal;
	uint8_t humidity_integral;
	uint8_t humidity_decimal;

private:
	uint8_t data[6];
	int pin;

protected:

//Funktionien
public:
	DHT22(uint8_t DDRpin);
	~DHT22();
	uint8_t get_values();

private:
	DHT22(const DHT22 &c);
	DHT22& operator=(const DHT22 &c);
	uint8_t read_sensor();

protected:

};

#endif
