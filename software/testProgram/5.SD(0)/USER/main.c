#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "malloc.h"  
#include "MMC_SD.h"   


//读取SD卡的指定扇区的内容，并通过串口1输出
//sec：扇区物理地址编号
void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);				//申请内存
	if(SD_ReadDisk(buf,sec,1)==0)	//读取0扇区的内容
	{	
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//打印sec扇区数据    	   
		printf("\r\nDATA ENDED\r\n");
	}
	myfree(buf);//释放内存	
}
	

 int main(void)
 { 
	 
	u8 t=0;	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2串口有用到中断
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	led_Init();		  		//初始化与LED连接的硬件接口
 	mem_init();				//初始化内存池	   
 	while(SD_Initialize())//检测不到SD卡
	{
		D0=!D0;//DS0闪烁
	}
   D1=0;   //检测到SD卡DS1亮
	while(1)
	{
		SD_Read_Sectorx(0);//读取SD卡扇区0的内容
		t++;
		delay_ms(10);
		if(t==20)
		{
			D1=!D1;
			t=0;
		}
	}    	   
}






