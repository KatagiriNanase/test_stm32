#include "Dri_spi.h"

//初始化
void Dri_SPI_Init()
{
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    //2.配置工作模式
    //PA5  PA7 PC13 通用推挽输出
    GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_MODE7);
    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_CNF7);
    GPIOC->CRH |= GPIO_CRH_MODE13;
    GPIOC->CRH &= ~GPIO_CRH_CNF13;

    //PA6 浮空输入
    GPIOA->CRL &= ~GPIO_CRL_MODE6;
    GPIOA->CRL &= ~GPIO_CRL_CNF6_1;
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    //3.选择SPI工作模式0：SCK空闲0 
    SCK_LOW;

    //4.片选不使能
    CS_HIGH;

    //5.延时 保证SCKlow一段时间
    SPI_DELAY;
}

//数据传输的开始
void Dri_SPI_Start()
{
    CS_LOW;
}

//数据传输的结束
void Dri_SPI_Stop()
{
    CS_HIGH;
}

//主从设备交换一个字节的数据
uint8_t Dri_SPI_SwapByte(uint8_t byte)
{
    //接收字节变量
    uint8_t rByte = 0x00;

    //用循环依次交换八位数据
    for (uint8_t i = 0;i < 8;++i)
    {
        //1.准备发送的数据，送到MOSI
        if (byte & 0x80)
            MOSI_HIGH;
        else
            MOSI_LOW;
        //左移一位
        byte <<= 1;

        //2.拉高时钟信号
        SCK_HIGH;
        SPI_DELAY;

        //3.读取MISO
        rByte <<= 1;
        if (MISO_READ)
            rByte |= 0x01;

        //4.拉低时钟
        SCK_LOW;
        SPI_DELAY;
    }

    //5.返回数据
    return rByte;
}