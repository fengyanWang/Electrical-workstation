#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"
//ALIENTEK Mini STM32开发板范例代码13
//RTC实时时钟实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 	
 int main(void)
 { 
	u8 t;	
	NVIC_Configuration();
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();				//初始化与LED连接的硬件接口
 	LCD_Init();				//初始化LCD
	usmart_dev.init(72);	//初始化USMART				 	
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");//显示字符串;x,y:起点坐标;width,height:区域大小;size:字体大小;*p:字符串起始地址		  
	LCD_ShowString(60,70,200,16,16,"RTC TEST");	
	LCD_ShowString(60,90,400,16,16,"the author is wfy");
	LCD_ShowString(60,110,200,16,16,"2016/1/6");	
	while(RTC_Init())		//RTC初始化	，一定要初始化成功
	{ 
		LCD_ShowString(60,130,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(60,130,200,16,16,"RTC Trying...");	
	}		    						
	//显示时间
	
	POINT_COLOR=BLUE;//设置字体为蓝色					 
	LCD_ShowString(60,130,200,16,16,"    -  -     ");	   
	LCD_ShowString(60,162,200,16,16,"  :  :  ");
	
	while(1)
	{	
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			//显示数字,高位为0,则不显示;x,y :起点坐标;len :数字的位数;size:字体大小;color:颜色 ;num:数值(0~4294967295);
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



