#ifndef __RTC_H__
#define __RTC_H__

#include <stm32f10x.h>
#include <stdio.h>
#include "Dri_USART.h"
//RTC初始化
void Dri_RTC_Init();

/**
 *@brief 配置闹钟秒数
 * 
 * @param second 秒
 */
void Drt_RTC_SetALR(uint32_t second);

#endif // !__RTC_H__