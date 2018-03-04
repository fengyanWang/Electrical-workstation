#include "led.h"
#include "USART3.h"
#include "usart.h"

//#define Set_RE  GPIO_SetBits(GPIOC,GPIO_Pin_5);			 
//#define Clr_RE  GPIO_ResetBits(GPIOC,GPIO_Pin_5);

//#define Set_DE  GPIO_SetBits(GPIOC,GPIO_Pin_4);
//#define Clr_DE  GPIO_ResetBits(GPIOC,GPIO_Pin_4);


void UART3Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//485_DIR	
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
//485_RX
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
//485_TX
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
{	  
	TX_EN;
	delay_ms(1);
    USART_SendData(USART3,SendData);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    delay_ms(1); 
}


unsigned char UART3GetByte(unsigned char* GetData)
{
  	   RX_EN;
	   delay_ms(1); 
       if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
        {
           printf("6\n");
			return 0;//没有收到数据
        }

       *GetData = USART_ReceiveData(USART3);
	   delay_ms(1);
       return 1;//收到数据
}

void RS485_Test(void)
{
    unsigned char i = 0x00;
//	printf("1\n");
     while(1)
     {
        i++; 
//		printf("2\n");		 
		while(UART3GetByte(&i))
         { 
			 
		   UART3SendByte(i);
           if(i==0x01)
			{	
				LED0=0;
				LED1=1;
//				printf("3\n");
			}
		   if(i==0x02)
			{	 
				LED0=1;
				LED1=0;
//				printf("4\n");
			}
		   if(i==0x03)
			{	 
				LED0=~LED0;
				LED1=1;
				delay_ms(100); 
			}
		   if(i==0x04)
			{	 
				LED0=1;
				LED1=1;
			}

		  }  
//			printf("5\n");
      }

      
}


