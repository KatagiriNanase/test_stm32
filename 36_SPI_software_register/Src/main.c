#include "Dri_USART.h"
#include "w25q32.h"
int main()
{
    Dri_USART_Init();
    Int_W25q32_Init();

    printf("SPIЭ����Ѳ��� ����!\n");
    Com_Delay_ms(200);
    //printf("�ؤ���I?C����С��Ҳ̫���ˤ�裡���⥯���å�������ô��룬�����ҿ����ܲ��ܶ������������ͤã�(�৥?)?�С�\n");

    //2.���� ��ȡID
    uint8_t mid = 0;
    uint16_t did = 0;
    //printf("��ȡFlash ID��... ����Ǳ�EVA��S2���ػ�Ҫ���ܵĲ���Ŷ��\n");
    Int_W25q32_ReadID(&mid, &did);
    printf("mid = %#x did = %#x\n", mid, did);

    //�β���
    Int_W25q32_EraseSector(0, 0);

    //ҳд
    Int_W25q32_PageWrite(0, 0, 0, "54875412", 8);

    //��ȡ
    uint8_t data[10] = { 0 };
    Int_W25q32_Read(0, 0, 0, 2, data, 6);
    printf("buffer = %s\n", data);
    while (1)
    {

    }
}