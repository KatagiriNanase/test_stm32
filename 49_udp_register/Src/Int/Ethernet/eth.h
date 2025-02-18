#ifndef __ETH_H__
#define __ETH_H__

#include <stm32f10x.h>
#include "w5500.h"
#include "Com_util.h"
#include "Dri_USART.h"
#include "Dri_spi.h"
#include "wizchip_conf.h"


//初始化
void Int_ETH_Init();

//复位
void Int_ETH_Reset();

//设置mac地址
void Int_ETH_SetMac();
//设置IP，子网掩码，网关
void Int_SetIP();
#endif /* __ETH_H__ */
