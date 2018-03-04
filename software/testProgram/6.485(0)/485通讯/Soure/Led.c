#include "stm32f10x_lib.h"

#include "CBase.h"
#include "Led.h"
#include "UART.h"
#include "Key.h"
#include "SysT.h"
#include "Timer2.h"
#include "AD.h"
#include "SPI.h"
#include "RTC.h"

#include "Comm.h"

void LedInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能外设时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        LedOff();
}

void LedOff(void)
{
        LedOutput(0,0);
        LedOutput(1,0);
        LedOutput(2,0);
        LedOutput(3,0);
}

void LedOutput(unsigned char LedNumber,unsigned char IfOn)
{
        if(LedNumber>3)
        {
                LedNumber = 0;
        }

        switch (LedNumber)
        {
               
                case 0:
                        if(IfOn)
                        {
                                GPIO_ResetBits(GPIOB,GPIO_Pin_14);
                        }
                        else
                        {
                                GPIO_SetBits(GPIOB,GPIO_Pin_14);
                        }
                        break;
                case 1:
                        if(IfOn)
                        {
                                GPIO_ResetBits(GPIOB,GPIO_Pin_12);
                        }
                        else
                        {
                                GPIO_SetBits(GPIOB,GPIO_Pin_12);
                        }
                        break;
                case 2:
                        if(IfOn)
                        {
                                GPIO_ResetBits(GPIOB,GPIO_Pin_13);
                        }
                        else
                        {
                                GPIO_SetBits(GPIOB,GPIO_Pin_13);
                        }
                        break;
                default:
                        break;
        }
}

void LedTest(void)
{
        while(1)
        {
                LedOutput(0,1);
                DelayNmS(200);
                LedOutput(0,0);

                LedOutput(1,1);
                DelayNmS(200);
                LedOutput(1,0);

                LedOutput(2,1);
                DelayNmS(200);
                LedOutput(2,0);

                
        }
}
