#ifndef __W25Q32_H__
#define __W25Q32_H__

#include "Dri_spi.h"

//初始化
void Int_W25q32_Init();

//读取ID
void Int_W25q32_ReadID(uint8_t* mid, uint16_t* did);

//开启写使能
void Int_W25q32_WriteEnable();

//关闭写使能
void Int_W25q32_WriteDisable();

//等待状态不为忙
void Int_W25q32_WaitNotBusy();

//擦除段区
void Int_W25q32_EraseSector(uint8_t block, uint8_t sector);

//写入（页写）
void Int_W25q32_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t* data, uint16_t len);

//读取
void Int_W25q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t len);


#endif /* __W25Q32_H__ */