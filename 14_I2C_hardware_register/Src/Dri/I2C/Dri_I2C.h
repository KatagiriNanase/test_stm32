#ifndef __DRI_I2C_H__
#define __DRI_I2C_H__
#include <stm32f10x.h>
#include "Com_Util.h"

//宏定义
#define OK 0
#define FAIL 1

//初始化
void Dri_I2C_Init();

//发出起始信号
uint8_t Dri_I2C_Start();

//设置发出停止信号
void Dri_I2C_Stop();

//主机设置应答使能
void Dri_I2C_Ack();

//主机设置非应答使能
void Dri_I2C_Nack();

//主机发送设备地址，并等待应答
uint8_t Dri_I2C_SendAddr(uint8_t addr);

//主机发送一个字节的数据,并等待应答
uint8_t Dri_I2C_SendByte(uint8_t byte);

//主机接收一个字节的数据
uint8_t Dri_I2C_ReadByte();
#endif /* __DRI_I2C_H__ */