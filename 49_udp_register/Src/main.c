#include "Dri_USART.h"
#include "eth.h"
#include "udp.h" 
#include "Com_Util.h"
int main()
{
    Dri_USART_Init();

    printf("UDP协议觉醒测试 启动!\n");
    Int_ETH_Init();

    printf("初始化以太网完成\n");

    while (1)
    {
        UDP_Socket0();
    }
}