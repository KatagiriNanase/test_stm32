#include "Int_lcd.h"
#include "Dri_fsmc.h"
#include "Com_Util.h"
#include "Int_lcd_font.h"
void Int_LCD_Init()
{
    Dri_FSMC_Init();

    Int_LCD_Reset();

    Int_LCD_BGon();

    Int_LCD_RegConfig();
}

//1.1.1
void Int_LCD_Reset()
{
    GPIOG->ODR &= ~GPIO_ODR_ODR15;

    Com_Delay_ms(100);

    GPIOG->ODR |= GPIO_ODR_ODR15;

    Com_Delay_ms(100);

}

//1.1.2开关背光
void Int_LCD_BGon()
{
    //PB0输出高电平
    GPIOB->ODR |= GPIO_ODR_ODR0;
}
void Int_LCD_BGoff()
{
    //PB0输出低电平
    GPIOB->ODR &= ~GPIO_ODR_ODR0;
}
//1.1.3 初始化LCD寄存器
void Int_LCD_RegConfig()
{
    /* 1. 设置灰阶电压以调整TFT面板的伽马特性， 正校准。一般出厂就设置好了 */
    Int_LCD_WriteCmd(0xE0);
    Int_LCD_WriteData(0x00);
    Int_LCD_WriteData(0x07);
    Int_LCD_WriteData(0x10);
    Int_LCD_WriteData(0x09);
    Int_LCD_WriteData(0x17);
    Int_LCD_WriteData(0x0B);
    Int_LCD_WriteData(0x41);
    Int_LCD_WriteData(0x89);
    Int_LCD_WriteData(0x4B);
    Int_LCD_WriteData(0x0A);
    Int_LCD_WriteData(0x0C);
    Int_LCD_WriteData(0x0E);
    Int_LCD_WriteData(0x18);
    Int_LCD_WriteData(0x1B);
    Int_LCD_WriteData(0x0F);

    /* 2. 设置灰阶电压以调整TFT面板的伽马特性，负校准 */
    Int_LCD_WriteCmd(0XE1);
    Int_LCD_WriteData(0x00);
    Int_LCD_WriteData(0x17);
    Int_LCD_WriteData(0x1A);
    Int_LCD_WriteData(0x04);
    Int_LCD_WriteData(0x0E);
    Int_LCD_WriteData(0x06);
    Int_LCD_WriteData(0x2F);
    Int_LCD_WriteData(0x45);
    Int_LCD_WriteData(0x43);
    Int_LCD_WriteData(0x02);
    Int_LCD_WriteData(0x0A);
    Int_LCD_WriteData(0x09);
    Int_LCD_WriteData(0x32);
    Int_LCD_WriteData(0x36);
    Int_LCD_WriteData(0x0F);

    /* 3.  Adjust Control 3 (F7h)  */
    /*LCD_WriteCmd(0XF7);
   Int_LCD_WriteData(0xA9);
   Int_LCD_WriteData(0x51);
   Int_LCD_WriteData(0x2C);
   Int_LCD_WriteData(0x82);*/
   /* DSI write DCS command, use loose packet RGB 666 */

   /* 4. 电源控制1*/
    Int_LCD_WriteCmd(0xC0);
    Int_LCD_WriteData(0x11); /* 正伽马电压 */
    Int_LCD_WriteData(0x09); /* 负伽马电压 */

    /* 5. 电源控制2 */
    Int_LCD_WriteCmd(0xC1);
    Int_LCD_WriteData(0x02);
    Int_LCD_WriteData(0x03);

    /* 6. VCOM控制 */
    Int_LCD_WriteCmd(0XC5);
    Int_LCD_WriteData(0x00);
    Int_LCD_WriteData(0x0A);
    Int_LCD_WriteData(0x80);

    /* 7. Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    Int_LCD_WriteCmd(0xB1);
    Int_LCD_WriteData(0xB0);
    Int_LCD_WriteData(0x11);

    /* 8.  Display Inversion Control (B4h) （正负电压反转，减少电磁干扰）*/
    Int_LCD_WriteCmd(0xB4);
    Int_LCD_WriteData(0x02);

    /* 9.  Display Function Control (B6h)  */
    Int_LCD_WriteCmd(0xB6);
    Int_LCD_WriteData(0x0A);
    Int_LCD_WriteData(0xA2);

    /* 10. Entry Mode Set (B7h)  */
    Int_LCD_WriteCmd(0xB7);
    Int_LCD_WriteData(0xc6);

    /* 11. HS Lanes Control (BEh) */
    Int_LCD_WriteCmd(0xBE);
    Int_LCD_WriteData(0x00);
    Int_LCD_WriteData(0x04);

    /* 12.  Interface Pixel Format (3Ah) */
    Int_LCD_WriteCmd(0x3A);
    Int_LCD_WriteData(0x55); /* 0x55 : 16 bits/pixel  */

    /* 13. Sleep Out (11h) 关闭休眠模式 */
    Int_LCD_WriteCmd(0x11);

    /* 14. 设置屏幕方向和RGB */
    Int_LCD_WriteCmd(0x36);
    Int_LCD_WriteData(0x08);

    Com_Delay_ms(120);

    /* 14. display on */
    Int_LCD_WriteCmd(0x29);


}

