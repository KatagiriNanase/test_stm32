#include "TIM5.h"
#include "TIM4.h"
#include "Int_LED.h"
#include "Com_Util.h"
#include "Dri_USART.h"
#include "Dri_Systick.h"
uint8_t flag = 0;
int main()
{
    Int_LED_Init();
    Dri_TIM5_Init();
    Dri_TIM4_Init();
    Dri_USART_Init();
    Dri_Systick_Init();
    //开启定时器
    Dri_TIM5_Start();
    Dri_TIM4_Start();
    //定义占空比和变化方向
    uint8_t dutycycle = 0;
    uint8_t direction = 0;
    while (1)
    {
        if (dutycycle == 99)
            direction = 1;
        else if (dutycycle == 0)
            direction = 0;

        if (direction == 0)
            dutycycle++;
        else if (direction == 1)
            dutycycle--;

        Dri_TIM5_SetDutyCycle(dutycycle);
        //保持当前的占空比亮一会，太快切换了看不出亮度差
        if (flag)
        {
            flag = 0;
            printf("T= %.2f ms,f = %.2f hz,duty=%.2f %%\n",
                Dri_TIM4_GetPWMCycle(), Dri_TIM4_GetPWMFreq(), Dri_TIM4_GetPWMDutyCycle() * 100);
        }
        Com_Delay_ms(16);

    }
}