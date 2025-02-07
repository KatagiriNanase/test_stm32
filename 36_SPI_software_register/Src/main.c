#include "Dri_USART.h"
#include "w25q32.h"
int main()
{
    Dri_USART_Init();
    Int_W25q32_Init();

    printf("SPI协议觉醒测试 启动!\n");
    Com_Delay_ms(200);
    //printf("へぇ～I?C这种小事也太简单了わよ！你这クソッタレ的破烂代码，就让我看看能不能动起来んだからねっ！(｀Д?)?⌒☆\n");

    //2.测试 读取ID
    uint8_t mid = 0;
    uint16_t did = 0;
    //printf("读取Flash ID中... 这可是比EVA的S2机关还要精密的操作哦！\n");
    Int_W25q32_ReadID(&mid, &did);
    printf("mid = %#x did = %#x\n", mid, did);

    //段擦除
    Int_W25q32_EraseSector(0, 0);

    //页写
    Int_W25q32_PageWrite(0, 0, 0, "54875412", 8);

    //读取
    uint8_t data[10] = { 0 };
    Int_W25q32_Read(0, 0, 0, 2, data, 6);
    printf("buffer = %s\n", data);
    while (1)
    {

    }
}