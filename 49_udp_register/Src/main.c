#include "Dri_USART.h"
#include "eth.h"
#include "udp.h" 
#include "Com_Util.h"
int main()
{
    Dri_USART_Init();

    printf("UDPЭ����Ѳ��� ����!\n");
    Int_ETH_Init();

    printf("��ʼ����̫�����\n");

    while (1)
    {
        UDP_Socket0();
    }
}