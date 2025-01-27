#ifndef __M24C02_H__
#define __M24C02_H__
#include <stm32f10x.h>
#include "Dri_I2C.h"
#include "Com_Util.h"
#define W_ADDR 0xA0
#define R_ADDR 0xA1

//初始化
void Int_M24C02_Init();

//写入EEPROM一个字节
void Int_M24C02_WriteByte(uint8_t addr,uint8_t byte);

//读取EEPROM一个字节
uint8_t Int_M24C02_ReadByte(uint8_t addr);

//连续写入多个字节（页写）
void Int_M24C02_WriteBytes(uint8_t addr, uint8_t* bytes, uint8_t size);

//连续读取多个字节
void Int_M24C02_ReadBytes(uint8_t addr, uint8_t* buffer, uint8_t size);



//连续读取
#endif /* __M24C02_H__ */