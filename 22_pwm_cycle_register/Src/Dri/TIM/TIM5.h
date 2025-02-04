#ifndef __TIM5_H__
#define __TIM5_H__
#include <stm32f10x.h>
void Dri_TIM5_Init();

//定时器开启
void Dri_TIM5_Start();

//定时器关闭
void Dri_TIM5_Stop();

//设置占空比
void Dri_TIM5_SetDutyCycle(uint8_t dutycycle);

#endif /* __TIM5_H__ */