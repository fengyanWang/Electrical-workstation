#include "Include.h"

#define SET_595CS {GPIO_SetBits(GPIOB, GPIO_Pin_5);} 
#define CLR_595CS {GPIO_ResetBits(GPIOB, GPIO_Pin_5);}

const unsigned char DisplayData[] =
{
        0xFA,0xC0,0x76,0xF4,0xCC,0xBC,0xBE,0xD0,0xFE,0xFC,0
};

void Led8IOInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        SET_595CS
}

void SPIInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        SPI_InitTypeDef SPI_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);//使能SPI1时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_CRCPolynomial = 7;
        SPI_Init(SPI1, &SPI_InitStructure);

        SPI_Cmd(SPI1, ENABLE);//使能SPI1

        Led8IOInit();

        DisplayNumber(0xFF);
}

unsigned char SPI1Action(unsigned char SendData)
{
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
        SPI_I2S_SendData(SPI1,SendData); 
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET);
        return(SPI_I2S_ReceiveData(SPI1));
}

void DisplayNumber(unsigned char Number)
{
        if(Number>10)
        {
                Number = 10;
        }

        CLR_595CS
        SPI1Action(DisplayData[Number]);
        SET_595CS
}

void SPITest(void)
{
        unsigned char i = 0;

        Led8IOInit();

        while(1)
        {
                DisplayNumber(i);
                i++;
                if(i>10)
                {
                        i = 0;
                }
                DelayNmS(200);
        }

        while(1)
        {
                CLR_595CS
                SPI1Action(0x55);
                SET_595CS
                DelayNmS(200);
        }
}
