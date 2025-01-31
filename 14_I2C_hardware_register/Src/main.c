#include "Dri_USART.h"
#include "m24c02.h"

int main()
{
    Dri_USART_Init();
    Int_M24C02_Init();

    printf("I2CЭ����Ѳ��� ����!\n");
    //Com_Delay_ms(200);
    //printf("�ؤ���I?C����С��Ҳ̫���ˤ�裡���⥯���å�������ô��룬�����ҿ����ܲ��ܶ������������ͤã�(�৥?)?�С�\n");

    //1.��EEPROMд�뵥���ֽ�
    Int_M24C02_WriteByte(0x00, 'a');
    Int_M24C02_WriteByte(0x01, 'b');
    Int_M24C02_WriteByte(0x02, 'c');

    //2.��ȡ�ַ�
    uint8_t byte1 = Int_M24C02_ReadByte(0x00);
    uint8_t byte2 = Int_M24C02_ReadByte(0x01);
    uint8_t byte3 = Int_M24C02_ReadByte(0x02);

    //3.���������ӡ
    printf("byte1=%c\t byte2=%c\t byte3=%c\n", byte1, byte2, byte3);

    //4.д���ַ���
    Int_M24C02_WriteBytes(0x00, "123456", 6);

    //5.��ȡ����ֽ�
    uint8_t buffer[100] = { 0 };
    Int_M24C02_ReadBytes(0x00, buffer, 6);
    printf("buffer=%s\n", buffer);
    while (1)
    {

    }
}