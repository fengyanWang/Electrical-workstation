#include "sys.h"
#include "beep.h"
#include "delay.h"
int main(void)
{
	delay_init();//��ʱ����������
	Beep_Init();//����������������
	while(1)
	{
	Be=0;
	delay_ms(500);
	Be=1;
	delay_ms(500);//����������500ms
	}
}







	