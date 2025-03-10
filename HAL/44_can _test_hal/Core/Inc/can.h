/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  /* USER CODE END Header */
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

  extern CAN_HandleTypeDef hcan;

  /* USER CODE BEGIN Private defines */
  typedef struct
  {
    uint16_t stdId;
    uint8_t data[8];
    uint8_t len;
  }RxDataMsg;
  /* USER CODE END Private defines */

  void MX_CAN_Init(void);

  /* USER CODE BEGIN Prototypes */
  void Can_FilterConfig();

  void Dri_CAN_SendMsg(uint16_t stdId, uint8_t* data, uint8_t len);


  void Dri_CAN_ReceiveMsg(RxDataMsg rxDataMsg[], uint8_t* MsgCout);
  /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

