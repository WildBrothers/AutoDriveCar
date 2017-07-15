
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h> 

# define SERVO 1
 
int main()
{
    char str;
    
    if(wiringPiSetup()==-1)
      return 1;

    softPwmCreate(SERVO,0,200);

    while(1)
    {
        fputs("select c,r,l q :", stdout);
        scanf("%c", &str);
        getchar();
          
        if(str=='c') // 가운데로 자동차 바퀴 이동.
            softPwmWrite(SERVO,15);
        else if(str=='r') // 오른쪽으로 자동차 바퀴 이동.
            softPwmWrite(SERVO,24);
        else if(str=='l') // 왼쪽으로 자동차 바퀴 이동.
            softPwmWrite(SERVO,5);
        else if(str=='q')
          return 0;
     }
  
     return 0;
}
