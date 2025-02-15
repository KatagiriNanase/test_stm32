#include "Dri_CAN.h"

/**
 *@brief can initialize
 *
 */
void Dri_CAN_Init()
{
    //1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    //2.配置PB8 浮空输入 MODE00 CNF01   PB9 复用推挽输出 MODE11 CNF10
    GPIOB->CRH |= GPIO_CRH_MODE9;
    GPIOB->CRH |= GPIO_CRH_CNF9_1;
    GPIOB->CRH &= ~GPIO_CRH_CNF9_0;

    GPIOB->CRH &= ~GPIO_CRH_MODE8;
    GPIOB->CRH &= ~GPIO_CRH_CNF8_1;
    GPIOB->CRH |= GPIO_CRH_CNF8_0;
    //3.配置AFIO重映射
    AFIO->MAPR |= AFIO_MAPR_CAN_REMAP_1;
    AFIO->MAPR &= ~AFIO_MAPR_CAN_REMAP_0;

    //4.CAN配置
    //4.1 控制器1
    //4.1.1 进入初始化模式
    CAN1->MCR |= CAN_MCR_INRQ;
    while (!(CAN1->MSR & CAN_MSR_INAK))
    {

    }
    //4.1.2 退出睡眠模式
    CAN1->MCR &= ~CAN_MCR_SLEEP;
    while(CAN1->MSR & CAN_MSR_SLAK)
    {

    }

    //4.1.2 自动离线管理
    CAN1->MCR |= CAN_MCR_ABOM;
    //4.1.3 自动唤醒模式
    CAN1->MCR |= CAN_MCR_AWUM;

    //4.1.3 配置位时序 BTR Tq=1us 
    CAN1->BTR |= (CAN_BTR_SILM | CAN_BTR_LBKM);
    CAN1->BTR &= ~CAN_BTR_BRP;
    CAN1->BTR |= 35 << 0;

    CAN1->BTR &= ~CAN_BTR_TS1;
    CAN1->BTR |= 3 << 16; //TS1=3+1Tq
    CAN1->BTR &= ~CAN_BTR_TS2;
    CAN1->BTR |= 6 << 20; //TS2=6+1Tq

    CAN1->BTR &= ~CAN_BTR_SJW; //重新同步跳跃宽度
    CAN1->BTR |= 2 << 24;

    //4.1.4 退出初始化模式
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while (CAN1->MSR & CAN_MSR_INAK)
    {

    }

    //4.2 配置过滤器
    //4.2.1 进入初始化模式
    CAN1->FMR |= CAN_FMR_FINIT;

    //4.2.2 配置过滤器组0工作模式：0--屏蔽位模式
    CAN1->FM1R &= ~CAN_FM1R_FBM1;

    //4.2.3 配置过滤器位宽 1- 1个32位的寄存器
    CAN1->FS1R |= CAN_FS1R_FSC0;

    //4.2.4 配置过滤器组关联的FIFO
    CAN1->FFA1R &= ~CAN_FFA1R_FFA0;

    //4.2.5设置F0R1:ID
    CAN1->sFilterRegister[0].FR1 = 0x00000000;

    //4.2.6设置屏蔽位FOR2:mask
    CAN1->sFilterRegister[0].FR2 = 0x00000000;

    //4.2.7 激活过滤器组0
    CAN1->FA1R |= CAN_FA1R_FACT0;

    //4.2.8 退出初始化模式
    CAN1->FMR &= ~CAN_FMR_FINIT;



}

/**
 *@brief 发送报文
 *
 * @param stdId 标准帧id（11位）
 * @param data 发送的数据指针
 * @param len 数据的长度（0~8byte）
 */
void Dri_CAN_SendMsg(uint16_t stdId, uint8_t* data, uint8_t len)
{
    //判断长度如果大于8 
    if (len > 8)
    {
        printf("error:len is %d,bigger 0~8 byte!\n",len);
        return;
    }

    //1.判断TME状态，等待邮箱0为空
    while (!(CAN1->TSR & CAN_TSR_TME0))
    {

    }

    //2.填入数据帧信息
    //2.1 IDE标准
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_IDE;
    //2.2 发送请求为数据帧
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_RTR;
    //2.3 设置发送的ID
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_STID;
    CAN1->sTxMailBox[0].TIR |= (stdId << 21);
    //2.4 设置数据发送的长度
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
    CAN1->sTxMailBox[0].TDTR |= len;
    //2.5 放置数据到数据寄存器
    CAN1->sTxMailBox[0].TDLR = 0;
    CAN1->sTxMailBox[0].TDHR = 0;
    for (uint8_t i = 0;i < len;++i)
    {
        if (i < 4)
            CAN1->sTxMailBox[0].TDLR |= (data[i] << 8 * i);
        else
            CAN1->sTxMailBox[0].TDHR |= (data[i] << 8 * (i - 4));

    }

    //3.激活邮箱发送
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;

}


/**
 *@brief 接收报文，将FIFO里所有的报文都接收到
 *
 * @param rxDataMsg 结构体数组
 * @param MsgCout a pointer to the addr of the msg`s size
 */
void Dri_CAN_ReceiveMsg(RxDataMsg rxDataMsg[], uint8_t* MsgCout)
{
    //1.获取FIFO中的报文个数
    *MsgCout = CAN1->RF0R & CAN_RF0R_FMP0;

    //2.循环读取每个报文
    for (uint8_t i = 0;i < *MsgCout;++i)
    {
        //1.读取ID
        rxDataMsg[i].stdId = (CAN1->sFIFOMailBox[0].RIR & CAN_RI0R_STID) >> 21;
        //2.读取报文字节长度
        rxDataMsg[i].len = CAN1->sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC;
        //清空data
        memset(rxDataMsg[i].data, 0, 8);
        //3.读取FIFO中数据寄存器的data

        uint32_t low = CAN1->sFIFOMailBox[0].RDLR;
        uint32_t high = CAN1->sFIFOMailBox[0].RDLR;

        for (uint8_t j = 0;j < rxDataMsg[i].len;++j)
        {
            if (j < 4)
                (rxDataMsg[i].data)[j] = (low >> (j * 8)) & 0xff;

            else
                (rxDataMsg[i].data)[j] = (high >> ((j - 4) * 8)) & 0xff;

        }

        //4. 出队！！
        CAN1->RF0R |= CAN_RF0R_RFOM0;

    }

}