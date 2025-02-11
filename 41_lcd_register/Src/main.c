#include "Dri_USART.h"
#include "Int_lcd.h"
#include "Com_Util.h"
int main()
{
    Dri_USART_Init();
    Int_LCD_Init();

    // printf("hello world!\n");

    // uint32_t id = Int_LEC_ReadID();

    // printf("id=%#x\n", id);

    //将全屏设置为蓝色
    Int_LCD_ClearAll(WHITE);

    //显示单个英文字符 1608
    // Int_LCD_WriteAsciiChar(10, 10, 16, 'C', BLACK, WHITE);
    // Int_LCD_WriteAsciiChar(18, 10, 16, 'o', BLACK, WHITE);
    // Int_LCD_WriteAsciiChar(26, 10, 16, 'm', BLACK, WHITE);
    // Int_LCD_WriteAsciiChar(34, 10, 16, 'm', BLACK, WHITE);
    // Int_LCD_WriteAsciiChar(42, 10, 16, 'u', BLACK, WHITE);
    // Int_LCD_WriteAsciiChar(50, 10, 16, '_', BLACK, WHITE);

    // Int_LCD_WriteAsciiString(10, 42, 24, "Kawaii-Desu~ \nNekoLCD-Chan v1.0", BRED, WHITE);
    // Int_LCD_WriteAsciiString(10, 42+2*12, 24, "Senpai! Notice my auto-wrap", BRED, WHITE);
    //Int_Display_Mujika(0,0);

    Int_LCD_DrowPoint(10, 10, 10, GRED);
    Int_LCD_DrowLine(20, 20, 70, 70, 3, BRED);
    Int_LCD_DrowRectangle(20, 50, 160, 160, 5, BLUE);
    Int_LCD_DrowSolidCircle(160, 300, 100, 5, CYAN);
    while (1)
    {

    }
}

