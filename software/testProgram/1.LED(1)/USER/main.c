#include "sys.h"
#include "led.h"
#include "delay.h"
int main(void)
{
	delay_init();//延时函数的声明
	led_Init();//LED初始化
	D0=1;      //DS0先亮，DS1后亮
	D1=0;
	while(1)
	{
		D0=!D0;
		delay_ms(500);//延时500ms
		D1=!D1;
		delay_ms(500);//延时500ms
	}


}

	