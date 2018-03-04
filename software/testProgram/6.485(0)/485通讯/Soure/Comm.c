#include "Include.h"

//和PC通过UART1通讯，接收命令

//简易的通讯协议：
//PC发出命令：
//'E' + 'S' + 命令长度（命令字长度 + 数据长度） + 命令字 + 数据（如果有的话） + 校验和（命令长度 + 命令字 + 数据）
//EasySTM32响应：
//'E' + 'S' + 响应长度（响应字长度 + 数据长度） + 响应字 + 数据（如果有的话） + 校验和（响应长度 + 响应字 + 数据）

#define COMMAND_MAX_NUMBER 10

#define COMMAND_TEST            0x01//测试命令
#define COMMAND_SET_RTC         0x11//设置RTC命令
#define COMMAND_READ_RTC        0x12//读取RTC命令

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
                        return 0;//超时
                }

                if(UART1GetByte(&GetChar))
                {
                        if('E' == GetChar)
                        {
                                break;//收到'E'
                        }
                }
        }

        while(1)
        {
                i++;
                if(i>10000)
                {
                        return 0;//超时
                }

                if(UART1GetByte(&GetChar))
                {
                        if('S' == GetChar)
                        {
                                break;//收到'S'
                        }
                }
        }

        while(1)
        {
                i++;
                if(i>10000)
                {
                        return 0;//超时
                }

                if(UART1GetByte(&Length))
                {
                        Sum += Length;
                        *p = Length;
                        p++;
                        break;//接收到命令长度
                }
        }

        for(;Length>0;Length--)
        {
                while(1)
                {
                        i++;
                        if(i>10000)
                        {
                                return 0;//超时
                        }

                        if(UART1GetByte(&GetChar))
                        {
                                Sum += GetChar;
                                *p = GetChar;
                                p++;
                                break;//接收到命令长度
                        }
                }
        }

        while(1)
        {
                i++;
                if(i>10000)
                {
                        return 0;//超时
                }

                if(UART1GetByte(&GetChar))//接收校验和
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

//命令处理
//---------------------------------------------------------
//测试命令
void CommandTest(void)
{        
        ReCommandData[0] = 1;
        ReCommandData[1] = COMMAND_TEST;

        AnswerCommand(ReCommandData);
}

//设置RTC
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

//读取RTC
void CommandReadRTC(void)
{
        unsigned long RTCCounterValue;
        struct StructTime NowTime;

        RTCCounterValue = RTC_GetCounter();

        NumberToTime(&RTCCounterValue,&NowTime);//转化为时间

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
        //测试响应命令情况
        while(1)
        {
                GetCommandData[0] = 2;
                GetCommandData[1] = 1;
                GetCommandData[2] = 3;
                AnswerCommand(GetCommandData);
                DelayNmS(1000);
        }

        //测试接收命令情况
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
