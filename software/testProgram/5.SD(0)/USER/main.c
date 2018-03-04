#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "malloc.h"  
#include "MMC_SD.h"   


//��ȡSD����ָ�����������ݣ���ͨ������1���
//sec�����������ַ���
void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);				//�����ڴ�
	if(SD_ReadDisk(buf,sec,1)==0)	//��ȡ0����������
	{	
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//��ӡsec��������    	   
		printf("\r\nDATA ENDED\r\n");
	}
	myfree(buf);//�ͷ��ڴ�	
}
	

 int main(void)
 { 
	 
	u8 t=0;	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2�������õ��ж�
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	led_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	mem_init();				//��ʼ���ڴ��	   
 	while(SD_Initialize())//��ⲻ��SD��
	{
		D0=!D0;//DS0��˸
	}
   D1=0;   //��⵽SD��DS1��
	while(1)
	{
		SD_Read_Sectorx(0);//��ȡSD������0������
		t++;
		delay_ms(10);
		if(t==20)
		{
			D1=!D1;
			t=0;
		}
	}    	   
}






