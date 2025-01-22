#include "Dri_USART.h"
#include "Com_Util.h"
#include "Int_LED.h"
uint8_t buffer[100] = { 0 };
int main()
{

    Dri_USART_Init();
    Int_LED_Init();

    while (1)
    {
        //发送字符
        /*Dri_USART_SendChar('x');
        Dri_USART_SendChar('\n');
        Int_LED_On(LED3);
        Com_Delay_ms(20);
        Int_LED_Off(LED3);
        Com_Delay_s(2);
        */

        //接收字符，再发回来
        // ch = Dri_USART_ReceiveChar();
        // Dri_USART_SendChar(ch);
        // Int_LED_On(LED3);
        // Com_Delay_ms(20);
        // Int_LED_Off(LED3);

        //接受a，点亮LED1
        // ch = Dri_USART_ReceiveChar();
        // if (ch == 'a')
        //     Int_LED_Toggle(LED1);
        // else if (ch == 'b')
        //     Int_LED_Toggle(LED2);
        // else if (ch == 'c')
        //     Int_LED_Toggle(LED3);

        //发送字符串
        // Dri_USART_SendString("hello,world!\n");
        // Com_Delay_s(2);
        // Int_LED_On(LED3);
        // Com_Delay_ms(20);
        // Int_LED_Off(LED3);
        Dri_USART_ReceiveString(buffer);
        Dri_USART_SendString(buffer);
    }
}