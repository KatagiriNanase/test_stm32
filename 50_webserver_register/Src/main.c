#include "Dri_USART.h"
#include "eth.h"
#include "web_server.h"
#include "Com_Util.h"
int main()
{
    Int_LED_Init();
    Dri_USART_Init();

    printf("Web Server���Ѳ��� ����!\n");
    Int_ETH_Init();

    printf("��ʼ����̫�����\n");

    WebServer_Init();
    WebServer_Start();
    while (1)
    {

    }
}