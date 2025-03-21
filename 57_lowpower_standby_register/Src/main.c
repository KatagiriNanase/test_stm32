#include "Key.h"
#include "Int_LED.h"
#include "Com_Util.h"
#include "Dri_USART.h"

void enter_standbymode();



int main()
{
    Dri_USART_Init();
    Int_LED_Init();
    Int_LED_On(LED2);
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    //判断标志位，如果唤醒标志位为1，就需要清除
    if (PWR->CSR & PWR_CSR_WUF)
    {
        printf("发生了唤醒事件！\n");
    }

    // 判断标志位，如果待机标志位为1，就需要清除
    if (PWR->CSR & PWR_CSR_SBF)
    {
        printf("从待机模式唤醒！\n");
        PWR->CR |= PWR_CR_CSBF;
    }

    printf("3秒后进入待机模式\n");
    Com_Delay_ms(3000);
    printf("进入待机模式\n");
    Com_Delay_ms(1);
    enter_standbymode();
    while (1)
    {
        printf("3秒后进入普通睡眠模式\n");
        Com_Delay_ms(3000);
        printf("进入停机模式\n");
        Com_Delay_ms(1);

    }
}

void enter_standbymode()
{
    // 1. 设置深睡眠模式
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    // 3. 设置PDDS = 1，待机模式
    PWR->CR |= PWR_CR_PDDS;

    // 4. 使能WKUP唤醒引脚
    PWR->CSR |= PWR_CSR_EWUP;

    PWR->CR |= PWR_CR_CWUF;
    // 5. 进入待机模式，等待唤醒
    __WFI();
}

