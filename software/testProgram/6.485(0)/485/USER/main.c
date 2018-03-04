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
 
	delay_init();	    	 //延时函数初始化	
	NVIC_Configuration();// 设置中断优先级分组
	uart_init(9600);	 //串口初始化为9600
	UART3Init();
	LED_Init();		  	 //初始化与LED连接的硬件接口 
	 
	while(1)
	{
		RS485_Test();
	}
 
//	while(1)
//	{
//		if(USART_RX_STA&0x8000)//判断串口1是否有接收数据
//		{					   
//			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];//将接收到的数据放到寄存器USART1->DR
//				while((USART1->SR&0X40)==0);//等待发送结束
//			}
//			printf("\r\n\r\n");//插入换行
//			USART_RX_STA=0;//将接收标志置零
//		}
//		else
//		{
//			times++;//计时
//			if(times%500==0)//没隔5000次打印下面的内容
//			{
////				printf("\r\nALIENTEK MiniSTM32开发板 串口实验\r\n");
////				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
//				printf("\r\n怎么还没发送数据？？\r\n");
//				printf("官人等不及了！！！\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\r\n");//每隔200次提醒用户输入数据  
//			if(times%10==0)
//			{
//				LED0=!LED0;//闪烁LED,提示系统正在运行.
//				LED1=!LED1;
//			}
//			delay_ms(10);   
//		}
//	}	 
}


