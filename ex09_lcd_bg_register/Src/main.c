#include "TIM3.h"
#include "TIM5.h"
#include "Int_LED.h"
#include "Com_Util.h"
#include "Key.h"
//全局状态 表示按键被按下
uint8_t isAdd = 0;
uint8_t isMinus = 0;

int main()
{
    Int_LED_Init();
    Int_Key_Init();
    Dri_TIM3_Init();
    Dri_TIM5_Init();
    //开启定时器
    Dri_TIM3_Start();
    Dri_TIM5_Start();
    //定义占空比
    uint8_t dutycycle = 0;

    while (1)
    {
        if (isAdd)
        {
            isAdd = 0;
            dutycycle = (dutycycle + 10 > 99) ? 99 : dutycycle + 10;
            Dri_TIM3_SetDutyCycle(dutycycle);
            Dri_TIM5_SetDutyCycle(dutycycle);
        }

        if (isMinus)
        {
            isMinus = 0;
            dutycycle = (dutycycle - 10 < 0) ? 0 : dutycycle - 10;
            Dri_TIM3_SetDutyCycle(dutycycle);
            Dri_TIM5_SetDutyCycle(dutycycle);
        }

    }
}