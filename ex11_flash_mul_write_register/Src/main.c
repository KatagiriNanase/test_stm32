#include "Dri_USART.h"
#include "w25q32.h"
#include "Com_Util.h"
#include <string.h>
#include <stm32f10x.h>
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

    //定义数据缓冲区，保存读取的数据
    uint8_t buffer[300] = { 0 };

    //构建字符串 
    uint8_t str[261];
    uint8_t a2z[27];
    for (uint8_t i = 0;i < 26;i++)
        a2z[i] = 'a' + i;

    for (uint8_t i = 0;i < 10;++i)
        strcat((char*)str, (char*)a2z);

    uint16_t len = strlen((char*)str);
    //根据地址，进行拆分，分页写入
    uint32_t addr = 0x32f680;
    uint8_t size1 = 0xff - (addr & 0xff) + 1;
    uint8_t size2 = len - size1;

    printf("size1=%d,size2=%d\n", size1, size2);

    //段擦除
    Int_W25q32_EraseSector((addr >> 16) & 0xff, (addr >> 12 & 0x0f));

    //分页写入
    Int_W25q32_RandomWrite(addr, str, size1);
    Int_W25q32_PageWrite(0x32, 0x0f, 0x07, str + size1, size2);

    //读取
    Int_W25q32_RandomRead(addr, buffer, len);

    printf("buffer=%s\n", buffer);

    while (1)
    {

    }
}