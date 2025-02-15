#include "Dri_USART.h"
#include "Dri_CAN.h"
#include <string.h>
int main()
{
    /*
    Dri_USART_Init();
    printf("hello,world!\n");
    Dri_CAN_Init();
    printf("can ��ʼ���ɹ�\n");

    //��������
    uint16_t stdID = 0x66;
    uint8_t* data = "abcdefg";
    Dri_CAN_SendMsg(stdID, data, strlen((char*)data));
    printf("�������\n");

    stdID = 114;
    data = "efg";
    Dri_CAN_SendMsg(stdID, data, strlen((char*)data));
    printf("�������\n");

    stdID = 0x54;
    data = "higk";
    Dri_CAN_SendMsg(stdID, data, strlen((char*)data));
    printf("�������\n");

    RxDataMsg rxDataMsg[3];
    uint8_t count;

    //��������
    Dri_CAN_ReceiveMsg(rxDataMsg, &count);
    printf("���Ľ������\n");
    printf("���ĸ�����%d\n", count);

    for (uint8_t i = 0;i < count;++i)
        printf("����%d -stdID:%d,len:%d,data:%s\n", i + 1, rxDataMsg[i].stdId, rxDataMsg[i].len, rxDataMsg[i].data);
*/
    Dri_USART_Init();
    printf("����У׼���ļ�׵Э���� (^///^)\n");
    Dri_CAN_Init();
    printf("����Э��������ɣ��Լ�ģʽ�����ջػ�~\n");

    //��������
    uint16_t stdID = 0x7AC;
    uint8_t data[] = { 0x53,0x77,0x65,0x6C,0x6C,0x69,0x6E,0x67 }; //Swelling
    Dri_CAN_SendMsg(stdID, data, sizeof(data)/sizeof(data[0]));
    printf("1964������������ĩ����...(*??��*)\n");

    stdID = 0x266;
    uint8_t data2[] = "CipherX";
    Dri_CAN_SendMsg(stdID, data2, sizeof(data2) / sizeof(data2[0]));
    printf("����ģ�鿪ʼ��ʴǰ��ҶƤ��~(=���أ�=)\n");

    stdID = 0x7FF;
    uint8_t data3[] = { 0x87,0x40,0x87,0x40 }; //GBK����ġ�?��
    Dri_CAN_SendMsg(stdID, data3, sizeof(data3) / sizeof(data3[0]));
    printf("���Ļ��������ֵͻ��!!(///��///)\n");

    RxDataMsg rxDataMsg[3];
    uint8_t count;

    //��������
    Dri_CAN_ReceiveMsg(rxDataMsg, &count);
    printf("����%d��г���쳣��(*/�أ�*)\n", count);
    printf("�������������桿\n");

    for (uint8_t i = 0;i < count;++i)
    {
        if (rxDataMsg[i].stdId == 0x7AC)
            printf("������������Ƶ��%dHz�����ϵ����0.%d~(��?��?��)\n", rxDataMsg[i].len * 10, rxDataMsg[i].data[0]);
        else if (rxDataMsg[i].stdId == 0x266)
            printf("�����ܳ׼���ȼ�v%d.%d������ѹ�%dPa(*??��*)\n", rxDataMsg[i].data[1], rxDataMsg[i].data[0], rxDataMsg[i].len);
        else
            printf("����δ�����Ŷ������鴽����֤%d��(? ???��??? ?)\n", rxDataMsg[i].stdId);
    }

    while (1)
    {
        
    }
}