#include "Include.h"

//音调表
//C 523 
//D 587 
//E 659 
//F 698 
//G 784 
//A 880 
//B 988 

const unsigned int MusicData[7] = {30592,27257,24297,22922,20408,18182,16194};

void SetBellF(unsigned int SetV)
{
        TIM_OCInitTypeDef TIM_OCInitStructure;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        
        TIM_TimeBaseInitStructure.TIM_Period = SetV;
        TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse = (SetV/2);
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
        TIM_OC2Init(TIM2, &TIM_OCInitStructure);
}


void Timer2Init(void)
{
        TIM_OCInitTypeDef TIM_OCInitStructure;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        
        TIM_TimeBaseInitStructure.TIM_Period = 10000;
        TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse = 5000;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
        TIM_OC2Init(TIM2, &TIM_OCInitStructure);
}

void Timer2OutEnable(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Timer2OutDisable(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Timer2Start(void)
{
        TIM_Cmd(TIM2, ENABLE);
}

void Timer2Stop(void)
{
        TIM_Cmd(TIM2, DISABLE);
}

void Timer2Test(void)
{
        unsigned char i = 0;

        Timer2Start();

        //一句简单的歌曲
        while(1)
        {
                Timer2OutEnable();
                SetBellF(MusicData[0]);
                DelayNmS(400);
                SetBellF(MusicData[0]);
                DelayNmS(400);
                SetBellF(MusicData[4]);
                DelayNmS(400);
                SetBellF(MusicData[4]);
                DelayNmS(400);
                SetBellF(MusicData[5]);
                DelayNmS(400);
                SetBellF(MusicData[5]);
                DelayNmS(400);
                SetBellF(MusicData[4]);
                DelayNmS(400);
                DelayNmS(400);
                SetBellF(MusicData[3]);
                DelayNmS(400);
                SetBellF(MusicData[3]);
                DelayNmS(400);
                SetBellF(MusicData[2]);
                DelayNmS(400);
                SetBellF(MusicData[2]);
                DelayNmS(400);
                SetBellF(MusicData[1]);
                DelayNmS(400);
                SetBellF(MusicData[1]);
                DelayNmS(400);
                SetBellF(MusicData[0]);
                DelayNmS(400);
                DelayNmS(400);
                Timer2OutDisable();
                DelayNmS(1000);
        }

        //从C播放到B
        while(1)
        {
                SetBellF(MusicData[i]);
                Timer2OutEnable();
                DelayNmS(200);
                i++;
                if(i>=7)
                {
                        i = 0;
                        Timer2OutDisable();
                        DelayNmS(2000);
                }
        }
}
