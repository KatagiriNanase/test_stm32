#include "TIM5.h"

void Dri_TIM5_Init()
{
    //1.开启时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    //2.配置工作模式 PA1 复用推挽输出
    GPIOA->CRL |= GPIO_CRL_MODE1;
    GPIOA->CRL &= ~GPIO_CRL_CNF1_0;
    GPIOA->CRL |= GPIO_CRL_CNF1_1;

    //3.配置定时器
    //3.1预分频7199 得到10000hz
    TIM5->PSC = 7199;

    //3.2配置重装载值
    TIM5->ARR = 99;

    //配置向上计数
    TIM5->CR1 &= ~TIM_CR1_DIR;
    //3.3配置通道2工作模式 输出比较 PWM模式一(OC2M 110)
    TIM5->CCMR1 &= ~TIM_CCMR1_CC2S;
    TIM5->CCMR1 &= ~TIM_CCMR1_OC2M_0;
    TIM5->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);

    //3.4配置比较值 (占空比0%)
    TIM5->CCR2 = 0;

    //3.5开启比较使能
    TIM5->CCER |= TIM_CCER_CC2E;

}

void Dri_TIM5_Start()
{
    //1.开启计数器使能
    TIM5->CR1 |= TIM_CR1_CEN;
}

void Dri_TIM5_Stop()
{
    //关闭计数器使能
    TIM5->CR1 &= ~TIM_CR1_CEN;
}

void Dri_TIM5_SetDutyCycle(uint8_t dutycycle)
{
    TIM5->CCR2 = dutycycle;
}


