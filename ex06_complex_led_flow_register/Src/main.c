#include "Dri_USART.h"
#include "m24c02.h"
#include "Int_LED.h"
#include "Dri_I2C.h"
#include "Key.h"
#include <string.h>
//定义全局变量
uint16_t leds[] = { LED1,LED2,LED3 };
uint8_t buffer[100];
uint8_t size;
uint8_t isOver;        //接收完成标志
uint8_t count;
//用二维数组保存流水灯方案
uint16_t plans[3][2];

STATE LedState = NoFlow;

void AynalyseStr();
// void SelLedsState(uint8_t state);
void ShowFlowLeds(enum state State);

int main()
{
    Dri_USART_Init();
    Int_M24C02_Init();
    Int_LED_Init();
    Int_Key_Init();
    printf("哼~区区人类居然敢启动本小姐的流光幻舞灯！\n");
    Com_Delay_ms(4000);
    //从EEPROM读取流水灯方案
    printf("(≧?≦)?咻——！开始检索杂鱼の羞耻play存档啦～\n");
    Com_Delay_ms(4000);


    Int_M24C02_ReadBytes(0x00, buffer, 11);
    if (buffer[0])
    {
        printf("嗅嗅~EEPROM里残留着上次笨蛋人类设置的羞耻方案呢！(///?//) \n");
        Com_Delay_ms(4000);


        AynalyseStr();
    }
    else
    {
        printf("欸——！空空如也?连1bit都没留下！\n杂鱼果然是内存金鱼吗！\n");
        Com_Delay_ms(4000);

    }

    while (1)
    {
        if (isOver)
        {
            //保存到EEPROM
            Int_M24C02_WriteBytes(0x00, buffer, size);
            //清空标志位，重置size,count
            count = 0;
            size = 0;
            //重置isOver
            isOver = 0;
            //解析当前字符串并改变流水灯状态
            AynalyseStr(buffer);
        }

        ShowFlowLeds(LedState);

    }
}

//将buffer中的方案载入plans数组中
void AynalyseStr()
{
    if (!buffer[0])
    {
        printf("RGB粒子正在坍缩成奇点...3秒后变成砖头信不信！(╬☉д⊙)\n");
        Com_Delay_ms(4000);

        return;
    }
    LedState = state1;

    sscanf((char*)buffer, "%d,%d#%d,%d#%d,%d",
        &plans[0][0], &plans[0][1],
        &plans[1][0], &plans[1][1],
        &plans[2][0], &plans[2][1]);
    for (uint8_t i = 0;i < 3;++i)
    {
        for (uint8_t j = 0;j < 2;++j)
        {
            switch (plans[i][j])
            {
            case 1:
                plans[i][j] = LED1;
                break;
            case 2:
                plans[i][j] = LED2;
                break;
            case 3:
                plans[i][j] = LED3;
                break;
            default:
                break;
            }
        }
    }
}

// void SelLedsState(STATE state)
// {
//     state = 1;
// }

void ShowFlowLeds(STATE state)
{

    switch (state)
    {
    case state1:
        if (!count)
        {
            printf("金☆黄与草☆莓的禁忌之恋~才没有在偷偷光合作用呢！(/ /^/w/^/ /) \n");
            count = 1;
        }
        Int_LED_OffAll(leds, 3);
        for (uint8_t i = 0;i < 2;++i)
        {
            Int_LED_On(plans[state1][i]);
            Com_Delay_ms(500);
            Int_LED_Off(plans[state1][i]);
        }
        break;
    case state2:
        if (!count)
        {
            count = 1;
            printf("呜哇！藻类要在开发板上繁殖了啦！(⊙?⊙)唰啦唰啦...\n");
        }
        Int_LED_OffAll(leds, 3);
        for (uint8_t i = 0;i < 2;++i)
        {
            Int_LED_On(plans[1][i]);
            Com_Delay_ms(500);
            Int_LED_Off(plans[1][i]);
        }
        break;
    case state3:
        if (!count)
        {
            count = 1;
            printf("柠☆黄与海☆蓝的冰沙混合！(?≧?≦)?\n");
        }
        Int_LED_OffAll(leds, 3);
        for (uint8_t i = 0;i < 2;++i)
        {
            Int_LED_On(plans[2][i]);
            Com_Delay_ms(500);
            Int_LED_Off(plans[2][i]);
        }
    default:
        break;
    }
}