#include "tcp_server.h"

//ȫ�ֵĽ��ջ�����
static uint8_t rBuff[2048] = { 0 };
static int16_t rDataLen;

//�������ӵĿͻ���ip�Ͷ˿ں�
uint8_t clientIP[4];
uint16_t clientPort;

static int8_t openStatus;
int8_t listenStatus;
static uint8_t socketStatus;
void TCP_Server_Socket0()
{
    //1.��ȡsocket0�ĵ�ǰ״̬��Sn_SR�Ĵ���
    socketStatus = getSn_SR(0);

    //2.���ݵ�ǰ��ͬ״̬��ִ�в�ͬ�Ĳ���
    switch (socketStatus)
    {
    case SOCK_CLOSED:

        openStatus = socket(0, Sn_MR_TCP, 8080, SF_TCP_NODELAY);
        if (openStatus == 0)
            printf("socket 0 �����ɹ�\n");
        else
            printf("socket 0 ��ʧ��\n");
        break;
    case SOCK_INIT:
        //�����˳�ʼ��״̬�����Կ�ʼ����
        listenStatus = listen(0);
        if (listenStatus == SOCK_OK)
            printf("socket 0 �������״̬\n");
        else if (listenStatus == SOCK_ERROR)
            printf("socket 0 �ѹر�\n");
        else
            printf("δ֪����\n");
        break;
    case SOCK_LISTEN:
        //�ȴ��ͻ��˵�����
        break;
    case SOCK_ESTABLISHED:
        //���ӳɹ����Ȼ�ȡ�ͻ��˵�IP�Ͷ˿ں�
        getSn_DIPR(0, clientIP);
        clientPort = getSn_DPORT(0);
        //��ӡ��Ϣ
        printf("�ͻ���IP��%d.%d.%d.%d\n", clientIP[0], clientIP[1], clientIP[2], clientIP[3]);
        printf("�ͻ���Port��%d\n", clientPort);
        //��һ��ѭ���ȴ��ͻ��˷�����Ϣ
        while (1)
        {

            rDataLen = recv(0, rBuff, 2048);
            if (rDataLen < 0)
            {
                printf("socket 0 �������⣬�����رգ���������\n");
                return;
            }
            printf("���յ������ݳ���Ϊ��%d,����:%.*s\n", rDataLen, rDataLen, rBuff);
            send(0, rBuff, rDataLen);

        }
        break;
    default:
        break;
    }
}
