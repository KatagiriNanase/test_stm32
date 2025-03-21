#include "Key.h"
#include "Int_LED.h"
#include "Com_Util.h"
#include "Dri_USART.h"
typedef struct {
    uint32_t SYSTCLK_SRC;  //系统时钟来源
    uint32_t SYSCLK_Freq;  // 系统时钟频率（Hz）
    uint32_t AHB_Freq;    // AHB总线时钟频率（Hz）
    uint32_t APB1_Freq;    // APB1总线时钟频率（Hz）
    uint32_t APB2_Freq;    // APB2总线时钟频率（Hz）
} RCC_ClocksTypeDef;

void enter_stopmode();
void GetClock(RCC_ClocksTypeDef* RCC_Clocks);
void GetAHB_Clock(RCC_ClocksTypeDef* RCC_Clocks);


int main()
{
    Dri_USART_Init();
    Int_LED_Init();
    Int_Key_Init();
    Int_LED_On(LED2);
    RCC_ClocksTypeDef RCC_Clocks;
    while (1)
    {
        printf("3秒后进入普通睡眠模式\n");
        Com_Delay_ms(3000);
        printf("进入停机模式\n");
        Com_Delay_ms(1);
        enter_stopmode();
        GetClock(&RCC_Clocks);

        SystemInit();
        printf("Init前系统时钟：%d,AHB：%d,APB1:%d,APB2:%d\n",
            RCC_Clocks.SYSCLK_Freq,
            RCC_Clocks.AHB_Freq,
            RCC_Clocks.APB1_Freq,
            RCC_Clocks.APB2_Freq);
        Com_Delay_ms(10);
        GetClock(&RCC_Clocks);
        printf("Init后系统时钟：%d,AHB：%d,APB1:%d,APB2:%d\n",
            RCC_Clocks.SYSCLK_Freq,
            RCC_Clocks.AHB_Freq,
            RCC_Clocks.APB1_Freq,
            RCC_Clocks.APB2_Freq);
        printf("被唤醒\n");
    }
}

void enter_stopmode()
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* 进入停机模式 */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR &= ~PWR_CR_PDDS;
    /* 让电压调节器进入低功耗模式 （给寄存器和SRAM供电，其他断开）*/
    PWR->CR |= PWR_CR_LPDS;

    /* 发送WFI进入等待中断模式 */
    __WFI();
}

//获取系统各模块时钟
void GetClock(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t mul;
    //获取系统时钟频率
    switch (RCC->CFGR & RCC_CFGR_SWS)
    {
    case RCC_CFGR_SWS_HSE:
        RCC_Clocks->SYSTCLK_SRC = RCC_CFGR_SW_HSE;
        RCC_Clocks->SYSCLK_Freq = HSE_Value;
        break;
    case RCC_CFGR_SWS_HSI:
        RCC_Clocks->SYSTCLK_SRC = RCC_CFGR_SW_HSI;
        RCC_Clocks->SYSCLK_Freq = HSI_Value;
        break;
    case RCC_CFGR_SWS_PLL:
        RCC_Clocks->SYSTCLK_SRC = RCC_CFGR_SW_PLL;
        mul = ((RCC->CFGR & RCC_CFGR_PLLMULL) >> 18) + 2;
        RCC_Clocks->SYSCLK_Freq = HSE_VALUE * mul;
        break;
    default:
        break;
    }

    //获取AHB,APB1,APB2时钟频率
    GetAHB_Clock(RCC_Clocks);

}
void GetAHB_Clock(RCC_ClocksTypeDef* RCC_Clocks)
{
    //获取AHB频率
    if ((((RCC->CFGR & RCC_CFGR_HPRE) >> 4) & 0x08) == 0)
        RCC_Clocks->AHB_Freq = RCC_Clocks->SYSCLK_Freq;
    else
    {
        uint8_t div = ((RCC->CFGR & RCC_CFGR_HPRE >> 4) & 0x07) + 2;
        if (div < 4)
            RCC_Clocks->AHB_Freq = RCC_Clocks->SYSCLK_Freq >> div;
        else
            RCC_Clocks->AHB_Freq = RCC_Clocks->SYSCLK_Freq >> (div + 1);
    }
    //获取APB1频率
    if (((RCC->CFGR & RCC_CFGR_PPRE1) >> 8) & 0x04 == 0)
        RCC_Clocks->APB1_Freq = RCC_Clocks->SYSCLK_Freq;
    else
    {
        uint8_t div = ((RCC->CFGR & RCC_CFGR_HPRE >> 8) & 0x03) + 1;
        RCC_Clocks->APB1_Freq = RCC_Clocks->SYSCLK_Freq >> div;
    }

    //获取APB2频率
    if ((((RCC->CFGR & RCC_CFGR_PPRE1) >> 11) & 0x04) == 0)
        RCC_Clocks->APB2_Freq = RCC_Clocks->SYSCLK_Freq;
    else
    {
        uint8_t div = ((RCC->CFGR & RCC_CFGR_HPRE >> 11) & 0x03) + 1;
        RCC_Clocks->APB2_Freq = RCC_Clocks->SYSCLK_Freq >> div;
    }
}