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

//定义操作的基本延时
#define I2C_DELAY Com_Delay_us(10)

//初始化
void Dri_I2C_Init();

//发出起始信号
void Dri_I2C_Start();

//发出停止信号
void Dri_I2C_Stop();

//主机发出 应答信号
void Dri_I2C_Ack();

//主机发出非应答信号
void Dri_I2C_Nack();

//主机等待从设别发来应答信号
uint8_t Dri_I2C_Wait4Ack();

//主机发送一个字节的数据
void Dri_I2C_SendByte(uint8_t byte);

//主机接收一个字节的数据
uint8_t Dri_I2C_ReadByte();
#endif /* __DRI_I2C_H__ */