#include "rtc.h"

void Dri_RTC_Init()
{
    //1.配置时钟
    RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    //2.关闭写保护
    PWR->CR |= PWR_CR_DBP;
    // // 1.3 复位整个备份域
    // RCC->BDCR |= RCC_BDCR_BDRST;

    // // 1.4 解除备份域复位
    // RCC->BDCR &= ~RCC_BDCR_BDRST;
    /* 选择外部低速时钟 */

    RCC->BDCR &= ~RCC_BDCR_RTCSEL;
    RCC->BDCR |= RCC_BDCR_RTCSEL_0;

    /* 开启外部低速时钟使能 */
    RCC->BDCR |= RCC_BDCR_LSEON;

    /* 等待LSE就绪 */
    while (!(RCC->BDCR & RCC_BDCR_LSERDY))
    {

    }
    RCC->BDCR |= RCC_BDCR_RTCEN;
    //4.配置RTC闹钟模式
    /* 等待RTC寄存器上一次更新完成 */
    while (!(RTC->CRL & RTC_CRL_RTOFF))
    {

    }
    /* 置为CNF，进入配置模式 */
    RTC->CRL |= RTC_CRL_CNF;

    /* 配置分频系数32767 */
    RTC->PRLL = 0x7fff;
    RTC->PRLH = 0;
    /* 计数寄存器默认为0 */

    /* 开启闹钟中断 */
    //RTC->CRH |= RTC_CRH_ALRIE;

    /* 关闭CNF，等待写入完成*/
    RTC->CRL &= ~RTC_CRL_CNF;
    printf("1");
    while (!(RTC->CRL & RTC_CRL_RTOFF))
    {

    }
    // printf("1");
    //5.配置NVIC
    // NVIC_SetPriorityGrouping(3);
    // NVIC_SetPriority(RTC_IRQn, 3);
    // NVIC_EnableIRQ(RTC_IRQn);

}

void Drt_RTC_SetALR(uint32_t second)
{
    /* 等待RTC寄存器上一次更新完成 */
    while (!(RTC->CRL & RTC_CRL_RTOFF))
    {

    }
    /* 置为CNF，进入配置模式 */
    RTC->CRL |= RTC_CRL_CNF;
    /* 计数器 */
    RTC->CNTH = 0;
    RTC->CNTL = 0;

    /* 配置闹钟秒数 */
    second -= 1;
    RTC->ALRH = (second >> 16) & 0xffff;
    RTC->ALRL = (second >> 0) & 0xffff;

    /* 关闭CNF，等待写入完成*/
    RTC->CRL &= ~RTC_CRL_CNF;
    while (!(RTC->CRL & RTC_CRL_RTOFF))
    {

    }
}

void Dri_RTC_SetTimeStamp(uint32_t timeStamp)
{
    /* 等待RTC寄存器上一次更新完成 */
    while (!(RTC->CRL & RTC_CRL_RTOFF))
    {

    }
    /* 置为CNF，进入配置模式 */
    RTC->CRL |= RTC_CRL_CNF;
    /* 计数器 */
    RTC->CNTH = (timeStamp >> 16) & 0xffff;
    RTC->CNTL = (timeStamp >> 0) & 0xffff;

    /* 关闭CNF，等待写入完成*/
    RTC->CRL &= ~RTC_CRL_CNF;
    while (!(RTC->CRL & RTC_CRL_RTOFF))
    {

    }
}

void Dri_RTC_GetDateTime(DateTime* datetime)
{
    /* 获取当前时间戳 */
    uint32_t ts;
    /* 等待寄存器同步后才能读取寄存器 */
    while (!(RTC->CRL & RTC_CRL_RSF))
    {

    }

    ts = (RTC->CNTH << 16) | (RTC->CNTL << 0);

    struct tm* ptm = localtime((time_t*)&ts);

    /* 整合为自己的时间 */
    datetime->year = ptm->tm_year + 1900;
    datetime->month = ptm->tm_mon + 1;
    datetime->day = ptm->tm_mday;
    datetime->hour = ptm->tm_hour;
    datetime->minute = ptm->tm_min;
    datetime->second = ptm->tm_sec;

}

// void RTC_IRQHandler()
// {
//     if (RTC->CRL & RTC_CRL_ALRF)
//     {
//         //Dri_USART_Init();
//         /* 清除标志位 */
//         RTC->CRL &= ~RTC_CRL_ALRF;
//         // Drt_RTC_SetALR(5);
//         //printf("into RTC interrupt handler,wake up\n");
//         flag = 1;

//     }
// }