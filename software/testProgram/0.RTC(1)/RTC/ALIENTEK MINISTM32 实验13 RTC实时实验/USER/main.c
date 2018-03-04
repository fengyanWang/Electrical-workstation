#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"
//ALIENTEK Mini STM32�����巶������13
//RTCʵʱʱ��ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 	
 int main(void)
 { 
	u8 t;	
	NVIC_Configuration();
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();				//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();				//��ʼ��LCD
	usmart_dev.init(72);	//��ʼ��USMART				 	
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");//��ʾ�ַ���;x,y:�������;width,height:�����С;size:�����С;*p:�ַ�����ʼ��ַ		  
	LCD_ShowString(60,70,200,16,16,"RTC TEST");	
	LCD_ShowString(60,90,400,16,16,"the author is wfy");
	LCD_ShowString(60,110,200,16,16,"2016/1/6");	
	while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	{ 
		LCD_ShowString(60,130,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(60,130,200,16,16,"RTC Trying...");	
	}		    						
	//��ʾʱ��
	
	POINT_COLOR=BLUE;//��������Ϊ��ɫ					 
	LCD_ShowString(60,130,200,16,16,"    -  -     ");	   
	LCD_ShowString(60,162,200,16,16,"  :  :  ");
	
	while(1)
	{	
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			//��ʾ����,��λΪ0,����ʾ;x,y :�������;len :���ֵ�λ��;size:�����С;color:��ɫ ;num:��ֵ(0~4294967295);
			LCD_ShowNum(60,130,calendar.w_year,4,16);									  
			LCD_ShowNum(100,130,calendar.w_month,2,16);									  
			LCD_ShowNum(124,130,calendar.w_date,2,16);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(60,148,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60,148,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60,148,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60,148,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60,148,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60,148,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60,148,200,16,16,"Saturday ");
					break;  
			}
			LCD_ShowNum(60,180,calendar.hour,2,16);									  
			LCD_ShowNum(84,180,calendar.min,2,16);									  
			LCD_ShowNum(108,180,calendar.sec,2,16);
			LED0=!LED0;
		}	
		delay_ms(10);								  
	};  											    
}	



