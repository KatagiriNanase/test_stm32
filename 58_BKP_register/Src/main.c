#include "Key.h"
#include "Dri_USART.h"
#include "bkp.h"
int main()
{
    Dri_USART_Init();
    Int_Key_Init();
    Dri_BKP_Init();

    //�򱸷���д������
    printf("д������\n");
    //BKP->DR1 = 9999;


    while (1);
}
