#include "Include.h"

void KeyInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能外设时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能外设时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_15 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
}

unsigned char GetKey(void)
{
        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
        {
                DelayNmS(10);//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))//等待按键释放
                        {
                        }
                        return '3';//返回按键值
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
        {
                DelayNmS(10);//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))//等待按键释放
                        {
                        }
                        return '1';//返回按键值
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
        {
                DelayNmS(10);//去抖动
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))//等待按键释放
                        {
                        }
                        return '2';//返回按键值
                }
        }

        

        return NO_KEY;
}

void KeyTest(void)
{
        unsigned char i = 0;

        while(1)
        {
                i = GetKey();//按键扫描
                if(NO_KEY != i)
                {
                        LedOutput(0,1);//亮LED指示
                        UART1SendByte(i);//发送按键值
                        DelayNmS(100);
                        LedOutput(0,0);
                }
        }
}
