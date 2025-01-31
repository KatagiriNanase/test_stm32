#ifndef __KEY_H__
#define __KEY_H__

#include <stm32f10x.h>
typedef enum state {
    NoFlow = -1,//初始无灯状态
    state1,//plans中的第一套方案
    state2,
    state3
}STATE;
//初始化
void Int_Key_Init();


#endif /* __KEY_H__ */