#include "Include.h"

void KeyInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ������ʱ��
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ������ʱ��

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_15 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
}

unsigned char GetKey(void)
{
        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
        {
                DelayNmS(10);//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))//�ȴ������ͷ�
                        {
                        }
                        return '3';//���ذ���ֵ
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
        {
                DelayNmS(10);//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))//�ȴ������ͷ�
                        {
                        }
                        return '1';//���ذ���ֵ
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
        {
                DelayNmS(10);//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))//�ȴ������ͷ�
                        {
                        }
                        return '2';//���ذ���ֵ
                }
        }

        

        return NO_KEY;
}

void KeyTest(void)
{
        unsigned char i = 0;

        while(1)
        {
                i = GetKey();//����ɨ��
                if(NO_KEY != i)
                {
                        LedOutput(0,1);//��LEDָʾ
                        UART1SendByte(i);//���Ͱ���ֵ
                        DelayNmS(100);
                        LedOutput(0,0);
                }
        }
}
