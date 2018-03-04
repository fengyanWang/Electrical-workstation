#include "Include.h"

//ʱ���2000��1��1�տ�ʼ
struct StructTime NowTime;

#define START_WEEK 6//2000��1��1����6     0��ʾ����
#define START_YEAR 2000//2000�꿪ʼ

//�ж��Ƿ������꣬2100�����
//�Ƿ�������
const unsigned char IfRun[100] =
{
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
        1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0
};

const unsigned int DayPerYear[2] = {365,366};

const unsigned char DayPerMonth[2][12] =
{
        31,28,31,30,31,30,31,31,30,31,30,31,
        31,29,31,30,31,30,31,31,30,31,30,31//����
};

const unsigned long SecondPerMinute = 60;//1����=60��
const unsigned long SecondPerHour = 60*60;//1Сʱ=60����
const unsigned long SecondPerDay = 60*60*24;//1��=24Сʱ
//ʱ��ת��������
void TimeToNumber(unsigned long* PNumber,struct StructTime* p)
{
        unsigned char Year = 0;
        unsigned char Month = 0;
        unsigned char Day = 0;
        unsigned long DayNumber = 0;
        unsigned int i = 0;
        unsigned long t = 0;

        Year = p->Year - START_YEAR;
        Month = p->Month - 1;
        Day = p->Day - 1;

        if(Year>0)
        {
                for(i=0;i<Year;i++)
                {
                        DayNumber += DayPerYear[IfRun[i]];
                }
        }

        if(Month>0)
        {
                for(i=0;i<Month;i++)
                {
                        DayNumber += DayPerMonth[IfRun[Year]][i];
                }
        }

        DayNumber += Day;

        //-------------------------------------------------

        t = DayNumber*SecondPerDay;
        t += (p->Hour)*SecondPerHour;
        t += (p->Minute)*SecondPerMinute;
        t += (p->Second);

        *PNumber = t;

        return;
}

//����ת����ʱ��
void NumberToTime(unsigned long* PNumber,struct StructTime* p)
{
        unsigned long i = 0;
        unsigned long t = 0;
        unsigned long Day = 0;
        unsigned char Year = 0;
        unsigned char Month = 0;

        //����ȷ������
        Day = *PNumber/SecondPerDay;

        //-------------------------------------------------
        i = Day;
        //ȷ������
        i = (i + START_WEEK)%7;
        p->Week = i;

        //ȷ��Сʱ��
        i = *PNumber%SecondPerDay;
        t = i/SecondPerHour;
        p->Hour = t;

        //ȷ��������
        i = i%SecondPerHour;
        t = i/SecondPerMinute;
        p->Minute = t;

        //ȷ������
        i = i%SecondPerMinute;
        p->Second = i;

        //-------------------------------------------------

        //�ж�����
        t = 0;
        for(i=0;i<100;i++)
        {
                t += DayPerYear[IfRun[i]];
                if(t>Day)
                {
                        break;
                }
        }

        Year = i;
        p->Year = Year+START_YEAR;

        //�ж��·�
        for(i=0;i<Year;i++)
        {
                Day = Day - DayPerYear[IfRun[i]];
        }
        
        t = 0;
        for(i=0;i<12;i++)
        {
                t += DayPerMonth[IfRun[Year]][i];
                if(t>Day)
                {
                        break;
                }
        }

        Month = i;
        p->Month = Month + 1;

        //�ж���
        for(i=0;i<Month;i++)
        {
                Day = Day - DayPerMonth[IfRun[Year]][i];
        }

        p->Day = Day + 1;
        
}

void RTCInit(void)
{
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        PWR_BackupAccessCmd(ENABLE);

        if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
        {
                RCC_LSEConfig(RCC_LSE_ON);
                while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
                {
                }
                RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
        
                RCC_RTCCLKCmd(ENABLE);
        
                //Output
                BKP_TamperPinCmd(DISABLE);
                //BKP_RTCOutputConfig(ENABLE);
                BKP_RTCOutputConfig(DISABLE);
        
                RTC_WaitForSynchro();
                RTC_WaitForLastTask();

                //����ʱ�� 
                RTC_SetCounter(0);

                BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);    
        }
}

void RTCTest(void)
{
        unsigned long RTCCounterValue;

        while(1)
        {
                RTCCounterValue = RTC_GetCounter();

                UART1SendByte(RTCCounterValue>>24);
                UART1SendByte(RTCCounterValue>>16);
                UART1SendByte(RTCCounterValue>>8);
                UART1SendByte(RTCCounterValue);

                DelayNmS(1000);
        }
}


