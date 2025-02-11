#include "Dri_USART.h"
#include "w25q32.h"
#include "Com_Util.h"
#include <string.h>
#include <stm32f10x.h>
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

    //�������ݻ������������ȡ������
    uint8_t buffer[300] = { 0 };

    //�����ַ��� 
    uint8_t str[261];
    uint8_t a2z[27];
    for (uint8_t i = 0;i < 26;i++)
        a2z[i] = 'a' + i;

    for (uint8_t i = 0;i < 10;++i)
        strcat((char*)str, (char*)a2z);

    uint16_t len = strlen((char*)str);
    //���ݵ�ַ�����в�֣���ҳд��
    uint32_t addr = 0x32f680;
    uint8_t size1 = 0xff - (addr & 0xff) + 1;
    uint8_t size2 = len - size1;

    printf("size1=%d,size2=%d\n", size1, size2);

    //�β���
    Int_W25q32_EraseSector((addr >> 16) & 0xff, (addr >> 12 & 0x0f));

    //��ҳд��
    Int_W25q32_RandomWrite(addr, str, size1);
    Int_W25q32_PageWrite(0x32, 0x0f, 0x07, str + size1, size2);

    //��ȡ
    Int_W25q32_RandomRead(addr, buffer, len);

    printf("buffer=%s\n", buffer);

    while (1)
    {

    }
}