#include "Include.h"

void ADInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        ADC_InitTypeDef ADC_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能外设时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//使能外设时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
        ADC_InitStructure.ADC_NbrOfChannel = 1;
        ADC_Init(ADC1, &ADC_InitStructure);

        ADC_Cmd(ADC1, ENABLE);

        ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_13Cycles5);

        ADC_ResetCalibration(ADC1);
        /* Check the end of ADC1 reset calibration register */
        while(ADC_GetResetCalibrationStatus(ADC1));

        /* Start ADC1 calibaration */
        ADC_StartCalibration(ADC1);
        /* Check the end of ADC1 calibration */
        while(ADC_GetCalibrationStatus(ADC1));
}

unsigned char GetADV(void)
{
        unsigned int DataValue;

        ADC_SoftwareStartConvCmd(ADC1, ENABLE);

        while(RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

        DataValue = ADC_GetConversionValue(ADC1);

        return (DataValue>>8);
}

void ADTest(void)
{
        while(1)
        {
                UART1SendByte(GetADV());
                DelayNmS(200);
        }
}

