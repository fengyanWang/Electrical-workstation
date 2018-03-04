#include "sys.h"
#include "beep.h"
#include "delay.h"
int main(void)
{
	delay_init();//延时函数的声明
	Beep_Init();//蜂鸣器函数的声明
	while(1)
	{
	Be=0;
	delay_ms(500);
	Be=1;
	delay_ms(500);//蜂鸣器发声500ms
	}
}







	