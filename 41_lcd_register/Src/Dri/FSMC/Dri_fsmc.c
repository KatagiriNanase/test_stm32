#include "Dri_fsmc.h"

void FSMC_GPIO_Init();

void Dri_FSMC_Init()
{
    //1.开启时钟
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;
    RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPEEN | RCC_APB2ENR_IOPFEN | RCC_APB2ENR_IOPGEN | RCC_APB2ENR_IOPBEN);

    //2.配置工作模式
    FSMC_GPIO_Init();

    //3. FSMC 配置 BCR4 BTCR[6]
    //3.1存储块使能
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MBKEN;

    //3.2设置存储器类型
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MTYP;

    //3.3禁止访问flash
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_FACCEN;

    //3.4数据宽度：16位
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MWID_1;
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MWID_0;

    //3.5 地址数据线不复用
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MUXEN;

    //3.6开启写使能
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_WREN;


    //4配置 BTR4 BTCR[6]
    //4.1 地址建立时间ADDSET
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_ADDSET;

    //4.2数据建立时间
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_DATAST;
    FSMC_Bank1->BTCR[7] |= 71 << 8;


}


void FSMC_GPIO_Init()
{
    //1.地址线 A0~A18 复用推挽输出 CNF10 MODE11
    //1.1 MODE=11

    GPIOG->CRL |= GPIO_CRL_MODE0;

    //1.2 CNF=10

    GPIOG->CRL |= GPIO_CRL_CNF0_1;

    GPIOG->CRL &= ~GPIO_CRL_CNF0_0;

    GPIOD->CRH |= (GPIO_CRH_CNF11_1 |
        GPIO_CRH_CNF12_1 |
        GPIO_CRH_CNF13_1
        );

    GPIOD->CRH &= ~(GPIO_CRH_CNF11_0 |
        GPIO_CRH_CNF12_0 |
        GPIO_CRH_CNF13_0
        );

    //2.数据线
    /* =============MODE=============== */
    GPIOD->CRL |= (GPIO_CRL_MODE0 |
        GPIO_CRL_MODE1);
    GPIOD->CRH |= (GPIO_CRH_MODE8 |
        GPIO_CRH_MODE9 |
        GPIO_CRH_MODE10 |
        GPIO_CRH_MODE14 |
        GPIO_CRH_MODE15);

    GPIOE->CRL |= (GPIO_CRL_MODE7);
    GPIOE->CRH |= (GPIO_CRH_MODE8 |
        GPIO_CRH_MODE9 |
        GPIO_CRH_MODE10 |
        GPIO_CRH_MODE11 |
        GPIO_CRH_MODE12 |
        GPIO_CRH_MODE13 |
        GPIO_CRH_MODE14 |
        GPIO_CRH_MODE15);

    /* =============CNF=============== */
    GPIOD->CRL |= (GPIO_CRL_CNF0_1 |
        GPIO_CRL_CNF1_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0_0 |
        GPIO_CRL_CNF1_0);

    GPIOD->CRH |= (GPIO_CRH_CNF8_1 |
        GPIO_CRH_CNF9_1 |
        GPIO_CRH_CNF10_1 |
        GPIO_CRH_CNF14_1 |
        GPIO_CRH_CNF15_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF8_0 |
        GPIO_CRH_CNF9_0 |
        GPIO_CRH_CNF10_0 |
        GPIO_CRH_CNF14_0 |
        GPIO_CRH_CNF15_0);

    GPIOE->CRL |= (GPIO_CRL_CNF7_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF7_0);

    GPIOE->CRH |= (GPIO_CRH_CNF8_1 |
        GPIO_CRH_CNF9_1 |
        GPIO_CRH_CNF10_1 |
        GPIO_CRH_CNF11_1 |
        GPIO_CRH_CNF12_1 |
        GPIO_CRH_CNF13_1 |
        GPIO_CRH_CNF14_1 |
        GPIO_CRH_CNF15_1);
    GPIOE->CRH &= ~(GPIO_CRH_CNF8_0 |
        GPIO_CRH_CNF9_0 |
        GPIO_CRH_CNF10_0 |
        GPIO_CRH_CNF11_0 |
        GPIO_CRH_CNF12_0 |
        GPIO_CRH_CNF13_0 |
        GPIO_CRH_CNF14_0 |
        GPIO_CRH_CNF15_0);

    //3.控制信号 复用推挽输出 CNF10 MODE11
    GPIOD->CRL |= (GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
    GPIOD->CRL |= (GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0);

    GPIOG->CRH |= (GPIO_CRH_MODE12);
    GPIOG->CRH |= (GPIO_CRH_CNF12_1);
    GPIOG->CRH &= ~(GPIO_CRH_CNF12_0);

    //4.复位引脚 通用推挽输出
    GPIOG->CRH |= GPIO_CRH_MODE15;
    GPIOG->CRH &=~ GPIO_CRH_CNF15;

    //4.背光亮度引脚 PB0 通用推挽输出
    GPIOB->CRL |= GPIO_CRL_MODE0;
    GPIOB->CRL &= ~GPIO_CRL_CNF0;

}