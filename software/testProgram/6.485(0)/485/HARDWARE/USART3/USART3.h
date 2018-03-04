#ifndef __USART3_H
#define __USART3_H
#include "delay.h"

#define RX_EN GPIO_ResetBits(GPIOB,GPIO_Pin_9)   //485接收使能
#define TX_EN GPIO_SetBits(GPIOB,GPIO_Pin_9)	//485发送使能

void UART3Init(void);
void UART3SendByte(unsigned char SendData);
unsigned char UART3GetByte(unsigned char* GetData);
void RS485_Test(void);


#endif


