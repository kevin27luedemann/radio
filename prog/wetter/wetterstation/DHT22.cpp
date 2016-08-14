


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
    DDR_DHT22 &= ~(1 << pin);
    PORT_DHT22 |= (1 << pin);
}

DHT22::~DHT22(){
    DDR_DHT22  &= ~(1 << pin);
    PORT_DHT22 &= ~(1 << pin);
}

uint8_t DHT22::read_sensor(){
    uint8_t tmp;
    uint8_t sum = 0;
    uint8_t j = 0, i;
    uint8_t last_state = 1;
    uint16_t counter = 0;
    /*
     * Pull the pin 1 and wait 250 milliseconds
     */
    PORT_DHT22 |= (1 << pin);
    _delay_ms(250);

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    /* Now pull it low for ~20 milliseconds */
    DDR_DHT22 |= (1 << pin);
    PORT_DHT22 &= ~(1 << pin);
    _delay_ms(20);
    cli();
    PORT_DHT22 |= (1 << pin);
    _delay_us(40);
    DDR_DHT22 &= ~(1 << pin);

    /* Read the timings */
    for (i = 0; i < DHT22_MAXTIMINGS; i++) {
        counter = 0;
        while (1) {
            tmp = ((PIN_DHT22 & (1 << pin)) >> 1);
            _delay_us(3);

            if (tmp != last_state)
                break;

            counter++;
            _delay_us(1);

            if (counter == 255)
                break;
        }

        last_state = ((PIN_DHT22 & (1 << pin)) >> 1);

        if (counter == 255)
            break;

        /* Ignore first 3 transitions */
        if ((i >= 4) && (i % 2 == 0)) {
            /* Shove each bit into the storage bytes */
            data[j/8] <<= 1;
            if (counter > DHT22_COUNT)
                data[j/8] |= 1;
            j++;
        }
    }

    sei();
    sum = data[0] + data[1] + data[2] + data[3];

    if ((j >= 40) && (data[4] == (sum & 0xFF)))
        return 1;
    return 0;
}

uint8_t DHT22::get_values(){
	if (read_sensor()) {
        /* Reading temperature */
        temp = data[2] & 0x7F;
        temp *= 256;
        temp += data[3];
        temp /= 10;

        if (data[2] & 0x80)
            temp *= -1;
		temperature_integral = (int8_t)temp;
		temperature_decimal = (uint8_t)(temp*10.0)%10;

        /* Reading humidity */
        hum = data[0];
        hum *= 256;
        hum += data[1];
        hum /= 10;
		
		humidity_integral = (uint8_t)hum;
		humidity_decimal = (uint8_t)(hum*10.0)%10;
		
        if (hum == 0.0f)
            return 0;
        return 1;
    }
    return 0;
}
