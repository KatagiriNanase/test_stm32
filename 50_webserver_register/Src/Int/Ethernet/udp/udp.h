#ifndef __UDP_H__
#define __UDP_H__

#include "socket.h"
#include "wizchip_conf.h"
#include "w5500.h"
#include <stdio.h>
#include <stm32f10x.h>
#include <string.h>
//根据当前状态，执行socket0的相关操作
void UDP_Socket0();

#endif /* __UDP_H__ */