//1.2. 写命令(发出一个指令)
void Int_LCD_WriteCmd(uint16_t cmd)
{
    *LCD_ADDR_CMD = cmd;
}

//1.3. 写数据(发出一个数据)
void Int_LCD_WriteData(uint16_t data)
{
    *LCD_ADDR_DATA = data;
}

//1.4.读数据
uint16_t Int_LCD_ReadData()
{
    return *LCD_ADDR_DATA;
}

//2.具体的命令操作

//2.1 返回ID信息
uint32_t Int_LEC_ReadID()
{
    //发送读取ID的命令
    Int_LCD_WriteCmd(0x04);

    //接受三个字节的信息
    uint32_t id = 0;

    //第一次读取的信息无效
    Int_LCD_ReadData();

    //依次读取三个字节的数据
    id |= (Int_LCD_ReadData() & 0xff) << 16;
    id |= (Int_LCD_ReadData() & 0xff) << 8;
    id |= (Int_LCD_ReadData() & 0xff) << 0;

    return id;

}

void Int_LCD_SetArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    //1. 设置区域列范围
    Int_LCD_WriteCmd(0x2a);
    //1.1设置起始列
    Int_LCD_WriteData((x >> 8) & 0xff);
    Int_LCD_WriteData(x & 0xff);
    //1.2设置结束列
    Int_LCD_WriteData(((x + w - 1) >> 8 & 0xff));
    Int_LCD_WriteData(((x + w - 1) & 0xff));

    //2. 设置区域行范围
    Int_LCD_WriteCmd(0x2b);
    //2.1设置起始行
    Int_LCD_WriteData((y >> 8) & 0xff);
    Int_LCD_WriteData(y & 0xff);
    //2.2设置结束行
    Int_LCD_WriteData(((y + h - 1) >> 8 & 0xff));
    Int_LCD_WriteData(((y + h - 1) & 0xff));
}


void Int_LCD_ClearAll(uint16_t color)
{
    //设置区域范围--全屏
    Int_LCD_SetArea(0, 0, LCD_W, LCD_H);

    //相对应范围发送数据
    Int_LCD_WriteCmd(0x2c);
    for (uint32_t i = 0;i < LCD_H * LCD_W;++i)
        Int_LCD_WriteData(color);
}

