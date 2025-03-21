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
        printf("3������˯��ģʽ\n");
        Com_Delay_s(3);
        printf("����˯��ģʽ\n");
        enter_sleepmode();
        printf("������\n");
        Com_Delay_s(2);
    }
}


void enter_sleepmode()
{
    /* sleepģʽ */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP;

    /* ����WFIָ�� */
    __WFI();
}