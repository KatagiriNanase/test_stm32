/**
 * @file eth.c
 * @author KatagiriNanase
 * @brief
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2024 YOUR_COMPANY
 *
 */
#include "eth.h"

 //全局设置MAC地址，IP，网关，子网掩码
// uint8_t mac[6] = { 101,102,103,104,105,106 };
// uint8_t ip[4] = { 192,168,2,50 };
// uint8_t submask[4] = { 255,255,255,0 };
// uint8_t gateway[4] = { 192, 168, 2, 1 };

static wiz_NetInfo netinfo = {
    { 101,102,103,104,105,106 },
    { 192,168,2,50 },
    { 255,255,255,0 },
    { 192, 168, 2, 1 }
};
//初始化
void Int_ETH_Init()
{
    //0. 初始化SPI
    Dri_SPI_Init();
    //1.注册回调函数
    user_register_function();
    //2.复位w5500
    Int_ETH_Reset();
    // //3.设置mac地址
    // Int_ETH_SetMac();
    // //4.设置IP
    // Int_SetIP();
    wizchip_setnetinfo(&netinfo);
}

//复位 RST PG7
void Int_ETH_Reset()
{
    //通用推挽输出
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN;
    GPIOG->CRL |= GPIO_CRL_MODE7;
    GPIOG->CRL &= ~GPIO_CRL_CNF7;

    //将PG7拉低，保持500us以上
    GPIOG->ODR &= ~GPIO_ODR_ODR7;
    Com_Delay_us(800);

    //再次拉高
    GPIOG->ODR |= GPIO_ODR_ODR7;

    //复位完成
    printf("复位完成!\n");
}

//设置mac地址
// void Int_ETH_SetMac()
// {
//     printf("开始设置mac地址\n");
//     setSHAR(mac);
//     printf("完成mac设置\n");
// }
// //设置IP，子网掩码，网关
// void Int_SetIP()
// {
//     printf("开始设置ip地址\n");
//     setSIPR(ip);
//     printf("完成ip设置\n");

//     printf("开始设置子网掩码\n");
//     setSUBR(submask);
//     printf("完成子网掩码设置\n");

//     printf("开始设置网关\n");
//     setGAR(gateway);
//     printf("完成网关设置\n");

//     printf("设备IP地址：%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
// }