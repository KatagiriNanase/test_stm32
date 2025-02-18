#ifndef __WEB_SERVER_H__
#define __WEB_SERVER_H__

#include "w5500.h"
#include "httpServer.h"
#include "httpParser.h"
#include <stdio.h>
#include <string.h>
#include "Int_LED.h"

//web服务器初始化
void WebServer_Init();

//启动web服务器
void WebServer_Start();
#endif /* __WEB_SERVER_H__ */
