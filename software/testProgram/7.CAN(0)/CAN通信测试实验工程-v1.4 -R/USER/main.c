#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "can.h" 

 
 int main(void)
 {
	u8 key;
	u8  cs0;
	u8 i=0,t=0;
	static u16 speed=500;
	u8 cnt=0;
	static u32 buad;
	u8  canbuf[8];
	u8  rxdbuf[8];
	u8 res;
	u8 mode=CAN_Mode_LoopBack;//CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式

 	SystemInit();
	delay_init();	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();


	CAN_Mode_Init(CAN_SJW_3tq,CAN_BS1_16tq,CAN_BS2_8tq,20,CAN_Mode_LoopBack);//CAN初始化环回模式,波特率450Kbps  
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,"WarShip STM32");	
	LCD_ShowString(60,70,"CAN TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2016/9/24");
	LCD_ShowString(60,130,"LoopBack Mode");	 
	LCD_ShowString(60,150,"KEY0:Send KEY1:Mode");//显示提示信息		
  	POINT_COLOR=BLUE;//设置字体为蓝色	  
	LCD_ShowString(60,170,"Count:");			//显示当前计数值	
	LCD_ShowString(60,190,"Send Data:");		//提示发送的数据	
	LCD_ShowString(60,250,"Receive Data:");	      
	while(1)
	{
		
		cs0=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
		if(cs0==1)
		{
			speed+=1;
			if(speed==1024)
			{
				speed=0;
			}
			cs0=0;
		}
		key=KEY_Scan(0);
		if(key==1)//KEY0按下,发送一次数据
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//填充发送缓冲区
				if(i<4)LCD_ShowxNum(60+i*32,210,canbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(60+(i-4)*32,230,canbuf[i],3,16,0X80);	//显示数据
				LCD_ShowxNum(60,30,speed,3,16,0);
				
 			}
			res=Can_Send_Msg(canbuf,8);//发送8个字节 
			if(res)
				LCD_ShowString(60+80,190,"Failed");		//提示发送失败
			else 
				LCD_ShowString(60+80,190,"OK    ");	 		//提示发送成功								   
		}
		else if(key==2)//WK_UP按下，改变CAN的工作模式
		{	   
			mode=!mode;
  			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_3tq,CAN_BS2_2tq,speed,mode);//CAN普通模式初始化, 波特率450Kbps
			POINT_COLOR=RED;//设置字体为红色 
			if(mode==0)//普通模式，需要2个开发板
			{
				LCD_ShowString(60,130,"Nnormal Mode ");	    
			}else //回环模式,一个开发板就可以测试了.
			{
 				LCD_ShowString(60,130,"LoopBack Mode");
			}
 			POINT_COLOR=BLUE;//设置字体为蓝色 
		}
		
		key=Can_Receive_Msg(rxdbuf);
		if(key)//接收到有数据
		{			
			LCD_Fill(60,270,130,310,WHITE);//清除之前的显示
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,rxdbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(60+(i-4)*32,290,rxdbuf[i],3,16,0X80);	//显示数据
				
 			}
		}
		buad=36000/((CAN_SJW_1tq+CAN_BS1_3tq+CAN_BS2_2tq)*speed);
		LCD_ShowxNum(60,30,speed,3,16,0);
		LCD_ShowxNum(120,30,buad,3,16,0);
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//提示系统正在运行	
			t=0;
			cnt++;
 			LCD_ShowxNum(60+48,170,cnt,3,16,0X80);	//显示数据
		}		   
	}
}
