#ifndef __DRI_SPI_H__
#define __DRI_SPI_H__

#include <stm32f10x.h>
#include "Com_Util.h"
//宏定义

#define CS_HIGH (GPIOC->ODR|=GPIO_ODR_ODR13)
#define CS_LOW (GPIOC->ODR&=~GPIO_ODR_ODR13)

#define SCK_HIGH (GPIOA->ODR|=GPIO_ODR_ODR5)
#define SCK_LOW (GPIOA->ODR&=~GPIO_ODR_ODR5)

#define MOSI_HIGH (GPIOA->ODR|=GPIO_ODR_ODR7)
#define MOSI_LOW (GPIOA->ODR&=~GPIO_ODR_ODR7)

//读取MISO信号
#define MISO_READ (GPIOA->IDR&GPIO_IDR_IDR6)

//SPI标准延迟时间
#define SPI_DELAY Com_Delay_us(5)

//初始化
void Dri_SPI_Init();

//数据传输的开始
void Dri_SPI_Start();

//数据传输的结束
void Dri_SPI_Stop();

//主从设备交换一个字节的数据
uint8_t Dri_SPI_SwapByte(uint8_t byte);
#endif /* __DRI_SPI_H__ */