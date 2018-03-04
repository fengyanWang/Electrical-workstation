#include "sys.h"
#include "beep.h"
void Beep_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //GPIOC的时钟使能
	
	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_Initstructure);//对GPIOC8设置50M的推挽输出
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//先关闭蜂鸣器
}



