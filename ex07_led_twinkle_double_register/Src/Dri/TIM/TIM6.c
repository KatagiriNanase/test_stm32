#include "TIM6.h"
#include <stdio.h>
void Dri_TIM6_Init()
{
    //1.开启TIM6时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    //2.配置预分频系数 周期T=0.1ms
    TIM6->PSC = 7200 - 1;

    //3.配置自动重装载值
    TIM6->ARR = 10000 - 1;

    //4.开启溢出中断使能
    TIM6->DIER |= TIM_DIER_UIE;

    //5.NVIC开启中断通道
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM6_IRQn, 3);
    NVIC_EnableIRQ(TIM6_IRQn);

    //6.开启定时器使能
    TIM6->CR1 |= TIM_CR1_CEN;


}
//判断是否第一次进中断
uint8_t isFirst = 0;
//中断服务程序
void TIM6_IRQHandler()
{
    printf("into TIM6\n");
    //清除中断标志位
    TIM6->SR &= ~TIM_SR_UIF;
    if (!isFirst)
    {
        isFirst = 1;
        return;
    }
    //翻转LED
    Int_LED_Toggle(LED2);
}
