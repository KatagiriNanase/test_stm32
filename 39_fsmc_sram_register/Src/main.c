#include "Dri_USART.h"
#include "Dri_fsmc.h"
#include "Com_Util.h"

//方式1：使用关键字 __attribute__ at 指定全局变量的地址
uint8_t v1 __attribute__((at(0x68000000)));
uint8_t v2 __attribute__((at(0x68000004)));

uint16_t v3 = 30;
int main()
{
    Dri_USART_Init();
    Dri_FSMC_Init();
    printf("| SRAM 自检通过  | FLASH 校验完成 |\n");
    printf(">> FSMC骑兵团已就绪 <<\n");

    v1 = 10;
    v2 = 20;

    uint8_t v4 __attribute__((at(0x68000008)));
    v4 = 40;
    uint8_t v5 = 50;
    printf("v1=%d,@%p\n", v1, &v1);
    printf("v2=%d,@%p\n", v2, &v2);
    printf("v3=%d,@%p\n", v3, &v3);
    printf("v4=%d,@%p\n", v4, &v4);
    printf("v5=%d,@%p\n", v5, &v5);

    //方式二：定义指针
    uint8_t* p = (uint8_t*)0x68000001;
    *p = 100;
    printf("*p=%d,@%p\n", *p, p);


    while (1)
    {

    }
}