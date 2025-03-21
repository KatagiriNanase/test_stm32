#include "Key.h"
#include "Com_Util.h"
#include "Int_LED.h"

uint16_t leds[] = { LED1,LED2,LED3 };

void Int_Key_Init()
{
    //1.配置时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    //2.GPIO工作模式，PF10，CNF上下拉（10），MODE输入模式（00）
    GPIOF->CRH &= ~GPIO_CRH_CNF10_0;
    GPIOF->CRH |= GPIO_CRH_CNF10_1;
    GPIOF->CRH &= ~GPIO_CRH_MODE10;
    //默认给低电平
    GPIOF->ODR &= ~GPIO_ODR_ODR10;

    //3.AFIO引脚复用选择 PF(0101)
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PF;

    //4.EXTI配置
    EXTI->RTSR |= EXTI_RTSR_TR10;
    EXTI->IMR |= EXTI_IMR_MR10;

    //5.NVIC配置
    NVIC_SetPriorityGrouping(3);//全部是抢占优先级
    NVIC_SetPriority(EXTI15_10_IRQn, 3);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

//中断服务程序
void EXTI15_10_IRQHandler(void)
{
    //清除中断挂起标志位
    EXTI->PR |= EXTI_PR_PR10;

    //防抖延时
    Com_Delay_ms(10);

    //判断是否仍为高电平
    if ((GPIOF->IDR & GPIO_IDR_IDR10) != 0)
    {
        printf("%d\n", BKP->DR1);
    }
}
