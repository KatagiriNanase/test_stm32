#include "Com_Util.h"
#include <stm32f10x.h>
//延时函数，微妙为单位，利用系统嘀嗒定时器，72MHz,一次嘀嗒 1/72us
void Com_Delay_us(uint16_t us)
{
    //1.装载计数值，72*us
    SysTick->LOAD = 72 * us;

    //2.配置，使用系统时钟(1)，计数结果不产生中断（0），使能开关（1）
    SysTick->CTRL |= 0x05;

    //3.等待计数器变为0，判断ctrl里的标志位countflag是否不为零
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0)
    {
        //如果变为1，就说明到时间了
        //并且我的定时器是要开着的，不然就直接跳出来
    }

    //4.关闭定时器
    //SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}

void Com_Delay_ms(uint16_t ms)
{
    while (ms--)
        Com_Delay_us(1000);
}

void Com_Delay_s(uint16_t s)
{
    while (s--)
        Com_Delay_ms(1000);
}
