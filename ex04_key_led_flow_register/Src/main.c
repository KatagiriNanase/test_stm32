#include "Key.h"
#include "Int_LED.h"
#include "Com_Util.h"
uint8_t isOn = 0;
uint16_t leds[] = { LED1,LED2,LED3 };

int main()
{

    Int_LED_Init();
    Int_Key_Init();

    
    while (1)
    {
        //流水灯
        for (uint8_t i = 0;i < 3;++i)
        {
            if (!isOn)
                break;
            Int_LED_On(leds[i]);
            Com_Delay_ms(500);
            Int_LED_Off(leds[i]);
        }
    }
}
