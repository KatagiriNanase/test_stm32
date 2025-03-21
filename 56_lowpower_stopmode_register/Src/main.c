#include "Key.h"
#include "Int_LED.h"
#include "Com_Util.h"
#include "Dri_USART.h"
typedef struct {
    uint32_t SYSTCLK_SRC;  //ϵͳʱ����Դ
    uint32_t SYSCLK_Freq;  // ϵͳʱ��Ƶ�ʣ�Hz��
    uint32_t AHB_Freq;    // AHB����ʱ��Ƶ�ʣ�Hz��
    uint32_t APB1_Freq;    // APB1����ʱ��Ƶ�ʣ�Hz��
    uint32_t APB2_Freq;    // APB2����ʱ��Ƶ�ʣ�Hz��
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
        printf("3��������ͨ˯��ģʽ\n");
        Com_Delay_ms(3000);
        printf("����ͣ��ģʽ\n");
        Com_Delay_ms(1);
        enter_stopmode();
        GetClock(&RCC_Clocks);

        SystemInit();
        printf("Initǰϵͳʱ�ӣ�%d,AHB��%d,APB1:%d,APB2:%d\n",
            RCC_Clocks.SYSCLK_Freq,
            RCC_Clocks.AHB_Freq,
            RCC_Clocks.APB1_Freq,
            RCC_Clocks.APB2_Freq);
        Com_Delay_ms(10);
        GetClock(&RCC_Clocks);
        printf("Init��ϵͳʱ�ӣ�%d,AHB��%d,APB1:%d,APB2:%d\n",
            RCC_Clocks.SYSCLK_Freq,
            RCC_Clocks.AHB_Freq,
            RCC_Clocks.APB1_Freq,
            RCC_Clocks.APB2_Freq);
        printf("������\n");
    }
}

void enter_stopmode()
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* ����ͣ��ģʽ */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR &= ~PWR_CR_PDDS;
    /* �õ�ѹ����������͹���ģʽ �����Ĵ�����SRAM���磬�����Ͽ���*/
    PWR->CR |= PWR_CR_LPDS;

    /* ����WFI����ȴ��ж�ģʽ */
    __WFI();
}

//��ȡϵͳ��ģ��ʱ��
void GetClock(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t mul;
    //��ȡϵͳʱ��Ƶ��
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

    //��ȡAHB,APB1,APB2ʱ��Ƶ��
    GetAHB_Clock(RCC_Clocks);

}
void GetAHB_Clock(RCC_ClocksTypeDef* RCC_Clocks)
{
    //��ȡAHBƵ��
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
    //��ȡAPB1Ƶ��
    if (((RCC->CFGR & RCC_CFGR_PPRE1) >> 8) & 0x04 == 0)
        RCC_Clocks->APB1_Freq = RCC_Clocks->SYSCLK_Freq;
    else
    {
        uint8_t div = ((RCC->CFGR & RCC_CFGR_HPRE >> 8) & 0x03) + 1;
        RCC_Clocks->APB1_Freq = RCC_Clocks->SYSCLK_Freq >> div;
    }

    //��ȡAPB2Ƶ��
    if ((((RCC->CFGR & RCC_CFGR_PPRE1) >> 11) & 0x04) == 0)
        RCC_Clocks->APB2_Freq = RCC_Clocks->SYSCLK_Freq;
    else
    {
        uint8_t div = ((RCC->CFGR & RCC_CFGR_HPRE >> 11) & 0x03) + 1;
        RCC_Clocks->APB2_Freq = RCC_Clocks->SYSCLK_Freq >> div;
    }
}