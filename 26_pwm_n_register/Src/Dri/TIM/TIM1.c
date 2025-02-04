#include "TIM1.h"
#include <stm32f10x.h>


void Dri_TIM1_Init()
{
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    //2.配置工作模式 PA6 复用输出 
    GPIOA->CRH |= GPIO_CRH_MODE8;
    GPIOA->CRH |= GPIO_CRH_CNF8_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;

    //3.时基部分
    //3.1预分频71 得到10000hz T=0.1ms
    TIM1->PSC = 7199;

    //3.2配置重装载值 500/0.1=5000
    TIM1->ARR = 4999;

    //3.3配置重复计数次数
    TIM1->RCR = 4;
    //配置向上计数
    TIM1->CR1 &= ~TIM_CR1_DIR;

    //4配置通道1
    //4.1配置通道1工作模式 输出比较 PWM模式1（110）
    TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2;
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;

    //4.2配置占空比
    TIM1->CCR1 = 2500;

    //4.3配置极性
    TIM1->CCER &= ~TIM_CCER_CC1P;

    //4.4开启OC1使能，关闭互补使能
    TIM1->CCER |= TIM_CCER_CC1E;

    //4.5开启主输出使能
    TIM1->BDTR |= TIM_BDTR_MOE;

    //4.6 产生一个更新事件，将PSC的值和REP的值载入影子寄存器
    TIM1->EGR |= TIM_EGR_UG;
    //5中断功能
    //5.1开启中断
    TIM1->DIER |= TIM_DIER_UIE;

    //5.2NVIC配置
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM1_UP_IRQn, 3);
    NVIC_EnableIRQ(TIM1_UP_IRQn);

}

void Dri_TIM1_Start()
{
    //1.开启计数器使能
    TIM1->CR1 |= TIM_CR1_CEN;
}

void Dri_TIM1_Stop()
{
    //关闭计数器使能
    TIM1->CR1 &= ~TIM_CR1_CEN;
}

void TIM1_UP_IRQHandler()
{
    printf("into handler\n");
    //清除中断标志位
    TIM1->SR &= ~TIM_SR_UIF;

    //停用定时器
    Dri_TIM1_Stop();
}