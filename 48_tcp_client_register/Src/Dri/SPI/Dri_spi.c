#include "Dri_spi.h"

//初始化
void Dri_SPI_Init()
{
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;

    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

    //2.配置工作模式
    //PC13 通用推挽输出
    GPIOD->CRL |= GPIO_CRL_MODE3;
    GPIOD->CRL &= ~GPIO_CRL_CNF3;

    //PB13 PB15:复用推挽输出
    GPIOB->CRH |= (GPIO_CRH_MODE13 | GPIO_CRH_MODE15);
    GPIOB->CRH |= (GPIO_CRH_CNF13_1 | GPIO_CRH_CNF15_1);
    GPIOB->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF15_0);


    //PB14 浮空输入
    GPIOB->CRH &= ~GPIO_CRH_MODE14;
    GPIOB->CRH &= ~GPIO_CRH_CNF14_1;
    GPIOB->CRH |= GPIO_CRH_CNF14_0;

    //3.SPI相关配置
    //3.1配置为主模式 
    SPI2->CR1 |= SPI_CR1_MSTR;
    //3.2配置为模式0 SCK拉高第一个上升沿采集
    SPI2->CR1 &= ~SPI_CR1_CPOL;
    SPI2->CR1 &= ~SPI_CR1_CPHA;

    //3.3配置分频系数 2 
    SPI2->CR1 &= ~SPI_CR1_BR;

    //3.4 先发高位
    SPI2->CR1 &= ~SPI_CR1_LSBFIRST;

    //3.5软件从设备管理
    SPI2->CR1 |= SPI_CR1_SSM;
    SPI2->CR1 |= SPI_CR1_SSI;

    //3.6 数据帧 8bit
    SPI2->CR1 &= ~SPI_CR1_DFF;

    //3.7 双向 （全双工）
    SPI2->CR1 &= ~SPI_CR1_BIDIMODE;

    //3.8开启SPI模块使能
    SPI2->CR1 |= SPI_CR1_SPE;



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
    //将数据写入发送缓冲区
    while (!(SPI2->SR & SPI_SR_TXE))
    {

    }
    SPI2->DR = byte;

    //接收缓冲区取数据
    while (!(SPI2->SR & SPI_SR_RXNE))
    {
        /* code */
    }
    return (uint8_t)(SPI2->DR & 0xff);

}