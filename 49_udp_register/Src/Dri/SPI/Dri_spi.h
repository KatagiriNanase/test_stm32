#ifndef __DRI_SPI_H__
#define __DRI_SPI_H__

#include <stm32f10x.h>
//宏定义

//CS PD3
#define CS_HIGH (GPIOD->ODR|=GPIO_ODR_ODR3)
#define CS_LOW (GPIOD->ODR&=~GPIO_ODR_ODR3)

//初始化
void Dri_SPI_Init();

//数据传输的开始
void Dri_SPI_Start();

//数据传输的结束
void Dri_SPI_Stop();

//主从设备交换一个字节的数据
uint8_t Dri_SPI_SwapByte(uint8_t byte);
#endif /* __DRI_SPI_H__ */