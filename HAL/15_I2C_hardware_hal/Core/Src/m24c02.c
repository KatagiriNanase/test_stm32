#include "m24c02.h"
#include "i2c.h"
//初始化
// void Int_M24C02_Init()
// {
//     MX_I2C2_Init();
// }

// //写入EEPROM一个字节
// void Int_M24C02_WriteByte(uint8_t addr, uint8_t byte)
// {
//     HAL_I2C_Mem_Write(&hi2c2, W_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);

//     //延时等待写入周期结束
//     HAL_Delay(5);
// }

// //读取EEPROM一个字节
// uint8_t Int_M24C02_ReadByte(uint8_t addr)
// {
//     uint8_t byte = 0;
//     HAL_I2C_Mem_Read(&hi2c2, R_ADDR, addr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);

//     return byte;
// }

// //连续写入多个字节（页写）
// void Int_M24C02_WriteBytes(uint8_t addr, uint8_t* bytes, uint8_t size)
// {
//     HAL_I2C_Mem_Write(&hi2c2, W_ADDR, addr, I2C_MEMADD_SIZE_8BIT, bytes, size, 1000);

//     HAL_Delay(5);
// }

// //连续读取多个字节
// void Int_M24C02_ReadBytes(uint8_t addr, uint8_t* buffer, uint8_t size)
// {
//     HAL_I2C_Mem_Read(&hi2c2, R_ADDR, addr, I2C_MEMADD_SIZE_8BIT, buffer, size, 1000);

// }



// 初始化
void Int_M24C02_Init(void)
{
    MX_I2C2_Init();
}

// 向EEPROM写入一个字节
void Int_M24C02_WriteByte(uint8_t innerAddr, uint8_t byte)
{
    HAL_I2C_Mem_Write(&hi2c2, W_ADDR, innerAddr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);

    // 延迟等待写入周期结束
    HAL_Delay(5);
}

// 读取EEPROM的一个字节
uint8_t Int_M24C02_ReadByte(uint8_t innerAddr)
{
    uint8_t byte;
    HAL_I2C_Mem_Read(&hi2c2, R_ADDR, innerAddr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);
    return byte;
}

// 连续写入多个字节（页写）
void Int_M24C02_WriteBytes(uint8_t innerAddr, uint8_t* bytes, uint8_t size)
{
    HAL_I2C_Mem_Write(&hi2c2, W_ADDR, innerAddr, I2C_MEMADD_SIZE_8BIT, bytes, size, 1000);

    // 延迟等待写入周期结束
    HAL_Delay(5);
}

// 连续读取多个字节
void Int_M24C02_ReadBytes(uint8_t innerAddr, uint8_t* buffer, uint8_t size)
{
    HAL_I2C_Mem_Read(&hi2c2, R_ADDR, innerAddr, I2C_MEMADD_SIZE_8BIT, buffer, size, 1000);
}
