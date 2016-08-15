


#include "DHT22.h"

#define DHT22_COUNT 6
#define DHT22_MAXTIMINGS 85

DHT22::DHT22(uint8_t DDRpin){
	pin	 = DDRpin;
	temperature_decimal = 0;
	temperature_integral = 0;
	humidity_decimal = 0;
	humidity_integral = 0;
	for(uint8_t i=0;i<DHT22_COUNT;i++){
		data[i] = 0;
	}
}

DHT22::~DHT22(){
}

uint8_t DHT22::count_seconds(){
	uint8_t counter = 0;
	while(!(PIN_DHT22&(1<<pin)) && counter < 255){
		_delay_us(1);
		counter ++;
	}
	if(counter >=255 ){
		return 212;
	}
	else{
		counter = 0;
	}
	while((PIN_DHT22&(1<<pin)) && counter < 255){
		_delay_us(1);
		counter++;
	}
	return counter;
}

uint8_t DHT22::read_sensor(){
    uint8_t sum = 0;
    uint8_t counter = 0;
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	//sende startsignal
    DDR_DHT22 |= (1 << pin);
    PORT_DHT22 &= ~(1 << pin);
    _delay_ms(10);
    cli();
    PORT_DHT22 |= (1 << pin);
    DDR_DHT22 &= ~(1 << pin);
	_delay_us(2);
	//warte antwort ab
	while((PIN_DHT22&(1<<pin)) && counter < 255){
		counter ++;
	}
	if(counter == 255){
		sei();
		return 4;
	}
	counter = count_seconds();
	if(counter >= 250){
		sei();
		return 3;
	}
    for (uint8_t i = 0; i < DHT22_MAXTIMINGS; i++) {
		counter = count_seconds();
		if (counter <= 100){
			//1 Signal
			//setze 1sen an die jeweiligen stellen
			if(i < 8){
				data[0] |= (1<<i);
			}
			else if(i < 16){
				data[1] |= (1<<(i-8));
			}
			else if(i < 24){
				data[2] |= (1<<(i-16));
			}
			else if(i < 32){
				data[3] |= (1<<(i-24));
			}
			else if(i >= 32){
				data[4] |= (1<<(i-32));
			}
		}
		else if(counter == 212){
			sei();
			return 2;
		}
        else if (counter >= 250)
			sei();
            return i+5;
    }

    sei();
    sum = data[0] + data[1] + data[2] + data[3];
	if(sum != data[4]){
		//zu letzt aendern
		return 0;
	}

    return 1;
}

uint8_t DHT22::get_values(){
	uint8_t status = read_sensor();
	if (status == 1) {
        /* Reading temperature */
        temp = (int16_t)data[2]*256.0;
		temp += data[3];
        temp /= 10.0;

		temperature_integral = (int8_t)data[2];
		temperature_decimal = (uint8_t)data[3];

        /* Reading humidity */
        hum = data[0]*256.0;
		hum += data[1];
		hum /= 10.0;
		
		humidity_integral = (uint8_t)data[0];
		humidity_decimal = (uint8_t)data[1];
		
    }
    return status;
}
