#ifndef __DRI_CAN_H__
#define __DRI_CAN_H__

#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>
typedef struct
{
    uint16_t stdId;
    uint8_t data[8];
    uint8_t len;
}RxDataMsg;


void Dri_CAN_Init();

void Dri_CAN_SendMsg(uint16_t stdId, uint8_t* data, uint8_t len);


void Dri_CAN_ReceiveMsg(RxDataMsg rxDataMsg[], uint8_t* MsgCout);

#endif /* __DRI_CAN_H__ */