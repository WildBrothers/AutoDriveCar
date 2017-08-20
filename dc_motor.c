#include <stdio.h>
#include <wiringPi.h>

#define MOTOR1 4 //GPIO 23
#define MOTOR2 5 //GPIO 24

int main(void){
	if (wiringPiSetup() == -1){
		return 1;
	}
	pinMode(MOTOR1,OUTPUT);
	pinMode(MOTOR2,OUTPUT);

	while(1)
	{
		digitalWrite(MOTOR1, 1);
		digitalWrite(MOTOR2, 0);
	}
	return 0;

}
 
