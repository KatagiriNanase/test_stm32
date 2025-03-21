#include "Int_LED.h"
#include "Com_Util.h"
#include "Dri_USART.h"
#include "rtc.h"
void enter_standbymode();
uint8_t flag = 0;


int main()
{
    Dri_USART_Init();
    Int_LED_Init();
    Dri_RTC_Init();
    Drt_RTC_SetALR(5);
    Int_LED_On(LED2);
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    printf("%d\n", flag);
    //判断标志位，如果唤醒标志位为1，就需要清除
    if (PWR->CSR & PWR_CSR_WUF)
    {
        printf("发生了唤醒事件！\n");
        PWR->CR |= PWR_CR_CWUF;
    }

    // 判断标志位，如果待机标志位为1，就需要清除
    if (PWR->CSR & PWR_CSR_SBF)
    {
        printf("从待机模式唤醒！\n");
        PWR->CR |= PWR_CR_CSBF;
    }
    //RTC->CRL &= ~RTC_CRL_ALRF;
    //printf("3秒后进入待机模式\n");
    Com_Delay_ms(3000);
    //printf("进入待机模式\n");
    Com_Delay_ms(1);
    enter_standbymode();
    while (1)
    {
        //printf("3秒后进入普通睡眠模式\n");
        // Com_Delay_ms(3000);
        // //printf("进入停机模式\n");
        // Com_Delay_ms(1);
        // printf("%d\n", RTC->CNTL);
        // Com_Delay_ms(500);
    }
}

void enter_standbymode()
{
    // 1. 设置深睡眠模式
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    // 3. 设置PDDS = 1，待机模式
    PWR->CR |= PWR_CR_PDDS;

    PWR->CR |= PWR_CR_CWUF;
    // 5. 进入待机模式，等待唤醒
    __WFI();
}

