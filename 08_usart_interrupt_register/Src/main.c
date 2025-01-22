#include "Dri_USART.h"
#include "Com_Util.h"
#include "Int_LED.h"
uint8_t buffer[100] = { 0 };
uint8_t size = 0;
//定义标志位
uint8_t isOver = 0;
int main()
{

    Dri_USART_Init();
    Int_LED_Init();

    while (1)
    {
        if (isOver)
        {
            Dri_USART_SendString(buffer);
            isOver = 0;
        }
    }
}