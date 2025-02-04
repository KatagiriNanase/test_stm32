#ifndef __TIM4_H__
#define __TIM4_H__

void Dri_TIM4_Init();

//定时器开启
void Dri_TIM4_Start();

//定时器关闭
void Dri_TIM4_Stop();

//获取输入信号周期
double Dri_TIM4_GetPWMCycle();

//获取输入信号频率
double Dri_TIM4_GetPWMFreq();

#endif /* __TIM4_H__ */