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
    //3.3配置通道1工作模式 输入捕获 直接映射CC4S（01） 不滤波ICF34（00）不分频
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;

    TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;
    TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC;

    //配置通道2 输入捕获 映射到TI1 下降沿检测   不滤波ICF34（00）不分频 下沿触发
    TIM4->CCMR1 |= TIM_CCMR1_CC2S_1;
    TIM4->CCMR1 &= ~TIM_CCMR1_CC2S_0;

    TIM4->CCMR1 &= ~TIM_CCMR1_IC2F;
    TIM4->CCMR1 &= ~TIM_CCMR1_IC2PSC;

    TIM4->CCER |= TIM_CCER_CC2P;


    //4.配置触发器控制器为从模式 
    //4.1（复位模式）
    TIM4->SMCR |= TIM_SMCR_SMS_2;
    TIM4->SMCR &= ~TIM_SMCR_SMS_1;
    TIM4->SMCR &= ~TIM_SMCR_SMS_0;

    //4.2触发来源 TS TI1的边沿检测器
    TIM4->SMCR |= TIM_SMCR_TS_2;
    TIM4->SMCR &= ~TIM_SMCR_TS_1;
    TIM4->SMCR |= TIM_SMCR_TS_0;

    //5开启捕获使能
    TIM4->CCER |= TIM_CCER_CC1E;
    TIM4->CCER |= TIM_CCER_CC2E;
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


double Dri_TIM4_GetPWMDutyCycle()
{
    return TIM4->CCR2 * 1.0 / TIM4->CCR1;
}

