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
        Com_Delay_ms(16);

    }
}