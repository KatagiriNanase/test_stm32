#include "TIM4.h"
#include <stm32f10x.h>


void Dri_TIM4_Init()
{
    //1.开启时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    //2.配置工作模式 PB6 浮空输入 CNF(01)
    GPIOB->CRL &= ~GPIO_CRL_MODE6;
    GPIOB->CRL &= ~GPIO_CRL_CNF6_1;
    GPIOB->CRL |= GPIO_CRL_CNF6_0;

    //3.配置定时器
    //3.1预分频71 得到1Mhz
    TIM4->PSC = 71;

    //3.2配置重装载值 装满，在信号一个周期内尽量不要产生溢出
    TIM4->ARR = 65535;

    //配置向上计数
    TIM4->CR1 &= ~TIM_CR1_DIR;

    //选择输入通道
    TIM4->CR2 &= ~TIM_CR2_TI1S;
    //3.3配置通道2工作模式 输入捕获 直接映射CC4S（01） 不滤波ICF34（00）不分频
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;

    TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;
    TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC;
    //3.4配置捕获值初始为0
    TIM4->CCR1 = 0;

    //3.5开启捕获使能
    TIM4->CCER |= TIM_CCER_CC1E;

    //3.6开启捕获中断使能
    TIM4->DIER |= TIM_DIER_CC1IE;

    //3.7 NVIC配置
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM4_IRQn, 3);
    NVIC_EnableIRQ(TIM4_IRQn);

}

void Dri_TIM4_Start()
{
    //1.开启计数器使能
    TIM4->CR1 |= TIM_CR1_CEN;
}

void Dri_TIM4_Stop()
{
    //关闭计数器使能
    TIM4->CR1 &= ~TIM_CR1_CEN;
}

// //定义全局变量
// uint16_t cycle = 0;     //保存CCR的捕获值
// uint8_t count = 0;      //当前上升沿到来的次数


// double Dri_TIM4_GetPWMCycle()
// {
//     return cycle / 1000.0;
// }

// double Dri_TIM4_GetPWMFreq()
// {
//     return 1000000.0 / cycle;
// }

// void TIM4_IRQHandler()
// {
//     //判断是否为通道一产生的捕获中断
//     if (TIM4->SR & TIM_SR_CC1IF)
//     {
//         //软件清除标志位
//         TIM4->SR &= ~TIM_SR_CC1IF;
//         count++;
//         //上升沿第一次来，清零CNT
//         if (count == 1)
//             TIM4->CNT = 0;
//         //上升沿第二次来，读取CNT返回计数
//         else if (count == 2)
//         {
//             cycle = TIM4->CNT;
//             count = 0;
//         }
//     }
// }

//获取输入信号周期
double Dri_TIM4_GetPWMCycle()
{
    return TIM4->CCR1 / 1000.0;
}

//获取输入信号频率
double Dri_TIM4_GetPWMFreq()
{
    return 1000000.0 / TIM4->CCR1;
}

void TIM4_IRQHandler()
{
    if(TIM4->SR&TIM_SR_CC1IF)
    {
        //清除标志位
        TIM4->SR &= ~TIM_SR_CC1IF;
        //清除CNT重新计数
        TIM4->CNT = 0;
    }
}