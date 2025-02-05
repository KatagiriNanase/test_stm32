#include "Dri_USART.h"
#include "Dri_DMA.h"
#include "Com_Util.h"

//放置在RAM中，作为数据源
uint8_t  src[] = { 'a','b','c','d' };


int main()
{
    Dri_USART_Init();
    Dri_DMA1_Init();
    //打印变量地址和常量地址
    printf("hello world!\n");
    Com_Delay_ms(10);
    //开启通道DMA通道进行传输
    Dri_DMA1_Transmit((uint32_t)src, (uint32_t) & (USART1->DR), 4);
    while (1)
    {

    }
}