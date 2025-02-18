#include "tcp_server.h"

//全局的接收缓冲区
static uint8_t rBuff[2048] = { 0 };
static int16_t rDataLen;

//保存连接的客户端ip和端口号
uint8_t clientIP[4];
uint16_t clientPort;

static int8_t openStatus;
int8_t listenStatus;
static uint8_t socketStatus;
void TCP_Server_Socket0()
{
    //1.获取socket0的当前状态，Sn_SR寄存器
    socketStatus = getSn_SR(0);

    //2.根据当前不同状态，执行不同的操作
    switch (socketStatus)
    {
    case SOCK_CLOSED:

        openStatus = socket(0, Sn_MR_TCP, 8080, SF_TCP_NODELAY);
        if (openStatus == 0)
            printf("socket 0 开启成功\n");
        else
            printf("socket 0 打开失败\n");
        break;
    case SOCK_INIT:
        //进入了初始化状态，可以开始监听
        listenStatus = listen(0);
        if (listenStatus == SOCK_OK)
            printf("socket 0 进入监听状态\n");
        else if (listenStatus == SOCK_ERROR)
            printf("socket 0 已关闭\n");
        else
            printf("未知错误\n");
        break;
    case SOCK_LISTEN:
        //等待客户端的请求
        break;
    case SOCK_ESTABLISHED:
        //连接成功，先获取客户端的IP和端口号
        getSn_DIPR(0, clientIP);
        clientPort = getSn_DPORT(0);
        //打印信息
        printf("客户端IP：%d.%d.%d.%d\n", clientIP[0], clientIP[1], clientIP[2], clientIP[3]);
        printf("客户端Port：%d\n", clientPort);
        //用一个循环等待客户端发送消息
        while (1)
        {

            rDataLen = recv(0, rBuff, 2048);
            if (rDataLen < 0)
            {
                printf("socket 0 发生意外，即将关闭，重新启动\n");
                return;
            }
            printf("接收到的数据长度为：%d,数据:%.*s\n", rDataLen, rDataLen, rBuff);
            send(0, rBuff, rDataLen);

        }
        break;
    default:
        break;
    }
}
