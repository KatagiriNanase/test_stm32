#ifndef __DRI_I2C_H__
#define __DRI_I2C_H__
#include <stm32f10x.h>
#include "Com_Util.h"
//相关宏定义
#define ACK 0
#define NACK 1

#define SCL_HIGH (GPIOB->ODR |=GPIO_ODR_ODR10)
#define SCL_LOW (GPIOB->ODR &=~GPIO_ODR_ODR10)
#define SDA_HIGH (GPIOB->ODR |=GPIO_ODR_ODR11)
#define SDA_LOW (GPIOB->ODR &=~GPIO_ODR_ODR11)

//读取 操作
#define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR11)

#endif /* __DRI_I2C_H__ */