//上层操作接口
//3.1 显示ASCII字符
void Int_LCD_WriteAsciiChar(uint16_t x, uint16_t y, uint16_t height, uint8_t c, uint16_t fColor, uint16_t bColor)
{
    //1.设置显示范围
    Int_LCD_SetArea(x, y, height / 2, height);

    //2.发送写入显存指令
    Int_LCD_WriteCmd(0x2c);

    //3.遍历整个区域所有的像素点，判断是否为字符的笔画
    //按照字体大小，到不同的数组中寻找对应的点阵

    //计算当前字符的索引
    uint8_t index = c - ' ';
    //3.1 如果字体为1608或1206，用一个字节表示一行点阵
    if (height == 16 || height == 12)
    {
        for (uint16_t i = 0;i < height;++i)
        {
            //根据字体大小，在字库中选择当前行对应的字节
            uint8_t tempRow = (height == 16) ? ascii_1608[index][i] : ascii_1206[index][i];
            for (uint8_t j = 0;j < height / 2;++j)
            {
                if (tempRow & 0x01)
                    Int_LCD_WriteData(fColor);
                else if (!(tempRow & 0x01))
                    Int_LCD_WriteData(bColor);

                tempRow >>= 1;
            }
        }
    }

    //3.2 如果字体为2412，用二个字节表示一行点阵
    else if (height == 24)
    {
        for (uint16_t i = 0;i < height * 2;++i)
        {
            //根据字体大小，在字库中选择当前行对应的字节
            uint8_t tempRow = ascii_2412[index][i];

            //根据当前i的值，判断字节中遍历多少位数据（奇数只遍历低四位）
            uint8_t jCount = (i % 2) ? 4 : 8;
            for (uint16_t j = 0;j < jCount;++j)
            {
                if (tempRow & 0x01)
                    Int_LCD_WriteData(fColor);
                else if (!(tempRow & 0x01))
                    Int_LCD_WriteData(bColor);

                tempRow >>= 1;
            }
        }
    }

    //3.3 如果字体为3216，用二个字节表示一行点阵
    else if (height == 32)
    {
        //i 为字节编号
        for (uint16_t i = 0;i < height * 2;++i)
        {
            //根据字体大小，在字库中选择当前行对应的字节
            uint8_t tempRow = ascii_3216[index][i];

            for (uint16_t j = 0;j < 8;++j)
            {
                if (tempRow & 0x01)
                    Int_LCD_WriteData(fColor);
                else if (!(tempRow & 0x01))
                    Int_LCD_WriteData(bColor);

                tempRow >>= 1;
            }
        }
    }
}


void Int_LCD_WriteAsciiString(uint16_t x, uint16_t y, uint16_t height, uint8_t* str, uint16_t fColor, uint16_t bColor)
{
    //定义一个变量，指明当前遍历的字符
    uint8_t i = 0;
    // 利用\0标志判断字符串是否结束

    while (str[i] != '\0')
    {
        //判断是否遇到\n需要换行 是否在边界
        if (str[i] == '\n' || x + height / 2 > LCD_W)
        {
            x = 0;
            y += height;
            ++i;
        }

        //字体高度超过边界 显示不下了
        if (y + height > LCD_H)
            return;

        Int_LCD_WriteAsciiChar(x, y, height, str[i], fColor, bColor);

        x += height / 2;
        ++i;
    }

}

void Int_LCD_WriteChineseChar16(uint16_t x, uint16_t y, uint16_t height, uint8_t* ch, uint16_t fColor, uint16_t bColor)
{
    //1.设置显示范围
    Int_LCD_SetArea(x, y, height, height);

    //2.发送写入显存指令
    Int_LCD_WriteCmd(0x2c);

    for (uint8_t i = 0;i < height * (height / 8);++i)
    {
        uint8_t tempByte = ch[i];
        for (uint8_t j = 0;j < 8;++j)
        {
            if (tempByte & 0x01)
                Int_LCD_WriteData(fColor);
            else if (!(tempByte & 0x01))
                Int_LCD_WriteData(bColor);

            tempByte >>= 1;
        }
    }

}

void Int_LCD_WriteChineseStr16(uint16_t x, uint16_t y, uint16_t height, uint8_t(*str)[32], uint8_t size, uint16_t fColor, uint16_t bColor)
{
    uint8_t i = 0;
    while (i < size)
    {
        if (x + height > LCD_W)
        {
            x = 0;
            y += height;
            i++;
        }

        if (y + height > LCD_H)
            return;

        else
        {
            Int_LCD_WriteChineseChar16(x, y, height, str[i], fColor, bColor);
            x += height;
        }
        i++;
    }



}


void Int_Display_Mujika(uint16_t x, uint16_t y)
{
    //1.设置显示范围
    Int_LCD_SetArea(x, y, 320, 480);

    //2.发送写入显存指令
    Int_LCD_WriteCmd(0x2c);
    for (uint32_t i = 0;i < 307208;i += 2)
    {
        uint16_t tempPix = (gImage_misade[i] << 8) + gImage_misade[i + 1];
        Int_LCD_WriteData(tempPix);

    }

}

