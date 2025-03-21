#include "bkp.h"

void Dri_BKP_Init()
{
    //1.打开电源和后备域接口时钟
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    RCC->APB1ENR |= RCC_APB1ENR_BKPEN;

    //2.使能PWR_CR中的DBP，开启对后备寄存器的访问
    PWR->CR |= PWR_CR_DBP;

    //3.软件复位一次备份寄存器
    //RCC->BDCR |= RCC_BDCR_BDRST;

    Com_Delay_ms(1);

    //4.清除复位位
    //RCC->BDCR &= ~RCC_BDCR_BDRST;

}