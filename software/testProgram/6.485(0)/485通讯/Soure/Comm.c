#include "Include.h"

//��PCͨ��UART1ͨѶ����������

//���׵�ͨѶЭ�飺
//PC�������
//'E' + 'S' + ����ȣ������ֳ��� + ���ݳ��ȣ� + ������ + ���ݣ�����еĻ��� + У��ͣ������ + ������ + ���ݣ�
//EasySTM32��Ӧ��
//'E' + 'S' + ��Ӧ���ȣ���Ӧ�ֳ��� + ���ݳ��ȣ� + ��Ӧ�� + ���ݣ�����еĻ��� + У��ͣ���Ӧ���� + ��Ӧ�� + ���ݣ�

#define COMMAND_MAX_NUMBER 10

#define COMMAND_TEST            0x01//��������
#define COMMAND_SET_RTC         0x11//����RTC����
#define COMMAND_READ_RTC        0x12//��ȡRTC����

extern void TimeToNumber(unsigned long* PNumber,struct StructTime* p);
extern void NumberToTime(unsigned long* PNumber,struct StructTime* p);

unsigned char ReCommandData[COMMAND_MAX_NUMBER];
unsigned char GetCommandData[COMMAND_MAX_NUMBER];

unsigned char GetCommand(unsigned char* p)
{
        unsigned char GetChar = 0;
        unsigned char Sum = 0;
        unsigned char Length = 0;
        unsigned int i = 0;

        while(1)
        {
                i++;
                if(i>10000)
                {
                        return 0;//��ʱ
                }

                if(UART1GetByte(&GetChar))
                {
                        if('E' == GetChar)
                        {
                                break;//�յ�'E'
                        }
                }
        }

        while(1)
        {
                i++;
                if(i>10000)
                {
                        return 0;//��ʱ
                }

                if(UART1GetByte(&GetChar))
                {
                        if('S' == GetChar)
                        {
                                break;//�յ�'S'
                        }
                }
        }

        while(1)
        {
                i++;
                if(i>10000)
                {
                        return 0;//��ʱ
                }

                if(UART1GetByte(&Length))
                {
                        Sum += Length;
                        *p = Length;
                        p++;
                        break;//���յ������
                }
        }

        for(;Length>0;Length--)
        {
                while(1)
                {
                        i++;
                        if(i>10000)
                        {
                                return 0;//��ʱ
                        }

                        if(UART1GetByte(&GetChar))
                        {
                                Sum += GetChar;
                                *p = GetChar;
                                p++;
                                break;//���յ������
                        }
                }
        }

        while(1)
        {
                i++;
                if(i>10000)
                {
                        return 0;//��ʱ
                }

                if(UART1GetByte(&GetChar))//����У���
                {
                        if(Sum == GetChar)
                        {
                                return 1;
                        }
                        return 0;
                }
        }
}

void AnswerCommand(unsigned char* p)
{
        unsigned char Sum = 0;
        unsigned char Length = 0;
        unsigned int i = 0;

        UART1SendByte('E');
        UART1SendByte('S');

        Length = *p;

        for(i=0;i<=Length;i++)
        {
                UART1SendByte(*p);
                Sum += *p;
                p++;
        }

        UART1SendByte(Sum);
}

//�����
//---------------------------------------------------------
//��������
void CommandTest(void)
{        
        ReCommandData[0] = 1;
        ReCommandData[1] = COMMAND_TEST;

        AnswerCommand(ReCommandData);
}

//����RTC
void CommandSetRTC(void)
{
        unsigned long RTCCounterValue;
        struct StructTime NowTime;

        NowTime.Year = GetCommandData[2];
        NowTime.Year = (NowTime.Year)<<8;
        NowTime.Year += GetCommandData[3];
        NowTime.Month = GetCommandData[4];
        NowTime.Day = GetCommandData[5];
        NowTime.Hour = GetCommandData[6];
        NowTime.Minute = GetCommandData[7];
        NowTime.Second = GetCommandData[8];
        NowTime.Week = GetCommandData[9];

        TimeToNumber(&RTCCounterValue,&NowTime);

        RTC_SetCounter(RTCCounterValue);

        ReCommandData[0] = 1;
        ReCommandData[1] = COMMAND_SET_RTC;
        AnswerCommand(ReCommandData);
}

//��ȡRTC
void CommandReadRTC(void)
{
        unsigned long RTCCounterValue;
        struct StructTime NowTime;

        RTCCounterValue = RTC_GetCounter();

        NumberToTime(&RTCCounterValue,&NowTime);//ת��Ϊʱ��

        ReCommandData[0] = 8;
        ReCommandData[1] = (NowTime.Year)>>8;
        ReCommandData[2] = NowTime.Year;
        ReCommandData[3] = NowTime.Month;
        ReCommandData[4] = NowTime.Day;
        ReCommandData[5] = NowTime.Hour;
        ReCommandData[6] = NowTime.Minute;
        ReCommandData[7] = NowTime.Second;
        ReCommandData[8] = NowTime.Week;

        AnswerCommand(ReCommandData);
}
//---------------------------------------------------------

void CommTest(void)
{
        unsigned char i = 0;

        while(1)
        {
                if(GetCommand(GetCommandData))
                {
                        switch (GetCommandData[1])
                        {
                                case COMMAND_TEST:
                                        CommandTest();
                                        break;
                                case COMMAND_SET_RTC:
                                        CommandSetRTC();
                                        break;
                                case COMMAND_READ_RTC:
                                        CommandReadRTC();
                                        break;
                                default:
                                        break;
                        }
                }
        }
        //������Ӧ�������
        while(1)
        {
                GetCommandData[0] = 2;
                GetCommandData[1] = 1;
                GetCommandData[2] = 3;
                AnswerCommand(GetCommandData);
                DelayNmS(1000);
        }

        //���Խ����������
        while(1)
        {
                if(GetCommand(GetCommandData))
                {
                        for(i=0;i<= GetCommandData[0];i++)
                        {
                                UART1SendByte(GetCommandData[i]);
                        }
                }
        }
}
