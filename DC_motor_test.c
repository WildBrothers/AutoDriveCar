#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>

#define MOTOR 1 //GPIO 18
#define DIRECTION 3 // GPIO 22

void INThandler(int);
void init();
void init()
{
	digitalWrite(MOTOR,LOW);
	digitalWrite(DIRECTION,LOW);
}
void INThandler(int sig)
{
	printf("\ngoodbye\n");
	init();
	exit(0);
}
int main()
{
	printf("DC_motor TEST\n");

	wiringPiSetup();
	signal(SIGINT, INThander);
	
	pinMode(MOTOR, OUTPUT);
	pinMode(DIRECTION, OUTPUT);

	pullUpDnControl(MOTOR, PUD_DOWN);
	pullUpDnControl(DIRECTION, PUD_DOWN);

	while(1)
	{
		digitalWrite(DIRECTION, HIGH);
		digitalWrite(MOTOR, HIGH);
		usleep(1000*500);
		digitalWrite(Motor,LOW);
		usleep(1000*500);
		
		digitalWrite(DIRECTION, LOW);
		digitalWRite(MOTOR, HIGH);
		usleep(1000*500);
		digitalWrite(MOTOR, LOW);
		usleep(1000*500);
	}
}
void INThandler(int signal)
{
	printf("\ngoodbye\n");
	init();
	exit(0);
}
void init()
{
	digitalWrite(MOTOR, LOW);
	digitalWrite(DIRECTION, LOW);
}
