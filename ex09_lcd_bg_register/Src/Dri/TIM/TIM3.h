#ifndef __TIM3_H__
#define __TIM3_H__
#include <stm32f10x.h>
void Dri_TIM3_Init();

//定时器开启
void Dri_TIM3_Start();

//定时器关闭
void Dri_TIM3_Stop();

//设置占空比
void Dri_TIM3_SetDutyCycle(uint8_t dutycycle);

#endif /* __TIM3_H__ */