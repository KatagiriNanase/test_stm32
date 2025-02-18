#include "Dri_USART.h"
#include "eth.h"
#include "tcp_client.h" 
#include "Com_Util.h"
int main()
{
    Dri_USART_Init();

    printf("TCP协议觉醒测试 启动!\n");
    Int_ETH_Init();

    printf("初始化以太网完成\n");
    wiz_NetInfo netinfo;
    wizchip_getnetinfo(&netinfo);
    printf("IP: %d.%d.%d.%d\n", netinfo.ip[0], netinfo.ip[1], netinfo.ip[2], netinfo.ip[3]);
    printf("Gateway: %d.%d.%d.%d\n", netinfo.gw[0], netinfo.gw[1], netinfo.gw[2], netinfo.gw[3]);
    while (1)
    {
        TCP_Client_Socket0();
    }
}