/* Copyright 2014 Miguel Moreto
 *
 * This file is part of DHT22 Interrupt Driven library for AVR.
 *
 * DHT22 Interrupt Driven library for AVR is free software: you can redistribute 
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * DHT22 Interrupt Driven library for AVR is distributed in the hope that it will 
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * 
 * Please consult the GNU General Public License at http://www.gnu.org/licenses/.
 */

/*
 * DHT22int.h
 *
 * Version 1
 *
 * Header file of the DHT22 Interrupt Driven library for AVR.
 * Created: 12/01/2014 22:25:54
 * Author: Miguel Moreto

 *
 * IMPORTANT: You need to modify this file accordingly with your microcontroller,
 *            the external interrupt used (and the pin) and the timer.
 *
 * This file is configured to the following situation:
 *    Microcontroller: ATmega328P
 *    Timer: 8bit Timer 2
 *    Pin: PD2 => INT0 pin
 *    8MHz clock from internal RC oscillator.
 *    Divide by 8 fuse not programmed (clock is not divided by 8).
 *
 * This config should also work with ATmega48A(PA), ATmega88A(PA),
 * ATmega168A(PA) and ATmega328.
 *
 * Please, see the comments at the .c file about how the lib works and how to use it.
 */

#ifndef __DHT22__
#define __DHT22__

#include <avr/io.h>
#include <avr/interrupt.h>

/* Driver Configuration */
#define OVERFLOWS_HOST_START 2 // How many times a timer overflow is used to generate Period P1.
#define DHT22_DATA_BIT_COUNT 40 // Number of bits that the sensor send.

/* Macros: */
#define PIN_LOW(port,pin) port &= ~(1<<pin)
#define PIN_HIGH(port,pin) port |= (1<<pin)
#define SET_PIN_INPUT(portdir,pin) portdir &= ~(1<<pin)
#define SET_PIN_OUTPUT(portdir,pin) portdir |= (1<<pin)
#define PIN_TOGGLE(port,pin) port ^= (1<<pin)

/* Pin definition (change accordingly) 
   The pin must be a INT pin. Pin Change Interrupt is not sopported yet. */
//#define DHT22_PIN PIND2 // INT0
//#define DHT22_DDR DDRD
//#define DHT22_PORT PORTD

/* User define macros. Please change this macros accordingly with the microcontroller,
   pin, the timer and also the external interrupt that you are using.
   
   IMPORTANT: You must configure the timer with a prescaler such that the tick
              is 1us, this means a timer clock freq. of 1MHz. With 8MHz clock, you
			  can set the prescaler to divide by 8. */
//#define TIMER_SETUP_CTC	 				TCCR2A = (1 << WGM21);   // Code to configure the timer in CTC mode.
//#define TIMER_ENABLE_CTC_INTERRUPT		TIMSK2 = (1 << OCIE2A);  // Code to enable Compare Match Interrupt
//#define TIMER_OCR_REGISTER				OCR2A			// Timer output compare register.
//#define TIMER_COUNTER_REGISTER			TCNT2			// Timer counter register
//#define TIMER_START						TCCR2B = (1 << CS21); // Code to start timer with 1MHz clock
//#define TIMER_STOP						TCCR2B = 0; // Code to stop the timer by writing 0 in prescaler bits.
//#define EXT_INTERRUPT_DISABLE			EIMSK &= ~(1 << INT0); // Code to disable the external interrupt used.
//#define EXT_INTERRUPT_ENABLE			EIMSK |= (1 << INT0);  // Code to enable the external interrupt used.
//#define EXT_INTERRUPT_SET_RISING_EDGE	EICRA |= (1 << ISC01) | (1 << ISC00); // Code to set the interrupt to rising edge
//#define EXT_INTERRUPT_SET_FALLING_EDGE	EICRA |= (1 << ISC01); EICRA &= ~(1 << ISC00);  // Code to set the interrupt to falling edge
//#define EXT_INTERRUPT_CLEAR_FLAG		EIFR |= (1 << INTF0);  // Code to clear the external interrupt flag.

