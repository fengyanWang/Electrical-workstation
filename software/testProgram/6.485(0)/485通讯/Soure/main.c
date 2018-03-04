/******************** 基本实验例程 ********************
*               UART3通过485接口发送和接收数据
*        		,发送0X01点亮LED1
*        		,发送0X02点亮LED2
*        		,发送0X03点亮LED3
*       		,发送0X04关闭全部LED
*******************************************************************************/

#include "stm32f10x_lib.h"

#include "CBase.h"
#include "Led.h"
#include "UART.h"




#include "Comm.h"



void RCC_Configuration(void)
{
        ErrorStatus HSEStartUpStatus;
        // RCC system reset(for debug purpose) 
        RCC_DeInit();

        // Enable HSE 
        RCC_HSEConfig(RCC_HSE_ON);

        // Wait till HSE is ready 
        HSEStartUpStatus = RCC_WaitForHSEStartUp();

        if(HSEStartUpStatus == SUCCESS)
        {
                // HCLK = SYSCLK 
                RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
                // PCLK2 = HCLK 
                RCC_PCLK2Config(RCC_HCLK_Div1); 

                // PCLK1 = HCLK/2 
                RCC_PCLK1Config(RCC_HCLK_Div2);
 
                // Flash 2 wait state 
                //FLASH_SetLatency(FLASH_Latency_2);
                FLASH_SetLatency(FLASH_Latency_0);
                //FLASH_SetLatency(FLASH_Latency_1);

                
                // Enable Prefetch Buffer 
                FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
                
                // PLLCLK = 8MHz * 2 = 16 MHz 
                RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_2);

                // Enable PLL 
                RCC_PLLCmd(ENABLE);

                // Wait till PLL is ready 
                while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
                {
                }

                // Select PLL as system clock source 
                RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

                // Wait till PLL is used as system clock source 
                while(RCC_GetSYSCLKSource() != 0x08)
                {
                }
                
        }

        // Enable peripheral clocks --------------------------------------------------
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configure the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
        //NVIC_InitTypeDef NVIC_InitStructure;
   
#ifdef  VECT_TAB_RAM  
        /* Set the Vector Table base location at 0x20000000 */ 
        NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
        /* Set the Vector Table base location at 0x08000000 */ 
        NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

void SystemInit(void)
{
        RCC_Configuration();//设置系统时钟
        NVIC_Configuration();//设置中断

       	LedInit();
        UART3Init(); //串口1 初始化
	
}


/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
        SystemInit();//系统初始化

        while (1)
        {
              
                RS485_Test();
			
        }
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
