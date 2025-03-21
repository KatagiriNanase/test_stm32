#include "Dri_USART.h"
#include "Com_Util.h"
#include "Int_LED.h"

void enter_sleepmode();

int main()
{

    Dri_USART_Init();
    Int_LED_Init();
    Int_LED_On(LED3);
    while (1)
    {
        printf("3秒后进入睡眠模式\n");
        Com_Delay_s(3);
        printf("进入睡眠模式\n");
        enter_sleepmode();
        printf("被唤醒\n");
        Com_Delay_s(2);
    }
}


void enter_sleepmode()
{
    /* sleep模式 */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP;

    /* 发送WFI指令 */
    __WFI();
}