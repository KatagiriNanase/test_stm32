#ifndef __DRI_USART_H__
#define __DRI_USART_H__
#include <stm32f10x.h>
extern uint8_t buffer[100];
extern uint8_t size;
extern uint8_t isOver;
//串口通讯初始化
void Dri_USART_Init();

//发送一个字符--轮询
void Dri_USART_SendChar(uint8_t ch);

//接收一个字符

//发送字符串
void Dri_USART_SendString(uint8_t* str);

//接收字符串
#endif /* __DRI_USART_H__ */
