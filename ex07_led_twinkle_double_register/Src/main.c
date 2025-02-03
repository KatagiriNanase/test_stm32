#include "TIM6.h"
#include "Dri_Systick.h"
#include <stdio.h>
#include "Dri_USART.h"
int main()
{
    Dri_USART_Init();
    printf("usart init successfully\n");
    Int_LED_Init();
    Dri_TIM6_Init();
    Dri_Systick_Init();
    while (1)
    {

    }
}