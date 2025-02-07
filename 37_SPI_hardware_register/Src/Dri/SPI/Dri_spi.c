#include "Dri_spi.h"

//初始化
void Dri_SPI_Init()
{
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    //2.配置工作模式
    //PC13 通用推挽输出
    GPIOC->CRH |= GPIO_CRH_MODE13;
    GPIOC->CRH &= ~GPIO_CRH_CNF13;

    //PA5 PA7:复用推挽输出
    GPIOA->CRL |= (GPIO_CRL_MODE7 | GPIO_CRL_MODE5);
    GPIOA->CRL |= (GPIO_CRL_CNF5_1 | GPIO_CRL_CNF7_1);
    GPIOA->CRL &= ~(GPIO_CRL_CNF5_0 | GPIO_CRL_CNF7_0);


    //PA6 浮空输入
    GPIOA->CRL &= ~GPIO_CRL_MODE6;
    GPIOA->CRL &= ~GPIO_CRL_CNF6_1;
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    //3.SPI相关配置
    //3.1配置为主模式 
    SPI1->CR1 |= SPI_CR1_MSTR;
    //3.2配置为模式0 SCK拉高第一个上升沿采集
    SPI1->CR1 &= ~SPI_CR1_CPOL;
    SPI1->CR1 &= ~SPI_CR1_CPHA;

    //3.3配置分频系数 4 
    SPI1->CR1 &= ~SPI_CR1_BR_2;
    SPI1->CR1 &= ~SPI_CR1_BR_1;
    SPI1->CR1 |= SPI_CR1_BR_0;

    //3.4 先发高位
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

    //3.5软件从设备管理
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR1 |= SPI_CR1_SSI;

    //3.6 数据帧 8bit
    SPI1->CR1 &= ~SPI_CR1_DFF;

    //3.7 双向 （全双工）
    SPI1->CR1 &= ~SPI_CR1_BIDIMODE;

    //3.8开启SPI模块使能
    SPI1->CR1 |= SPI_CR1_SPE;



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
    while (!(SPI1->SR & SPI_SR_TXE))
    {

    }
    SPI1->DR = byte;

    //接收缓冲区取数据
    while (!(SPI1->SR & SPI_SR_RXNE))
    {
        /* code */
    }
    return (uint8_t)(SPI1->DR & 0xff);

}