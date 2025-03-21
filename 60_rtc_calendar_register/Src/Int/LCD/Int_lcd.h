/**
 * @file Int_lcd.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2024 YOUR_COMPANY
 *
 */
#ifndef __INT_LCD_H__
#define __INT_LCD_H__

#include <stm32f10x.h>
#include <math.h>
 //宏定义
 //定义写命令和写数据的指针
#define SRAM_BANK1_4 0x6C000000
#define LCD_ADDR_CMD (uint16_t*)SRAM_BANK1_4
#define LCD_ADDR_DATA (uint16_t*)(SRAM_BANK1_4+(1<<11))

//定义显示屏的宽和高
#define LCD_W 320
#define LCD_H 480

/* 常见颜色 */
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 // 棕色
#define BRRED 0XFC07 // 棕红色
#define GRAY 0X8430  // 灰色

//1.基本控制操作
//1.1初始化
void Int_LCD_Init();

//1.1.1
void Int_LCD_Reset();

//1.1.2开关背光
void Int_LCD_BGon();
void Int_LCD_BGoff();

//1.1.3 初始化LCD寄存器
void Int_LCD_RegConfig();

//2. 写命令(发出一个指令)
void Int_LCD_WriteCmd(uint16_t cmd);

//3. 写数据(发出一个数据)
void Int_LCD_WriteData(uint16_t data);

//4.读数据
uint16_t Int_LCD_ReadData();


uint32_t Int_LEC_ReadID();

//清屏 填充全屏色
void Int_LCD_ClearAll(uint16_t color);

//设置区域
void Int_LCD_SetArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

void Int_LCD_WriteAsciiChar(uint16_t x, uint16_t y, uint16_t height, uint8_t c, uint16_t fColor, uint16_t bColor);

//显示字符串
void Int_LCD_WriteAsciiString(uint16_t x, uint16_t y, uint16_t height, uint8_t* str, uint16_t fColor, uint16_t bColor);

//显示一个中文字符
void Int_LCD_WriteChineseChar16(uint16_t x, uint16_t y, uint16_t height, uint8_t* ch, uint16_t fColor, uint16_t bColor);

//显示中文（正方形状）字符串
void Int_LCD_WriteChineseStr16(uint16_t x, uint16_t y, uint16_t height, uint8_t(*str)[32], uint8_t size, uint16_t fColor, uint16_t bColor);

//显示图片
void Int_Display_Mujika(uint16_t x, uint16_t y);


void Int_LCD_DrowPoint(uint16_t x, uint16_t y, uint16_t w, uint16_t color);


void Int_LCD_DrowLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t w, uint16_t color);

void Int_LCD_DrowRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t w, uint16_t color);

void Int_LCD_DrowHallowCircle(uint16_t xCenter, uint16_t yCenter, uint16_t r, uint16_t w, uint16_t color);

void Int_LCD_DrowSolidCircle(uint16_t xCenter, uint16_t yCenter, uint16_t r, uint16_t w, uint16_t color);

#endif /* __INT_LCD_H__ */