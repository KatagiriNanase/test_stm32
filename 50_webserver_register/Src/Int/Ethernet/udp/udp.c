#include "udp.h"

//ȫ�ֵĽ��ջ�����
static uint8_t rBuff[2048] = { 0 };
static int16_t rDataLen;

//�������ӵĿͻ���ip�Ͷ˿ں�
uint8_t fromIP[4];
uint16_t fromPort;

static int8_t openStatus;
static uint8_t socketStatus;
void UDP_Socket0()
{
    //1.��ȡsocket0�ĵ�ǰ״̬��Sn_SR�Ĵ���
    socketStatus = getSn_SR(0);

    //2.���ݵ�ǰ��ͬ״̬��ִ�в�ͬ�Ĳ���
    switch (socketStatus)
    {
    case SOCK_CLOSED:

        openStatus = socket(0, Sn_MR_UDP, 8080, 0);
        if (openStatus == 0)
            printf("socket 0 �����ɹ�\n");
        else
            printf("socket 0 ��ʧ��\n");
        break;
    case SOCK_UDP:
        printf("����udpЭ��ģʽ\n");            
        //��һ��ѭ���ȴ��ͻ��˷�����Ϣ
        while (1)
        {

            rDataLen = recvfrom(0, rBuff, 2048, fromIP, &fromPort);
            if (rDataLen < 0)
            {
                printf("socket 0 �������⣬�����رգ���������\n");
                return;
            }
            printf("���յ�����IP:%d.%d.%d.%d���˿�Ϊ��%d������\n", fromIP[0], fromIP[1], fromIP[2], fromIP[3], fromPort);
            printf("���ݳ���:%d,����:%.*s", rDataLen, strlen((char*)rBuff), rBuff);
            sendto(0, rBuff, strlen((char*)rBuff), fromIP, fromPort);

        }
        break;
    default:
        break;
    }
}
