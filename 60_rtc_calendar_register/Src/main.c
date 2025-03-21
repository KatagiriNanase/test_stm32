#include "Com_Util.h"
#include "rtc.h"
#include "Int_lcd.h"
#include "TIM5.h"
#include "Int_LED.h"
#include "TIM3.h"
#include "Key.h"
DateTime datetime;
uint8_t flag = 0;
//ȫ��״̬ ��ʾ����������
uint8_t isAdd = 0;
uint8_t isMinus = 0;
int main()
{
    Int_LED_Init();
    Dri_TIM5_Init();
    Int_Key_Init();
    Dri_TIM3_Init();
    //������ʱ��
    Dri_TIM5_Start();
    Dri_TIM3_Start();
    //����ռ�ձȺͱ仯����
    uint8_t dutycycle = 0;
    int8_t step = -1;
    //������ʱ��
    //���屳������
    uint8_t BgBright = 0;

    Int_LCD_Init();
    //Dri_RTC_SetTimeStamp(1741022658);
    uint8_t info[100];
    Int_LCD_ClearAll(WHITE);
    Int_Display_Mujika(0, 0);
    while (1)
    {
        Dri_RTC_GetDateTime(&datetime);
        sprintf((char*)info, "%04d-%02d-%02d %02d:%02d:%02d",
            datetime.year, datetime.month, datetime.day,
            datetime.hour, datetime.minute, datetime.second);
        Int_LCD_WriteAsciiString(50, 40, 24, info, BLUE, WHITE);

        if (dutycycle <= 0 || dutycycle >= 99)
            step = -step;
        dutycycle += step;

        Dri_TIM5_SetCH2DutyCycle(dutycycle);
        Dri_TIM5_SetCH1DutyCycle(100 - dutycycle);

        if (isAdd)
        {
            isAdd = 0;
            BgBright = (BgBright + 10 > 99) ? 99 : BgBright + 10;
            Dri_TIM3_SetDutyCycle(BgBright);
        }

        if (isMinus)
        {
            isMinus = 0;
            BgBright = (BgBright - 10 < 0) ? 0 : BgBright - 10;
            Dri_TIM3_SetDutyCycle(BgBright);
        }
        //���ֵ�ǰ��ռ�ձ���һ�ᣬ̫���л��˿��������Ȳ�
        Com_Delay_ms(16);

    }
}

//������
// 0XEF, 0X7E,
// 0X94, 0XB8, 0X52
// 0X3F,0XBF