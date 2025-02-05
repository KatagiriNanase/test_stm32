#ifndef __DRI_DMA_H__
#define __DRI_DMA_H__
#include <stm32f10x.h>
//DMA1初始化
void Dri_DMA1_Init();

//数据传输
void Dri_DMA1_Transmit(uint32_t scrAddr, uint32_t desAddr, uint16_t dataLen);
#endif /* __DRI_DMA_H__ */