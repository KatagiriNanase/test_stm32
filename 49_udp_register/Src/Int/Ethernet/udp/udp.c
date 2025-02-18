#include "udp.h"

//全局的接收缓冲区
static uint8_t rBuff[2048] = { 0 };
static int16_t rDataLen;

//保存连接的客户端ip和端口号
uint8_t fromIP[4];
uint16_t fromPort;

static int8_t openStatus;
static uint8_t socketStatus;
void UDP_Socket0()
{
    //1.获取socket0的当前状态，Sn_SR寄存器
    socketStatus = getSn_SR(0);

    //2.根据当前不同状态，执行不同的操作
    switch (socketStatus)
    {
    case SOCK_CLOSED:

        openStatus = socket(0, Sn_MR_UDP, 8080, 0);
        if (openStatus == 0)
            printf("socket 0 开启成功\n");
        else
            printf("socket 0 打开失败\n");
        break;
    case SOCK_UDP:
        printf("进入udp协议模式\n");            
        //用一个循环等待客户端发送消息
        while (1)
        {

            rDataLen = recvfrom(0, rBuff, 2048, fromIP, &fromPort);
            if (rDataLen < 0)
            {
                printf("socket 0 发生意外，即将关闭，重新启动\n");
                return;
            }
            printf("接收到来自IP:%d.%d.%d.%d，端口为：%d的数据\n", fromIP[0], fromIP[1], fromIP[2], fromIP[3], fromPort);
            printf("数据长度:%d,数据:%.*s", rDataLen, strlen((char*)rBuff), rBuff);
            sendto(0, rBuff, strlen((char*)rBuff), fromIP, fromPort);

        }
        break;
    default:
        break;
    }
}
