#include "TIM3.h"

void Dri_TIM3_Init()
{
    //1.开启时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    //2.配置工作模式 PB0 复用推挽输出
    GPIOB->CRL |= GPIO_CRL_MODE0;
    GPIOB->CRL &= ~GPIO_CRL_CNF0_0;
    GPIOB->CRL |= GPIO_CRL_CNF0_1;

    //3.配置定时器
    //3.1预分频7199 得到10000hz
    TIM3->PSC = 7199;

    //3.2配置重装载值 每隔10ms溢出一次
    TIM3->ARR = 99;

    //配置向上计数
    TIM3->CR1 &= ~TIM_CR1_DIR;
    //3.3配置通道2工作模式 输出比较 PWM模式一(OC2M 110)
    TIM3->CCMR2 &= ~TIM_CCMR2_CC3S;
    TIM3->CCMR2 &= ~TIM_CCMR2_OC3M_0;
    TIM3->CCMR2 |= (TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2);

    //3.4配置比较值 (占空比50%)
    TIM3->CCR3 = 0;

    //3.5开启比较使能
    TIM3->CCER |= TIM_CCER_CC3E;

}

void Dri_TIM3_Start()
{
    //1.开启计数器使能
    TIM3->CR1 |= TIM_CR1_CEN;
}

void Dri_TIM3_Stop()
{
    //关闭计数器使能
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

void Dri_TIM3_SetDutyCycle(uint8_t dutycycle)
{
    TIM3->CCR3 = dutycycle;
}


