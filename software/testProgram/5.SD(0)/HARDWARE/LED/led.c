#include "sys.h"
#include "led.h"

void led_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //GPIOC��ʱ��ʹ��
	
	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_Initstructure);//��GPIOC8����50M���������

	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_Initstructure);//��GPIOC9����50M���������
	
	
	
	

}





