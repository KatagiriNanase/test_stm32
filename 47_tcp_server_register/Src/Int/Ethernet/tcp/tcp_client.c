#include "tcp_server.h"

//全局的接收缓冲区
uint8_t rBuff[2048] = { 0 };
int16_t rDataLen;

//服务端ip和端口号
uint8_t serverIP[4] = { 192,168,2,200 };
const uint16_t serverPort = 8080;

int8_t openStatus;
int8_t connectStatus;
uint8_t socketStatus;
void TCP_Client_Socket0()
{
    //1.获取socket0的当前状态，Sn_SR寄存器
    uint8_t socketStatus = getSn_SR(0);

    //2.根据当前不同状态，执行不同的操作
    switch (socketStatus)
    {
    case SOCK_CLOSED:

        openStatus = socket(0, Sn_MR_TCP, serverPort, SF_TCP_NODELAY);
        if (openStatus == 0)
            printf("socket 0 开启成功\n");
        else
            printf("socket 0 打开失败\n");
        break;
    case SOCK_INIT:
        //进入了初始化状态，主动连接服务器
        connectStatus = connect(0, serverIP, serverPort);
        if (connectStatus == SOCK_OK)
            printf("连接服务器成功\n");
        else
            printf("连接服务器失败\n");
        break;
    case SOCK_ESTABLISHED:
        //连接成功，发送数据
        //打印信息
        send(0, "Hello server!I am client!Give me data!\n", 39);
        //用一个循环等待服务端发送数据
        while (1)
        {
            // //等待Sn_IR RECV置1
            // while (!(getSn_IR(0) & Sn_IR_RECV))
            // {
            //     //判断如果不是连接状态，就关闭socket，并退出
            //     if (getSn_SR(0) != SOCK_ESTABLISHED)
            //     {
            //         printf("socket 0 发生意外，即将关闭，重新启动\n");
            //         close(0);
            //         return;
            //     }
            // }
            // //接收数据
            // rDataLen = getSn_RX_RSR(0);
            // if (rDataLen > 0)
            // {
            //     recv(0, rBuff, 2048);
            //     printf("接收到的数据长度为：%d,数据:%.*s\n", rDataLen, rDataLen, rBuff);
            //     send(0, rBuff, rDataLen);
            // }
            // //对RECV置1清零
            // setSn_IR(0, Sn_IR_RECV);
            rDataLen = recv(0, rBuff, 2048);
            if (rDataLen < 0)
            {
                printf("socket 0 发生意外，即将关闭，重新启动\n");
                return;
            }
            printf("接收到的数据长度为：%d,数据:%.*s\n", rDataLen, rDataLen, rBuff);
            // send(0, rBuff, rDataLen);

        }
        break;
    default:
        break;
    }
}
