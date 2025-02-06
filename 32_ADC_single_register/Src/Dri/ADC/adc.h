#ifndef __ADC_H__
#define __ADC_H__

#include <stm32f10x.h>

//初始化
void Dri_ADC1_Init();

//开启转换
void Dri_ADC1_StartConvert();

//返回转换后的模拟电压值
double Dri_ADC1_ReadV();

#endif /* __ADC_H__ */