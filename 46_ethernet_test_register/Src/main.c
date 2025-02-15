#include "Dri_USART.h"
#include "eth.h"
#include "Com_Util.h"
int main()
{
    Dri_USART_Init();

    printf("以太网协议觉醒测试 启动!\n");
    Int_ETH_Init();

    printf("初始化以太网完成\n");           
    wiz_NetInfo netinfo;
    wizchip_getnetinfo(&netinfo);
    while (1)
    {
    printf("IP: %d.%d.%d.%d\n", netinfo.ip[0], netinfo.ip[1], netinfo.ip[2], netinfo.ip[3]);
    printf("Gateway: %d.%d.%d.%d\n", netinfo.gw[0], netinfo.gw[1], netinfo.gw[2], netinfo.gw[3]);
    Com_Delay_ms(1000);
    }
}