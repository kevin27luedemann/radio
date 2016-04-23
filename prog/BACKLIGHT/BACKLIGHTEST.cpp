#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

#define BUTTONBACKLIGHT	17
#define BACKLIGHTAUS()	system("sudo sh -c 'echo '0' > /sys/class/gpio/gpio508/value'");
#define BACKLIGHTAn()	system("sudo sh -c 'echo '1' > /sys/class/gpio/gpio508/value'");


int main(){
	
	wiringPiSetupGpio();
	pinMode(BUTTONBACKLIGHT,INPUT);
	pullUpDnControl(BUTTONBACKLIGHT,PUD_UP);
	bool Lampean = true;

	system("sh -c 'echo 508 > /sys/class/gpio/export'");
	system("sudo sh -c 'echo 'out' > /sys/class/gpio/gpio508/direction'");

	while(true){
	
		if (!digitalRead(BUTTONBACKLIGHT) && !Lampean){
			std::cout << "Lampe an" << std::endl;
			BACKLIGHTAn();
			Lampean = true;
			system("sleep 1");
		}
		else if (!digitalRead(BUTTONBACKLIGHT) && Lampean){
			std::cout << "Lampe aus" << std::endl;
			BACKLIGHTAUS();
			Lampean = false;
			system("sleep 1");
		}
	}

	return 0;
}
