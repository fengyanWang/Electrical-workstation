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



#define Set_RE  GPIO_SetBits(GPIOC,GPIO_Pin_5);			 
#define Clr_RE  GPIO_ResetBits(GPIOC,GPIO_Pin_5);

#define Set_DE  GPIO_SetBits(GPIOC,GPIO_Pin_4);
#define Clr_DE  GPIO_ResetBits(GPIOC,GPIO_Pin_4);


void UART3Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//使能外设时钟	  
         GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);



        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        USART_InitStructure.USART_BaudRate = 9600;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
        USART_Init(USART3, &USART_InitStructure);

        USART_Cmd(USART3, ENABLE);
}



void UART3SendByte(unsigned char SendData)
{	   Set_DE;
	   Set_RE;DelayNmS(1);
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		DelayNmS(1);
	   Clr_DE;
	   Clr_RE; 
}


unsigned char UART3GetByte(unsigned char* GetData)
{
  	   Clr_DE;
	   Clr_RE;DelayNmS(1); 
        if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
        {
                return 0;//没有收到数据
        }

        *GetData = USART_ReceiveData(USART3);
	   DelayNmS(1);
	   Set_DE;
	   Set_RE;

        return 1;//收到数据
}

void RS485_Test(void)
{
        unsigned char i = 0;
		 unsigned char a = 0;

      while(1)
       {
           
			   while(UART3GetByte(&i))
                { UART3SendByte(i);
           if(i==0x01){	 LedOutput(0,1);}
		   if(i==0x02){	 LedOutput(1,1);}
		   if(i==0x03){	 LedOutput(2,1); }
		   if(i==0x04){	 LedOutput(0,0); LedOutput(1,0);  LedOutput(2,0);}

                }

			 
                        
             
        }

      
}