/* Interrupt vectors. Change accordingly */
//#define TIMER_CTC_VECTOR				TIMER2_COMPA_vect
//#define EXT_INTERRUPT_VECTOR			INT0_vect

class DHT22
{
//Variablem
public:
	int8_t temperature_integral;
	uint8_t temperature_decimal;
	uint8_t humidity_integral;
	uint8_t humidity_decimal;
	typedef enum
	{
		DHT_STOPPED = 0,
		DHT_HOST_START,
		DHT_HOST_PULLUP,
		DHT_WAIT_SENSOR_RESPONSE,
		DHT_SENSOR_PULLUP,
		DHT_TRANSFERING,
		DHT_CHECK_CRC,
		DHT_DATA_READY,
		DHT_ERROR_NOT_RESPOND,
		DHT_ERROR_CHECKSUM,
		DHT_BUSY,
		DHT_STARTED,
	} DHT22_STATE_t;
	DHT22_STATE_t state;
	uint8_t overflow_cnt;
	uint8_t bitcounter;

	uint8_t csPart1, csPart2, csPart3, csPart4;
	uint16_t rawHumidity;
	uint16_t rawTemperature;
	uint8_t checkSum;

private:
	int8_t DHT22_OFFSET;
	uint8_t DHT22_PIN;
	volatile uint8_t *DHT22_DDR;
	volatile uint8_t *DHT22_PORT;

	uint8_t DHT22_INT;
	uint8_t DHT22_ISC0;
	uint8_t DHT22_ISC1;
	uint8_t DHT22_INTF;
	volatile uint8_t *DHT22_EIMSK;
	volatile uint8_t *DHT22_EICRA;
	volatile uint8_t *DHT22_EIFR;

	uint8_t DHT22_CS1;
	volatile uint8_t *TIMER_OCR_REGISTER;
	volatile uint8_t *TIMER_COUNTER_REGISTER;
	volatile uint8_t *DHT22_TCCRB;

protected:

//Funktionien
public:
	DHT22(int8_t offset, uint8_t DDRpin, volatile uint8_t *DHT22DDR, volatile uint8_t *DHT22PORT, uint8_t DHT22INT, uint8_t DHT22ISC0, uint8_t DHT22ISC1, uint8_t DHT22INTF, volatile uint8_t *DHT22EIMSK, volatile uint8_t *DHT22EICRA, volatile uint8_t *DHT22EIFR, uint8_t DHT22CS1, volatile uint8_t *TIMEROCRREGISTER, volatile uint8_t *TIMERCOUNTERREGISTER, volatile uint8_t *DHT22TCCRB);
	~DHT22();
	uint8_t DHT22_StartReading(void);
	uint8_t DHT22_CheckStatus();
	void ISR_INT_ROUTINE();
	void ISR_TIMER_TOUTINE();

private:
	DHT22(const DHT22 &c);
	DHT22& operator=(const DHT22 &c);
	void EXT_INTERRUPT_DISABLE(){*DHT22_EIMSK &= ~(1 << DHT22_INT);};
	void EXT_INTERRUPT_ENABLE(){*DHT22_EIMSK |= (1 << DHT22_INT);};
	void EXT_INTERRUPT_SET_RISING_EDGE(){*DHT22_EICRA |= (1 << DHT22_ISC1) | (1 << DHT22_ISC0);};
	void EXT_INTERRUPT_SET_FALLING_EDGE(){*DHT22_EICRA |= (1 << DHT22_ISC1); *DHT22_EICRA &= ~(1 << DHT22_ISC0);};
	void EXT_INTERRUPT_CLEAR_FLAG(){*DHT22_EIFR |= (1 << DHT22_INTF);};

	void TIMER_START(){*DHT22_TCCRB = (1 << DHT22_CS1);};
	void TIMER_STOP(){*DHT22_TCCRB = 0;};
	
protected:
};

#endif
