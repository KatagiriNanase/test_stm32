#include <stm32f10x.h>
#include "Int_LED.h"
#include "Com_Util.h"
int main()
{
    //LED初始化
    Int_LED_Init();

    //定义一个LED数组
    uint8_t size = 3;
    uint16_t leds[] = { LED1,LED2,LED3 };

    //全部关闭
    Int_LED_OffAll(leds, size);

    //依次打开
    while (1)
    {
        //正向遍历
        for (uint8_t i = 0;i < size;++i)
        {
            Int_LED_On(leds[i]);
            Com_Delay_ms(500);
            Int_LED_Off(leds[i]);
        }

        //反向遍历
        for(int8_t i=size-1;i>=0;--i)
        {
            Int_LED_On(leds[i]);
            Com_Delay_ms(500);
            Int_LED_Off(leds[i]);
        }
    }

}
