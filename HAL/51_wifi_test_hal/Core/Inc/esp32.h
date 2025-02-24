#ifndef __ESP32_H__
#define __ESP32_H__

#include "usart.h"
#include <string.h>

/*******WIFI相关配置*********/
//初始化
void ESP32_Init(void);

//发送命令
void ESP32_SendCmd(uint8_t* cmd);

//读取响应
void ESP32_ReadResp(uint8_t rBuff[], uint16_t* rDataLen);

//设置WIFI模式为STA
void ESP32_WIFI_STA(void);

//设置WIFI模式为AP
void ESP32_WIFI_AP(void);


/*******TCP相关配置*********/
//启动TCP服务器
void ESP_TCP_StartTcpServer(void);

/**
 *@brief 接收tcp传输数据
 *
 * @param rBuff 接收缓冲区
 * @param rMsglen 接收到数据的大小
 * @param id 连接方的id
 * @param ip 连接方的ip
 * @param port 连接方的端口号
 */
void ESP_TCP_RecvTcpData(uint8_t rBuff[], uint16_t* rMsglen, uint8_t* id, uint8_t* ip, uint16_t* port);

/**
 *@brief 以TCP协议发送数据
 *
 * @param id 客户端id
 * @param msg 发送数据缓冲区
 * @param len 发送数据长度
 */
void ESP_TCP_SendTcpData(uint8_t id, uint8_t* msg, uint16_t len);

/**
 * @brief 单连接下以TCP协议发送数据
 *
 * @param msg 发送数据缓冲区
 * @param len 发送数据长度
 */
void ESP_TCP_SendTcpDataSingle(uint8_t* msg, uint16_t len);
#endif /* __ESP32_H__ */
