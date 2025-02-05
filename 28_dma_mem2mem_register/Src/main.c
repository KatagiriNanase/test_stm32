#include "Dri_USART.h"
#include "Dri_DMA.h"

uint8_t isFinished = 0;

//定义全局常量，放置在ROM中，作为数据源
const uint8_t  src[] = { 10,20,30,40 };

//定义变量数组，用于存储接收来自ROM的数据
uint8_t des[4] = { 0 };
int main()
{
    Dri_USART_Init();
    Dri_DMA1_Init();
    //打印变量地址和常量地址
    printf("src=%p,des=%p\n", src, des);

    //开启通道DMA通道进行传输
    Dri_DMA1_Transmit((uint32_t)src, (uint32_t)des, (uint16_t)4);
    while (1)
    {
        if(isFinished)
        {
            for (uint8_t i = 0;i < 4;++i)
                printf("%d ", des[i]);
            printf("\n");
            isFinished = 0;
        }
    }
}