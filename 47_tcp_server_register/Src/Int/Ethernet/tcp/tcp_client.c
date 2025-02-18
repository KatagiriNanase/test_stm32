#include "tcp_server.h"

//ȫ�ֵĽ��ջ�����
uint8_t rBuff[2048] = { 0 };
int16_t rDataLen;

//�����ip�Ͷ˿ں�
uint8_t serverIP[4] = { 192,168,2,200 };
const uint16_t serverPort = 8080;

int8_t openStatus;
int8_t connectStatus;
uint8_t socketStatus;
void TCP_Client_Socket0()
{
    //1.��ȡsocket0�ĵ�ǰ״̬��Sn_SR�Ĵ���
    uint8_t socketStatus = getSn_SR(0);

    //2.���ݵ�ǰ��ͬ״̬��ִ�в�ͬ�Ĳ���
    switch (socketStatus)
    {
    case SOCK_CLOSED:

        openStatus = socket(0, Sn_MR_TCP, serverPort, SF_TCP_NODELAY);
        if (openStatus == 0)
            printf("socket 0 �����ɹ�\n");
        else
            printf("socket 0 ��ʧ��\n");
        break;
    case SOCK_INIT:
        //�����˳�ʼ��״̬���������ӷ�����
        connectStatus = connect(0, serverIP, serverPort);
        if (connectStatus == SOCK_OK)
            printf("���ӷ������ɹ�\n");
        else
            printf("���ӷ�����ʧ��\n");
        break;
    case SOCK_ESTABLISHED:
        //���ӳɹ�����������
        //��ӡ��Ϣ
        send(0, "Hello server!I am client!Give me data!\n", 39);
        //��һ��ѭ���ȴ�����˷�������
        while (1)
        {
            // //�ȴ�Sn_IR RECV��1
            // while (!(getSn_IR(0) & Sn_IR_RECV))
            // {
            //     //�ж������������״̬���͹ر�socket�����˳�
            //     if (getSn_SR(0) != SOCK_ESTABLISHED)
            //     {
            //         printf("socket 0 �������⣬�����رգ���������\n");
            //         close(0);
            //         return;
            //     }
            // }
            // //��������
            // rDataLen = getSn_RX_RSR(0);
            // if (rDataLen > 0)
            // {
            //     recv(0, rBuff, 2048);
            //     printf("���յ������ݳ���Ϊ��%d,����:%.*s\n", rDataLen, rDataLen, rBuff);
            //     send(0, rBuff, rDataLen);
            // }
            // //��RECV��1����
            // setSn_IR(0, Sn_IR_RECV);
            rDataLen = recv(0, rBuff, 2048);
            if (rDataLen < 0)
            {
                printf("socket 0 �������⣬�����رգ���������\n");
                return;
            }
            printf("���յ������ݳ���Ϊ��%d,����:%.*s\n", rDataLen, rDataLen, rBuff);
            // send(0, rBuff, rDataLen);

        }
        break;
    default:
        break;
    }
}
