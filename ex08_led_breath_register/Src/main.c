#include "TIM5.h"
#include "Int_LED.h"
#include "Com_Util.h"
int main()
{
    Int_LED_Init();
    Dri_TIM5_Init();
    //开启定时器
    Dri_TIM5_Start();
    //定义占空比和变化方向
    uint8_t dutycycle = 0;
    int8_t step = -1;
    while (1)
    {
        if (dutycycle <= 0 || dutycycle >= 99)
            step = -step;
        dutycycle += step;

        Dri_TIM5_SetCH2DutyCycle(dutycycle);
        Dri_TIM5_SetCH1DutyCycle(100 - dutycycle);

        //保持当前的占空比亮一会，太快切换了看不出亮度差
        Com_Delay_ms(16);

    }
}