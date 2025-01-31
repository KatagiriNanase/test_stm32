#include "Dri_USART.h"
#include "m24c02.h"
#include "Int_LED.h"
#include "Dri_I2C.h"
#include "Key.h"
#include <string.h>
//����ȫ�ֱ���
uint16_t leds[] = { LED1,LED2,LED3 };
uint8_t buffer[100];
uint8_t size;
uint8_t isOver;        //������ɱ�־
uint8_t count;
//�ö�ά���鱣����ˮ�Ʒ���
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
    printf("��~���������Ȼ��������С����������ƣ�\n");
    Com_Delay_ms(4000);
    //��EEPROM��ȡ��ˮ�Ʒ���
    printf("(�R?�Q)?�ݡ�������ʼ����������߳�play�浵����\n");
    Com_Delay_ms(4000);


    Int_M24C02_ReadBytes(0x00, buffer, 11);
    if (buffer[0])
    {
        printf("����~EEPROM��������ϴα����������õ��ܷ߳����أ�(///?//) \n");
        Com_Delay_ms(4000);


        AynalyseStr();
    }
    else
    {
        printf("�G�������տ���Ҳ?��1bit��û���£�\n�����Ȼ���ڴ������\n");
        Com_Delay_ms(4000);

    }

    while (1)
    {
        if (isOver)
        {
            //���浽EEPROM
            Int_M24C02_WriteBytes(0x00, buffer, size);
            //��ձ�־λ������size,count
            count = 0;
            size = 0;
            //����isOver
            isOver = 0;
            //������ǰ�ַ������ı���ˮ��״̬
            AynalyseStr(buffer);
        }

        ShowFlowLeds(LedState);

    }
}

//��buffer�еķ�������plans������
void AynalyseStr()
{
    if (!buffer[0])
    {
        printf("RGB��������̮�������...3�����שͷ�Ų��ţ�(�p���ա�)\n");
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
            printf("������ݡ�ݮ�Ľ���֮��~��û����͵͵��������أ�(/ /^/w/^/ /) \n");
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
            printf("���ۣ�����Ҫ�ڿ������Ϸ�ֳ������(��?��)������...\n");
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
            printf("������뺣�����ı�ɳ��ϣ�(?�R?�Q)?\n");
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