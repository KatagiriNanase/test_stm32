#include "adc.h"

//初始化
void Dri_ADC1_Init()
{
    //1.RCC模块
    //1.1开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    //1.2配置分频系数 ADC预分频 6分频 72/6 =12M
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    //2.GPIO模块 PC0 模拟输入（不配也行） 
    GPIOC->CRL &= ~GPIO_CRL_MODE0;
    GPIOC->CRL &= ~GPIO_CRL_CNF0;

    //3.ADC配置 
    //3.1配置规则组输入通道为IN10 IN12 数量为2
    ADC1->SQR1 &= ~ADC_SQR1_L;
    ADC1->SQR1 |= ADC_SQR1_L_0;
    //IN10 第一位
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (10 << 0);
    //IN12 第二位
    ADC1->SQR3 &= ~ADC_SQR3_SQ2;
    ADC1->SQR3 |= (12 << 5);
    //3.2配置模式 扫描 列表循环
    ADC1->CR1 |= ADC_CR1_SCAN;
    ADC1->CR2 |= ADC_CR2_CONT;
    //3.3 数据右对齐
    ADC1->CR2 &= ~ADC_CR2_ALIGN;
    //3.4配置通道10采样时间 7.5周期采样一次
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP10;
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_0;

    ADC1->SMPR1 &= ~ADC_SMPR1_SMP12;
    ADC1->SMPR1 |= ADC_SMPR1_SMP12_0;

    //3.5选择软件触发AD转换
    // ADC1->CR2 |= ADC_CR2_EXTTRIG;
    // ADC1->CR2 |= ADC_CR2_EXTSEL;
    //3.4开启转换完成中断
    // ADC1->CR1 |= ADC_CR1_EOCIE;

    //4.配置NVIC
    // NVIC_SetPriorityGrouping(3);
    // NVIC_SetPriority(ADC1_2_IRQn, 2);
    // NVIC_EnableIRQ(ADC1_2_IRQn);


}




//开启转换
void Dri_ADC1_DMA_StartConvert(uint32_t des, uint16_t len)
{
    //0. DMA配置原地址，目的地址，数据长度
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR = des;
    DMA1_Channel1->CNDTR = len;
    DMA1_Channel1->CCR |= DMA_CCR1_EN;

    //1.上电唤醒
    ADC1->CR2 |= ADC_CR2_ADON;

    //2.执行校准
    ADC1->CR2 |= ADC_CR2_CAL;

    while (ADC1->CR2 & ADC_CR2_CAL)
    {
        //等待校准完成
    }
    //3.启动转换
    // ADC1->CR2 |= ADC_CR2_SWSTART;
    ADC1->CR2 |= ADC_CR2_ADON;

    while (!(ADC1->SR & ADC_SR_EOC))
    {
        //等待转换完成
    }
}

void Dri_ADC1_DMA_Init()
{
    //1.开启时钟
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //2.设置通道1传输方向 DIR=0
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;

    //3.数据传输宽度 16位
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_PSIZE_0;
    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_MSIZE_0;

    //4.地址自增 外设不增 内存地址自增
    DMA1_Channel1->CCR &= ~DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;

    //5.开启循环模式
    DMA1_Channel1->CCR |= DMA_CCR1_CIRC;

    //6.开启DMA模式
    ADC1->CR2 |= ADC_CR2_DMA;



}

