#ifndef __INT_LED_H__
#define __INT_LED_H__
#include "stm32f10x.h"
#define LED1 GPIO_ODR_ODR0
#define LED2 GPIO_ODR_ODR1
#define LED3 GPIO_ODR_ODR8

//初始化
void Int_LED_Init(void);

//控制LED开关
void Int_LED_On(uint16_t led);
void Int_LED_Off(uint16_t led);

//翻转LED状态
void Int_LED_Toggle(uint16_t led);

//对一组LED全开，全关
void Int_LED_OnAll(uint16_t leds[], uint8_t size);
void Int_LED_OffAll(uint16_t leds[], uint8_t size);



#endif /* __INT_LED_H__ */
