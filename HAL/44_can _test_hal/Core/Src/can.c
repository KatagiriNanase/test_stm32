/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
  /* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 36;
  hcan.Init.Mode = CAN_MODE_SILENT_LOOPBACK;
  hcan.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = ENABLE;
  hcan.Init.AutoWakeUp = ENABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  if (canHandle->Instance == CAN1)
  {
    /* USER CODE BEGIN CAN1_MspInit 0 */

    /* USER CODE END CAN1_MspInit 0 */
      /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

    /* USER CODE BEGIN CAN1_MspInit 1 */

    /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if (canHandle->Instance == CAN1)
  {
    /* USER CODE BEGIN CAN1_MspDeInit 0 */

    /* USER CODE END CAN1_MspDeInit 0 */
      /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);

    /* USER CODE BEGIN CAN1_MspDeInit 1 */

    /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void Can_FilterConfig()
{
  CAN_FilterTypeDef sFiterConfig;

  //过滤器组编号0
  sFiterConfig.FilterBank = 0;
  //关联的FIFO
  sFiterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  //掩码模式
  sFiterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  //位宽
  sFiterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  //过滤器组的FR1(ID) 和FR2(mask)
  sFiterConfig.FilterIdHigh = 0x0000;
  sFiterConfig.FilterIdLow = 0x0000;

  sFiterConfig.FilterMaskIdHigh = 0x00;
  sFiterConfig.FilterMaskIdLow = 0x00;

  //激活过滤器组
  sFiterConfig.FilterActivation = ENABLE;


  HAL_CAN_ConfigFilter(&hcan, &sFiterConfig);
}

void Dri_CAN_SendMsg(uint16_t stdId, uint8_t* data, uint8_t len)
{
  //等待有邮箱空闲
  while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
  {

  }
  //填入数据帧信息
  CAN_TxHeaderTypeDef txHeader;
  txHeader.StdId = stdId;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = len;

  //发送报文
  uint32_t txMailbox;
  HAL_CAN_AddTxMessage(&hcan, &txHeader, data, &txMailbox);

}


void Dri_CAN_ReceiveMsg(RxDataMsg rxDataMsg[], uint8_t* MsgCout)
{
  //获取报文个数
  *MsgCout = HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0);

  CAN_RxHeaderTypeDef rxHeader;
  //循环读取报文信息
  for (uint8_t i = 0;i < *MsgCout;++i)
  {
    HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rxHeader, rxDataMsg[i].data);
    rxDataMsg[i].stdId = rxHeader.StdId;
    rxDataMsg[i].len = rxHeader.DLC;
  }
}
/* USER CODE END 1 */
