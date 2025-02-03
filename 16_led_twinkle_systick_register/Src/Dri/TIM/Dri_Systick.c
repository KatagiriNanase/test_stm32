#include "Dri_Systick.h"

static uint16_t count = 0;

void Dri_Systick_Init()
{
    //1.设置重装载值
    SysTick->LOAD = 72000 - 1;//一毫秒产生中断
    //2.配置工作频率 72M
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;
    //3.开启中断使能
    SysTick->CTRL |= SysTick_CTRL_TICKINT;
    //4.开启定时器
    SysTick->CTRL |= SysTick_CTRL_ENABLE;
}

void SysTick_Handler()
{
    count++;
    if (count == 1000)
    {
        Int_LED_Toggle(LED2);
        count = 0;
    }
}