/**
 *@brief    画出一个点，给定左上角起始点的坐标，以及方点的宽度
 *
 * @param x 起始x
 * @param y 起始y
 * @param w 宽度
 * @param color 颜色
 */
void Int_LCD_DrowPoint(uint16_t x, uint16_t y, uint16_t w, uint16_t color)
{
    //设置区域
    Int_LCD_SetArea(x, y, w, w);

    //传输数据
    Int_LCD_WriteCmd(0x2c);

    for (uint16_t i = 0;i < w * w;++i)
        Int_LCD_WriteData(color);
}

/**
 *@brief drow a line
 *  @attention x2>x1,y2>y1
 * @param x1 起始横坐标
 * @param y1 起始纵坐标
 * @param x2 终点横坐标
 * @param y2 终点纵坐标
 * @param w  线宽
 * @param color 颜色
 */
void Int_LCD_DrowLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t w, uint16_t color)
{
    //y=kx+b ,k=(y2-y1)/(x2-x1),b=y1-kx1

    //考虑x1==x2的情况
    if (x1 == x2)
    {
        for (uint16_t y = y1;y < y2;y += w)
            Int_LCD_DrowPoint(x1, y, w, color);
        return;
    }

    double k = (y2 - y1) / (x2 - x1) * 1.0;
    double b = y1 - k * x1;

    //根据直线方程画点
    for (uint16_t x = x1;x < x2;x++)
    {
        uint16_t y = (uint16_t)k * x + b;
        Int_LCD_DrowPoint(x, y, w, color);
    }

}

/**
 *@brief drow a rectangle
 *
 *  @attention x2>x1,y2>y1
 * @param x1 起始横坐标
 * @param y1 起始纵坐标
 * @param x2 终点横坐标
 * @param y2 终点纵坐标
 * @param w  线宽
 * @param color 颜色
 */

void Int_LCD_DrowRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t w, uint16_t color)
{
    Int_LCD_DrowLine(x1, y1, x2, y1, w, color);
    Int_LCD_DrowLine(x2, y1, x2, y2, w, color);
    Int_LCD_DrowLine(x1, y1, x1, y2, w, color);
    Int_LCD_DrowLine(x1, y2, x2, y2, w, color);

}
/**
 *@brief drow a hollow circle
 *
 * @param xCenter 圆心x
 * @param yCenter 圆心y
 * @param r 半径
 * @param w 线宽
 * @param color 线颜色
 */
void Int_LCD_DrowHallowCircle(uint16_t xCenter, uint16_t yCenter, uint16_t r, uint16_t w, uint16_t color)
{
    //极坐标方程
    //x = x0+rcosθ
    //y = y0+rcosθ
    for (uint16_t theta = 0;theta < 90;theta++)
    {
        uint16_t x = xCenter + r * cos((3.14 * theta) / 180);
        uint16_t y = yCenter + r * sin((3.14 * theta) / 180);
        Int_LCD_DrowPoint(x, y, w, color);
        Int_LCD_DrowPoint(2 * xCenter - x, y, w, color);
        Int_LCD_DrowPoint(x, 2 * yCenter - y, w, color);
        Int_LCD_DrowPoint(2 * xCenter - x, 2 * yCenter - y, w, color);

    }
}

/**
 *@brief drow a solid circle
 *
 * @param xCenter
 * @param yCenter
 * @param r
 * @param w
 * @param color
 */
void Int_LCD_DrowSolidCircle(uint16_t xCenter, uint16_t yCenter, uint16_t r, uint16_t w, uint16_t color)
{
    //极坐标方程
     //x = x0+rcosθ
     //y = y0+rcosθ
    for (uint16_t theta = 0;theta < 90;theta++)
    {
        uint16_t x = xCenter + r * cos((3.14 * theta) / 180);
        uint16_t y = yCenter + r * sin((3.14 * theta) / 180);
        Int_LCD_DrowLine(2 * xCenter - x, y, x, y, w, color);
        Int_LCD_DrowLine(2 * xCenter - x, 2 * yCenter - y, x, 2 * yCenter - y, w, color);

    }

}
