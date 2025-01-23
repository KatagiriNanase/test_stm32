#include "Dri_USART.h"

void Dri_USART_Init()
{
    //1.配置时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    //2.GPIO工作模式
    //PA9 USART_TX 复用推挽输出
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;

    //PA10 USART RX 浮空输入 
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;

    //3.串口配置
    //3.1 设置波特率
    USART1->BRR = 0x0271;

    //3.2 收发使能，模块使能
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

    //3.3 其他配置，设置数据帧格式
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR1 &= ~USART_CR1_PCE;
    USART1->CR2 &= ~USART_CR2_STOP;

}


void Dri_USART_SendChar(uint8_t ch)
{
    //轮询判断TXE是否为1
    while ((USART1->SR & USART_SR_TXE) == 0)
    {

    }

    //写入数据到DR
    USART1->DR = ch;

}

uint8_t Dri_USART_ReceiveChar()
{
    //轮询判断RXNE是否为1
    while ((USART1->SR & USART_SR_RXNE) == 0)
    {
        //添加判断空闲帧
        if (USART1->SR & USART_SR_IDLE)
            return 0;
    }

    //读取数据
    return USART1->DR;
}

void Dri_USART_SendString(uint8_t* str)
{
    for (uint8_t i = 0;str[i] != '\0'; ++i)
        Dri_USART_SendChar(str[i]);
}


void Dri_USART_ReceiveString(uint8_t buffer[])
{
    uint8_t i = 0;
    while ((USART1->SR & USART_SR_IDLE) == 0)
    {
        buffer[i] = Dri_USART_ReceiveChar();
        ++i;
    }
    //buffer[i] = 0;

    //清除IDLE位
    USART1->DR;


}

//重写fputc
int fputc(int ch, FILE* file)
{
    //直接发送字符到串口
    Dri_USART_SendChar(ch);
    return ch;
}