#include "TIM1.h"
#include "Dri_USART.h"
int main()
{
    Dri_USART_Init();
    Dri_TIM1_Init();
    //开启定时器
    Dri_TIM1_Start();
    printf("hello world!\n");
    //定义占空比和变化方向
    while (1)
    {
        //保持当前的占空比亮一会，太快切换了看不出亮度差

    }
}