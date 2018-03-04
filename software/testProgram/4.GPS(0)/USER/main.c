#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	    
#include "gps.h"
#include "string.h"		
#include "usart4.h"

//ALIENTEK mini��������չʵ��16
//ATK-S1216F8 GPSģ�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
u8 USART1_TX_BUF[USART4_MAX_RECV_LEN]; 					//����1,���ͻ�����
nmea_msg gpsx; 											//GPS��Ϣ
__align(4) u8 dtbuf[50];   								//��ӡ������
const u8*fixmode_tbl[4]={"Fail","Fail"," 2D "," 3D "};	//fix mode�ַ��� 
	  
//��ʾGPS��λ��Ϣ 
void Gps_Msg_Show(void)
{
 	float tp;		    	 
	tp=gpsx.longitude;	   
	sprintf((char *)dtbuf,"Longitude:%.5f %1c   ",tp/=100000,gpsx.ewhemi);	//�õ������ַ���
	printf("GPS �ľ���Ϊ %s\n",dtbuf);
// 	LCD_ShowString(30,120,200,16,16,dtbuf);	 	   
	tp=gpsx.latitude;	   
	sprintf((char *)dtbuf,"Latitude:%.5f %1c   ",tp/=100000,gpsx.nshemi);	//�õ�γ���ַ���
	printf("GPS ��γ��Ϊ %s\n",dtbuf);
// 	LCD_ShowString(30,140,200,16,16,dtbuf);	 	 
	tp=gpsx.altitude;	   
 	sprintf((char *)dtbuf,"Altitude:%.1fm     ",tp/=10);	    			//�õ��߶��ַ���
	printf("GPS �ĸ߶�Ϊ %s\n",dtbuf);
// 	LCD_ShowString(30,160,200,16,16,dtbuf);	 			   
	tp=gpsx.speed;	   
 	sprintf((char *)dtbuf,"Speed:%.3fkm/h     ",tp/=1000);		    		//�õ��ٶ��ַ���	 
	printf("GPS ���ٶ�Ϊ %s\n",dtbuf);
//	LCD_ShowString(30,180,200,16,16,dtbuf);	 				    
	if(gpsx.fixmode<=3)														//��λ״̬
	{  
		sprintf((char *)dtbuf,"Fix Mode:%s",fixmode_tbl[gpsx.fixmode]);	
		printf("GPS ��״̬Ϊ %s\n",dtbuf);
//	  LCD_ShowString(30,200,200,16,16,dtbuf);			   
	}	 	   
	sprintf((char *)dtbuf,"GPS+BD Valid satellite:%02d",gpsx.posslnum);	 		//���ڶ�λ��GPS������
	printf("GPS �Ķ�λ������ĿΪ %s\n",dtbuf);
// 	LCD_ShowString(30,220,200,16,16,dtbuf);	    
	sprintf((char *)dtbuf,"GPS Visible satellite:%02d",gpsx.svnum%100);	 		//�ɼ�GPS������
	printf("GPS �Ŀɼ�������ĿΪ %s\n",dtbuf);
// 	LCD_ShowString(30,240,200,16,16,dtbuf);
	
	sprintf((char *)dtbuf,"BD Visible satellite:%02d",gpsx.beidou_svnum%100);	 		//�ɼ�����������
	printf("�ɼ�����������ĿΪ %s\n",dtbuf);
// 	LCD_ShowString(30,260,200,16,16,dtbuf);
	
	sprintf((char *)dtbuf,"UTC Date:%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);	//��ʾUTC����
	printf("GPS ��UTC����Ϊ %s\n",dtbuf);
//	LCD_ShowString(30,280,200,16,16,dtbuf);		    
	sprintf((char *)dtbuf,"UTC Time:%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);	//��ʾUTCʱ��
	printf("GPS ��UTCʱ��Ϊ %s\n",dtbuf);
//  LCD_ShowString(30,300,200,16,16,dtbuf);		  
}


 int main(void)
 { 
	u16 i,rxlen;
	u16 lenx;
	u8 key=0XFF;
	u8 upload=0; 	  
	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600	
	printf("i am ok_1!!!\n");
	USART4_Init(38400);  //��ʼ������2������Ϊ115200
//	printf("i am ok_2!!!\n");
//	u4_printf("123\n");
	LED_Init();         	//LED��ʼ��
	printf("i am ok_3!!!\n");	

//	LCD_ShowString(30,20,200,16,16,"ALIENTEK STM32F1 ^_^");	  
//	LCD_ShowString(30,40,200,16,16,"S1216F8-BD TEST");	
//	LCD_ShowString(30,60,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(30,80,200,16,16,"KEY0:Upload NMEA Data SW");   	 										   	   
//  LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:OFF");

	if(SkyTra_Cfg_Rate(5)!=0)	//���ö�λ��Ϣ�����ٶ�Ϊ5Hz,˳���ж�GPSģ���Ƿ���λ. 
	{
//   	LCD_ShowString(30,120,200,16,16,"S1216F8-BD Setting...");
		printf("i am ok_4!!!\n");
		printf("S1216F8-BD Setting...\n");
		do
		{
			USART4_Init(9600);			//��ʼ������4������Ϊ9600
			SkyTra_Cfg_Prt(3);			//��������ģ��Ĳ�����Ϊ38400
			USART4_Init(38400);			//��ʼ������4������Ϊ38400
			key=SkyTra_Cfg_Tp(100000);	//������Ϊ100ms
		}while(SkyTra_Cfg_Rate(5)!=0&&key!=0);//����SkyTraF8-BD�ĸ�������Ϊ5Hz
//	  LCD_ShowString(30,120,200,16,16,"S1216F8-BD Set Done!!");
		printf("S1216F8-BD Set Done!!\n");
		delay_ms(500);
//		LCD_Fill(30,120,30+200,120+16,WHITE);//�����ʾ 
	}
	
	while(1) 
	{		
		delay_ms(1);
		printf("i am ok_5!!!\n");
		if(USART4_RX_STA&0X8000)		//���յ�һ��������
		{
			printf("i am ok_6!!!\n");
			rxlen=USART4_RX_STA&0X7FFF;	//�õ����ݳ���
			for(i=0;i<rxlen;i++)USART1_TX_BUF[i]=USART4_RX_BUF[i];	   
 			USART4_RX_STA=0;		   	//������һ�ν���
			USART1_TX_BUF[i]=0;			//�Զ���ӽ�����
			GPS_Analysis(&gpsx,(u8*)USART1_TX_BUF);//�����ַ���
			Gps_Msg_Show();				//��ʾ��Ϣ	
			if(upload)printf("\r\n%s\r\n",USART1_TX_BUF);//���ͽ��յ������ݵ�����1
 		}
//		key=KEY_Scan(0);
//		if(key==KEY0_PRES)
//		{
//			upload=!upload;
//			POINT_COLOR=RED;
//			if(upload)LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:ON ");
//			else LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:OFF");
// 		}
		printf("i am ok_7!!!\n");
		if((lenx%500)==0)
		{
			LED0=!LED0;
			delay_ms(100);
		}
		lenx++;	
	}
}
 
























