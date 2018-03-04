#include "Include.h"

void SysTInit(void)
{
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//2M
        SysTick_SetReload(200000);//100ms

        SysTick_ITConfig(ENABLE);

        NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 2, 0);

        SysTStop();
}

void SysTStart(void)
{
        SysTick_CounterCmd(SysTick_Counter_Enable);
}

void SysTStop(void)
{
        SysTick_CounterCmd(SysTick_Counter_Disable);
}

void SysTTest(void)
{
        SysTStart();
        while(1);
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
unsigned char SysTTestFlag = 0;
void SysTickHandler(void)
{
        if(SysTTestFlag)
        {
                SysTTestFlag = 0;
                LedOutput(0,0);
        }
        else
        {
                SysTTestFlag = 1;
                LedOutput(0,1);
        }
}





