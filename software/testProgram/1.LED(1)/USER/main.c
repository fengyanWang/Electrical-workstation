#include "sys.h"
#include "led.h"
#include "delay.h"
int main(void)
{
	delay_init();//��ʱ����������
	led_Init();//LED��ʼ��
	D0=1;      //DS0������DS1����
	D1=0;
	while(1)
	{
		D0=!D0;
		delay_ms(500);//��ʱ500ms
		D1=!D1;
		delay_ms(500);//��ʱ500ms
	}


}

	