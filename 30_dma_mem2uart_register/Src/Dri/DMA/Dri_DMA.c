#include "Dri_DMA.h"
#include <stdio.h>
//DMA初始化
void Dri_DMA1_Init()
{
    //1.配置时钟
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //2.配置传输模式 

    //2.2通道优先级 最高    
    DMA1_Channel4->CCR |= DMA_CCR4_PL;

    //2.3存储器数据宽度 00 八位
    DMA1_Channel4->CCR &= ~DMA_CCR4_MSIZE;

    //2.4外设数据宽度
    DMA1_Channel4->CCR &= ~DMA_CCR4_PSIZE;

    //2.5数据传输方向 M->P
    DMA1_Channel4->CCR |= DMA_CCR4_DIR;

    //2.6开启地址自增，串口地址不自增
    DMA1_Channel4->CCR |= DMA_CCR4_MINC;
    DMA1_Channel4->CCR &=~ DMA_CCR4_PINC;

    //2.7开启传输完成中断
    DMA1_Channel4->CCR |= DMA_CCR4_TCIE;

    //2.8开启串口DMA使能
    USART1->CR3 |= USART_CR3_DMAT;

    //3.配置NVIC
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel4_IRQn, 2);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);


}

void Dri_DMA1_Transmit(uint32_t scrAddr, uint32_t desAddr, uint16_t dataLen)
{
    //1.设置存储器地址
    DMA1_Channel4->CMAR = scrAddr;

    //2.设置外设地址
    DMA1_Channel4->CPAR = desAddr;

    //3.设置数据长度
    DMA1_Channel4->CNDTR = dataLen;

    //4.开启通道使能
    DMA1_Channel4->CCR |= DMA_CCR4_EN;
}

//中断服务程序
void DMA1_Channel4_IRQHandler()
{
    printf("into handler\n");
    if (DMA1->ISR & DMA_ISR_TCIF4)
    {
        //清除中断标志位
        DMA1->IFCR |= DMA_IFCR_CTCIF4;

        //关闭DMA通道
        DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
    }

}

