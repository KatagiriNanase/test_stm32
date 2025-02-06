#ifndef __ADC_H__
#define __ADC_H__

#include <stm32f10x.h>

//初始化
void Dri_ADC1_Init();

//开启转换
void Dri_ADC1_DMA_StartConvert(uint32_t des, uint16_t len);

void Dri_ADC1_DMA_Init();

#endif /* __ADC_H__ */