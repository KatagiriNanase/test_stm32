#include "Key.h"
#include "Dri_USART.h"
#include "bkp.h"
int main()
{
    Dri_USART_Init();
    Int_Key_Init();
    Dri_BKP_Init();

    //向备份域写入数据
    printf("写入数据\n");
    //BKP->DR1 = 9999;


    while (1);
}
