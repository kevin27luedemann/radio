TARGET=main
MCU=atmega328p
SOURCES=$(TARGET).cpp  BMP180.cpp I2C.cpp DHT22.cpp
#SOURCES=$(shell find . -type f -name '*.cpp')

PROGRAMMER=stk500
#auskommentieren für automatische Wahl
PORT=-P/dev/ttyUSB0
BAUD=-B11600

#Ab hier nichts verändern
OBJECTS=$(SOURCES:.cpp=.o)
CFLAGS=-c -O
LDFLAGS=-lm

all: hex eeprom

hex: $(TARGET).hex

eeprom: $(TARGET)_eeprom.hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -j .data -j .text $(TARGET).elf $(TARGET).hex

$(TARGET)_eeprom.hex: $(TARGET).elf
	avr-objcopy -O ihex -j .eeprom --change-section-lma .eeprom=1 $(TARGET).elf $(TARGET)_eeprom.hex

$(TARGET).elf: $(OBJECTS)
	avr-g++ $(LDFLAGS) -mmcu=$(MCU) $(OBJECTS) -o $(TARGET).elf

%.o : %.cpp
	avr-g++ $(CFLAGS) -mmcu=$(MCU) $< -o $@

size:
	avr-size --mcu=$(MCU) -C $(TARGET).elf

program:
	avrdude -p$(MCU) $(PORT) $(BAUD) -c$(PROGRAMMER) -Uflash:w:$(TARGET).hex:a

clean_tmp:
	rm -rf *.o
	rm -rf *.elf

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex
