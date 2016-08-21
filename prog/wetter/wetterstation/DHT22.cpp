/* Copyright 2014 Moreto
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
 * DHT22int.c
 * 
 * Version 1
 *
 * Main file of the DHT22 Interrupt Driven library for AVR.
 * Created: 12/01/2014 22:26:03
 * Author: Miguel Moreto
 
 * This lib can read temperature and humidity of a DHT22 sensor without
 * blocking the microcontroller with unnecessary delay functions.
 * The lib is interrupt driven, all the timing measurements of sensor
 * signal is done with a timer and a external interrupt using a state machine.
 * This way, you can use this lib with multiplexed displays without flicker the
 * display during the measurement of the sensor data.
 *
 * REQUIREMENTS: 
 *   A pin with external interrupt (INT0, INT1 or other).
 *   A timer with Clear Timer on Compare Match mode (CTC).
 *   Timer prescaler that gives a timer frequency of 1MHz.
 *
 *   Pin change interrupt is not supported yet.
 *
 * HOW IT WORKS:
 * Check the comments in this file to fully understand how it works. Basically:
 *   1) A timer in CTC is used to generate the host start condition.
 *      pin is configured as output (this is done in the timer interrupt
 *      handler function).
 *   2) Pin is switched to input with external interrupt. At each external
 *      interrupt the number of timer ticks (configured to occur at each
 *      microsecond) is counted.
 *   3) The value of the counter (microseconds) is compared with a fixed
 *      value in a state machine, this way, the signal from DHT22 is
 *      interpreted. This is done at the External Interrupt Handler.
 *
 * HOW TO USE:
 *  Include the lib:
 *
 *      #include "DHT22int.h"
 *
 *  Before entering the main loop of your program, declare some needed variables
 *  call the init function and enable interrupts.
 *
 *      DHT22_STATE_t state;
 *      DHT22_DATA_t sensor_data;
 *      DHT22_Init();
 *      sei();
 *
 *  Periodically (or not, depending of your use), call the function to 
 *  start reading the sensor:
 *
 *      state = DHT22_StartReading();
 *
 *  Check the state if you want to confirm that the state machine has started.
 *  In your main loop, check periodically when the data is available and in
 *  case of available, do something:
 *
 *      state = DHT22_CheckStatus(&sensor_data);
 *
 * 		if (state == DHT_DATA_READY){
 *	 		// Do something with the data.
 *          // sensor_data.temperature_integral
 *          // sensor_data.temperature_decimal
 *          // sensor_data.humidity_integral
 *          // sensor_data.humidity_decimal
 * 		}
 *		else if (state == DHT_ERROR_CHECKSUM){
 *	 		// Do something if there is a Checksum error
 *		}
 * 		else if (state == DHT_ERROR_NOT_RESPOND){
 *	 		// Do something if the sensor did not respond
 * 		}
 *
 *  To start a new measurement, you have to call DHT22_StartReading() again.
 *
 *  IMPORTANT: You need to modify the header (.h) file accordingly with your 
 *             microcontroller, the external interrupt used (and the pin) and
 *             the timer.
 */ 

#include "DHT22.h"

/*
 * void DHT22_Init(void)
 *
 * Function to be called before the main loop.
 * It configures the sensor pin and timer mode.
 */
DHT22::DHT22(uint8_t DDRpin){
	pin	 = DDRpin;
	temperature_decimal = 0;
	temperature_integral = 0;
	humidity_decimal = 0;
	humidity_integral = 0;

	/* Configuring DHT pin as output (initially) */
	DHT22_DDR |= (1 << DHT22_PIN);
	PIN_HIGH(DHT22_PORT,DHT22_PIN);
	
	/* Timer config. */
	TIMER_SETUP_CTC  // Seting timer to CTC
	TIMER_ENABLE_CTC_INTERRUPT  // Enable compare match interrupt
	// Timer is started by the function DHT22_StartReading. For now
	// it remains with prescaler = 0 (disable).
	TIMER_STOP
	
	state = DHT_STOPPED;

	overflow_cnt = 0;
	bitcounter = 0;

	rawHumidity = 0;
	rawTemperature = 0;
	checkSum = 0;
	
}

