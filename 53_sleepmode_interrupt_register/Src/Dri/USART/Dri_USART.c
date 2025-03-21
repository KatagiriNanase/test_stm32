#include "Dri_USART.h"


void Dri_USART_Init()
{
    //1.����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    //2.GPIO����ģʽ
    //PA9 USART_TX �����������
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;

    //PA10 USART RX �������� 
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;

    //3.��������
    //3.1 ���ò�����
    USART1->BRR = 0x0271;

    //3.2 �շ�ʹ�ܣ�ģ��ʹ��
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

    //3.3 �������ã���������֡��ʽ
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR1 &= ~USART_CR1_PCE;
    USART1->CR2 &= ~USART_CR2_STOP;

    //3.4 �ж�ʹ��
    USART1->CR1 |= (USART_CR1_RXNEIE | USART_CR1_IDLEIE);

    //4.NVIC����
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);

}


void Dri_USART_SendChar(uint8_t ch)
{
    //��ѯ�ж�TXE�Ƿ�Ϊ1
    while ((USART1->SR & USART_SR_TXE) == 0)
    {

    }

    //д�����ݵ�DR
    USART1->DR = ch;

}



void Dri_USART_SendString(uint8_t* str)
{
    for (uint8_t i = 0;str[i] != '\0'; ++i)
        Dri_USART_SendChar(str[i]);
}

//�жϷ������--�����ַ���
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

