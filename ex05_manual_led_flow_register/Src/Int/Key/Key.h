#ifndef __KEY_H__
#define __KEY_H__

#include <stm32f10x.h>
//定义流水灯状态枚举类型
typedef enum status {
    No_LED = -1,    //初始状态
    L1,             //LED1亮起
    L2,
    L3
}FLOW_STATUS;

//初始化
void Int_Key_Init();



#endif /* __KEY_H__ */