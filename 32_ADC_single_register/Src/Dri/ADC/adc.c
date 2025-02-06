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
    //3.1配置规则组输入通道为IN10 数量为1
    ADC1->SQR1 &= ~ADC_SQR1_L;
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (10 << 0);
    //3.2配置模式 不扫描 循环
    ADC1->CR1 &= ~ADC_CR1_SCAN;
    ADC1->CR2 |= ADC_CR2_CONT;
    //3.3 数据右对齐
    ADC1->CR2 &= ~ADC_CR2_ALIGN;
    //3.4配置通道10采样时间 7.5周期采样一次
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP10;
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_0;

    //3.5选择软件触发AD转换
    ADC1->CR2 |= ADC_CR2_EXTTRIG;
    ADC1->CR2 |= ADC_CR2_EXTSEL;
    //3.4开启转换完成中断
    // ADC1->CR1 |= ADC_CR1_EOCIE;

    //4.配置NVIC
    // NVIC_SetPriorityGrouping(3);
    // NVIC_SetPriority(ADC1_2_IRQn, 2);
    // NVIC_EnableIRQ(ADC1_2_IRQn);


}

//开启转换
void Dri_ADC1_StartConvert()
{
    //1.上电唤醒
    ADC1->CR2 |= ADC_CR2_ADON;

    //2.执行校准
    ADC1->CR2 |= ADC_CR2_CAL;

    while (ADC1->CR2 & ADC_CR2_CAL)
    {
        //等待校准完成
    }
    //3.启动转换
    ADC1->CR2 |= ADC_CR2_SWSTART;

    while (!(ADC1->SR & ADC_SR_EOC))
    {
        //等待转换完成
    }
}

//返回转换后的模拟电压值
double Dri_ADC1_ReadV()
{
    return ADC1->DR * 3.3 / 4095;
}