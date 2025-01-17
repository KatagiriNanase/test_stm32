#include "Int_LED.h"
#include "Com_Util.h"
//初始化
void Int_LED_Init()
{
    //配置时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;


    //配置工作模式
    GPIOA->CRL &= ~(GPIO_CRL_CNF0);
    GPIOA->CRL |= (GPIO_CRL_MODE0);

    GPIOA->CRL &= ~(GPIO_CRL_CNF1);
    GPIOA->CRL |= (GPIO_CRL_MODE1);

    GPIOA->CRH &= ~(GPIO_CRH_CNF8);
    GPIOA->CRH |= (GPIO_CRH_MODE8);

    //PA0,PA1,PA8输出高电平，关灯
    GPIOA->ODR |= (GPIO_ODR_ODR0);
    GPIOA->ODR |= (GPIO_ODR_ODR1);
    GPIOA->ODR |= (GPIO_ODR_ODR8);
}

//控制LED开关
void Int_LED_On(uint16_t led)
{
    GPIOA->ODR &= ~led;
}
void Int_LED_Off(uint16_t led)
{
    GPIOA->ODR |= led;
}

//翻转LED状态
void Int_LED_Toggle(uint16_t led)
{
    //判断当前LED状态
    if (!(GPIOA->IDR & led))
        Int_LED_Off(led);
    else
        Int_LED_On(led);
}

//对一组LED全开，全关
void Int_LED_OnAll(uint16_t leds[], uint8_t size)
{
    uint8_t i;
    for (i = 0;i < size;++i)
        Int_LED_On(leds[i]);
}
void Int_LED_OffAll(uint16_t leds[], uint8_t size)
{
    uint8_t i;
    for (i = 0;i < size;++i)
        Int_LED_Off(leds[i]);
}
