#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "USART3.h"


 int main(void)
 {	
//	u8 t;
//	u8 len;	
//	u16 times=0; 
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_Configuration();// �����ж����ȼ�����
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	UART3Init();
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
	 
	while(1)
	{
		RS485_Test();
	}
 
//	while(1)
//	{
//		if(USART_RX_STA&0x8000)//�жϴ���1�Ƿ��н�������
//		{					   
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];//�����յ������ݷŵ��Ĵ���USART1->DR
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			}
//			printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;//�����ձ�־����
//		}
//		else
//		{
//			times++;//��ʱ
//			if(times%500==0)//û��5000�δ�ӡ���������
//			{
////				printf("\r\nALIENTEK MiniSTM32������ ����ʵ��\r\n");
////				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
//				printf("\r\n��ô��û�������ݣ���\r\n");
//				printf("���˵Ȳ����ˣ�����\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\r\n");//ÿ��200�������û���������  
//			if(times%10==0)
//			{
//				LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//				LED1=!LED1;
//			}
//			delay_ms(10);   
//		}
//	}	 
}


