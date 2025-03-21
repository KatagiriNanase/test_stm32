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

    //3.4 中断使能
    USART1->CR1 |= (USART_CR1_RXNEIE | USART_CR1_IDLEIE);

    //4.NVIC配置
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);

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



void Dri_USART_SendString(uint8_t* str)
{
    for (uint8_t i = 0;str[i] != '\0'; ++i)
        Dri_USART_SendChar(str[i]);
}

//中断服务程序--接收字符串
void USART1_IRQHandler(void)
{
    if(USART1->SR&USART_SR_RXNE)
    {
        uint8_t rxChar = USART1->DR;
    }


}

int fputc(int ch,FILE* file)
{
    Dri_USART_SendChar((uint8_t)ch);
    return ch;
}

