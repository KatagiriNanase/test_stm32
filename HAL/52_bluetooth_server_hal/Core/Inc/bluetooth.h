#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "esp32.h"

void Bluetooth_Init(void);

/**
 *@brief 读取蓝牙收到的数据和连接状态
 *
 * @param rxBuff 接收缓冲区
 * @param rxLen 接收到数据的长度
 * @retval 状态码 0 正常接收到数据 \n  1 没有接收到数据 \n 2 链接发生改变
 */
uint8_t Bluetooth_ReadData(uint8_t* rxBuff, uint16_t* rxLen);

void BLE_SetupSPPService(void);

/**
 *@brief 处理连接状态改变的情况，状态保存在接收数据缓冲区
 *
 *@retval 状态码 
 */
uint8_t Bluetooth_HandleConnChange(void);

/**
 * @brief 发送数据至usart1
 *
 * @param txBuff 发送缓冲区
 * @param txLen 发送数据长度
 */
void Bluetooth_SendData(uint8_t txBuff[], uint16_t txLen);
#endif /* __BLUETOOTH_H__ */
