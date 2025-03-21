#ifndef __RTC_H__
#define __RTC_H__

#include <stm32f10x.h>
#include <stdio.h>
#include "Dri_USART.h"
#include "time.h"

/* 自定义日期时间结构体 */
typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}DateTime;


//RTC初始化
void Dri_RTC_Init();

/**
 *@brief 配置闹钟秒数
 * 
 * @param second 秒
 */
void Drt_RTC_SetALR(uint32_t second);

/**
 *@brief 设置当前系统时间戳
 * 
 * @param timeStamp 当前时间戳
 */
void Dri_RTC_SetTimeStamp(uint32_t timeStamp);

/**
 *@brief 获取当前系统时间
 * 
 * @param datetime 日期时间结构体
 */
void Dri_RTC_GetDateTime(DateTime* datetime);
#endif // !__RTC_H__