DHT22::~DHT22(){
}

/* NOTE: Check the macro definitions at the header file. */



/*
 * DHT22_STATE_t DHT22_CheckStatus(DHT22_DATA_t* data)
 *
 * Function that should be called after DHT22_StartReading() in order to check
 * if a transfer is complete.
 *
 * It returns a DHT22_STATE_t variable with the state of the state machine.
 *  Returned values:
 *    DHT_DATA_READY: Data is ok and can be used by the main program.
 *    DHT_ERROR_CHECKSUM: Error, checksum does no match.
 *    DHT_ERROR_NOT_RESPOND: Sensor is not connected or not responding for some reason.
 */

uint8_t DHT22::DHT22_CheckStatus(){
	
	/* If a transfer is complete, check CRC and update sensor data structure */
	if (state == DHT_CHECK_CRC){
		
		// calculate checksum:
		csPart1 = rawHumidity >> 8;
		csPart2 = rawHumidity & 0xFF;
		csPart3 = rawTemperature >> 8;
		csPart4 = rawTemperature & 0xFF;
		
		if( checkSum == ( (csPart1 + csPart2 + csPart3 + csPart4) & 0xFF ) ){ // Checksum correct
			
			/* raw data to sensor values */
			humidity_integral = (uint8_t)(rawHumidity / 10.0)+15;
			humidity_decimal = (uint8_t)(rawHumidity % 10);			
			if(rawTemperature & 0x8000)	// Check if temperature is below zero, non standard way of encoding negative numbers!
			{
				rawTemperature &= 0x7FFF; // Remove signal bit
				temperature_integral = (int8_t)(rawTemperature / 10.0) * -1;
				temperature_decimal = (uint8_t)(rawTemperature % 10);
			} else
			{
				temperature_integral = (int8_t)(rawTemperature / 10.0);
				temperature_decimal = (uint8_t)(rawTemperature % 10);
			}
			state = DHT_DATA_READY;
		}
		else{
			state = DHT_ERROR_CHECKSUM;
		}
	}
	
	return state;
}

/*
 * DHT22_STATE_t DHT22_StartReading(void)
 *
 * This function starts a new reading of the sensor.
 * It returns a variable of type DHT22_STATE_t with the possible values:
 *    DHT_BUSY: The reading did not started because the state machine 
 *              is doing something else, indicating that the previous
 *              reading did not finished.
 *    DHT_STARTED: The state machine has successfully started. The user
 *                 can wait for data using DHT22_CheckStatus() function.
 *
 */
uint8_t DHT22::DHT22_StartReading(void){
	
	/* Check if the state machine is stopped. If so, start it. */
	if (state == DHT_STOPPED || state == DHT_DATA_READY || state == DHT_ERROR_CHECKSUM || state == DHT_ERROR_NOT_RESPOND){
		/* Reset values and counters */
		rawTemperature = 0;
		rawHumidity = 0;
		checkSum = 0;
		overflow_cnt = 0;
		bitcounter = 0;
		/* Configuring peripherals */
		//EIMSK &= ~(1 << INT0); // Disable external interrupt
		EXT_INTERRUPT_DISABLE
		DHT22_DDR |= (1 << DHT22_PIN); // Configuring sensor pin as output.
		PIN_LOW(DHT22_PORT,DHT22_PIN); // Write 0 to pin. Start condition sent to sensor.
		TIMER_OCR_REGISTER = 255; // Timer compare value equals to overflow (interrupt will fired at 255us).
		TIMER_COUNTER_REGISTER = 0; // Reset counter value.
		state = DHT_HOST_START; // Change state.
		TIMER_START // Start timer with prescaler such that 1 tick equals 1us (freq = 1MHz).
		return DHT_STARTED; // Return value indicating that the state machine started.
	}
	else{
		return DHT_BUSY; // If state machine is busy, return this value.
	}
	
} // end DHT22_StartReading
