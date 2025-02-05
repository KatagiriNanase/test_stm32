#include "Dri_DMA.h"

//DMA初始化
void Dri_DMA1_Init()
{
    //1.配置时钟
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //2.配置传输模式 
    //2.1mem2mem
    DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM;

    //2.2通道优先级 最高
    DMA1_Channel1->CCR |= DMA_CCR1_PL;

    //2.3存储器数据宽度 00 八位
    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE;

    //2.4外设数据宽度
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE;

    //2.5数据传输方向 P->M
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;

    //2.6开启地址自增
    DMA1_Channel1->CCR |= (DMA_CCR1_PINC | DMA_CCR1_MINC);

    //2.7开启传输完成中断
    DMA1_Channel1->CCR |= DMA_CCR1_TCIE;

    //3.配置NVIC
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);


}

void Dri_DMA1_Transmit(uint32_t scrAddr, uint32_t desAddr, uint16_t dataLen)
{
    //1.设置存储器地址
    DMA1_Channel1->CMAR = desAddr;

    //2.设置外设地址
    DMA1_Channel1->CPAR = scrAddr;

    //3.设置数据长度
    DMA1_Channel1->CNDTR = dataLen;

    //4.开启通道使能
    DMA1_Channel1->CCR |= DMA_CCR1_EN;
}

extern uint8_t isFinished;
//中断服务程序
void DMA1_Channel1_IRQHandler()
{
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        //清除中断标志位
        DMA1->IFCR |= DMA_IFCR_CTCIF1;

        //关闭DMA通道
        DMA1_Channel1->CCR &= ~DMA_CCR1_EN;

        //置为标志位
        isFinished = 1;
    }

}

