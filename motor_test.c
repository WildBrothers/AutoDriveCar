#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <signal.h>

# define MOTOR 1 // GPIO 18
# define SERVO 2
# define DIRECTION 3 // GPIO 22

void init() 
{
	pwmWrite(MOTOR, 0); //PWM 핀 사용 
	digitalWrite(DIRECTION, LOW); //디지털 출력하는 메소드
}
void INThandler(int sig)
{
	printf("\ngoodBye\n");
	init();
	exit(0);
}
int main()
{
	char str;
	printf("motor test Start \n");

	if(wiringPiSetup()==-1)//wiringPi 초기화 
		return 1;
	
	signal(SIGINT,INThandler);
	
	pinMode(MOTOR, OUTPUT); //pin을 INPUT, OUTPUT으로 바꿀 때 사용
	pinMode(DIRECTION, OUTPUT);

	pullUpDnControl(MOTOR, PUD_DOWN);// 풀업 풀다운 저항 설정
	pullUpDnControl(DIRECTION, PUD_DOWN);

	softPwmCreate(SERVO,0,200);//서보 모터 핀번호 설정 , 범위 설정

	while(1)
	{
		fputs("select c,r,l,u,b :",stdout);
		scanf("%c", &str);
		getchar();

		if(str=='c') // 가운데로 자동차바퀴 이동.
			softPwmWrite(SERVO,15);
		else if(str=='r') //오른쪽으로 바퀴 이동
			softPwmWrite(SERVO,24);
		else if(str=='l')
			softPwmWrite(SERVO,5);
		else if(str=='u')
		{
			digitalWrite(MOTOR, HIGH);
			digitalWrite(DIRECTION, LOW);
			usleep(1000*500);
		}
		else if(str=='b')
		{
			digitalWrite(MOTOR, LOW);
			digitalWrite(DIRECTION, HIGH);
			usleep(1000*500);
		}
		else if(str=='q')
		{
			return 0;
		}
	}

	return 0;

}
