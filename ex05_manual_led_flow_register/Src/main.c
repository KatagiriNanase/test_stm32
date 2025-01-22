#include "Key.h"
#include "Int_LED.h"
#include "Com_Util.h"
//定义全局变量，表示当前流水灯状态
FLOW_STATUS flow_status = No_LED;
uint16_t leds[] = { LED1,LED2,LED3 };

int main()
{

    Int_LED_Init();
    Int_Key_Init();


    while (1)
    {
        switch (flow_status)
        {
        case L1:
            Int_LED_Off(LED3);
            Int_LED_On(LED1);
            break;
        case L2:
            Int_LED_Off(LED1);
            Int_LED_On(LED2);
            break;
        case L3:
            Int_LED_Off(LED2);
            Int_LED_On(LED3);
            break;
        default:
            break;
        }
    }
}

