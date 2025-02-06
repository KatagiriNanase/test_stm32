#include "Dri_USART.h"
#include "ADC.h"
#include "Com_Util.h"
//定义变量数组，用于存储接收来自ROM的数据
int main()
{
    Dri_USART_Init();
    Dri_ADC1_Init();
    //打印变量地址和常量地址
    printf("===== ?^?ω?^? ADC电压捕捉实验启动 =====\n"
        "| 固件版本: V1.0 喵爪稳定版\n"
        "| 当前采样周期: 7.5*12M Hz\n"
        "| 目标通道: ADC_IN10 (对应喵星电压接口)\n"
        "| 参考电压: 3.3V (像三文鱼罐头一样精准)\n"
        "======================================\n");
    //开启ADC
    Dri_ADC1_StartConvert();
    while (1)
    {
        //向串口打印模拟电压
        printf("V=%.2f\n", Dri_ADC1_ReadV());
        Com_Delay_ms(1000);
    }
}