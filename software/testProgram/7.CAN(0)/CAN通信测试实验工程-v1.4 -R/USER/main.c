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
	u8 mode=CAN_Mode_LoopBack;//CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ

 	SystemInit();
	delay_init();	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	LCD_Init();


	CAN_Mode_Init(CAN_SJW_3tq,CAN_BS1_16tq,CAN_BS2_8tq,20,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������450Kbps  
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,"WarShip STM32");	
	LCD_ShowString(60,70,"CAN TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2016/9/24");
	LCD_ShowString(60,130,"LoopBack Mode");	 
	LCD_ShowString(60,150,"KEY0:Send KEY1:Mode");//��ʾ��ʾ��Ϣ		
  	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	LCD_ShowString(60,170,"Count:");			//��ʾ��ǰ����ֵ	
	LCD_ShowString(60,190,"Send Data:");		//��ʾ���͵�����	
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
		if(key==1)//KEY0����,����һ������
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//��䷢�ͻ�����
				if(i<4)LCD_ShowxNum(60+i*32,210,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(60+(i-4)*32,230,canbuf[i],3,16,0X80);	//��ʾ����
				LCD_ShowxNum(60,30,speed,3,16,0);
				
 			}
			res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
			if(res)
				LCD_ShowString(60+80,190,"Failed");		//��ʾ����ʧ��
			else 
				LCD_ShowString(60+80,190,"OK    ");	 		//��ʾ���ͳɹ�								   
		}
		else if(key==2)//WK_UP���£��ı�CAN�Ĺ���ģʽ
		{	   
			mode=!mode;
  			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_3tq,CAN_BS2_2tq,speed,mode);//CAN��ͨģʽ��ʼ��, ������450Kbps
			POINT_COLOR=RED;//��������Ϊ��ɫ 
			if(mode==0)//��ͨģʽ����Ҫ2��������
			{
				LCD_ShowString(60,130,"Nnormal Mode ");	    
			}else //�ػ�ģʽ,һ��������Ϳ��Բ�����.
			{
 				LCD_ShowString(60,130,"LoopBack Mode");
			}
 			POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		}
		
		key=Can_Receive_Msg(rxdbuf);
		if(key)//���յ�������
		{			
			LCD_Fill(60,270,130,310,WHITE);//���֮ǰ����ʾ
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,rxdbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(60+(i-4)*32,290,rxdbuf[i],3,16,0X80);	//��ʾ����
				
 			}
		}
		buad=36000/((CAN_SJW_1tq+CAN_BS1_3tq+CAN_BS2_2tq)*speed);
		LCD_ShowxNum(60,30,speed,3,16,0);
		LCD_ShowxNum(120,30,buad,3,16,0);
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
			cnt++;
 			LCD_ShowxNum(60+48,170,cnt,3,16,0X80);	//��ʾ����
		}		   
	}
}
