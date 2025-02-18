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

 //ȫ������MAC��ַ��IP�����أ���������
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
//��ʼ��
void Int_ETH_Init()
{
    //0. ��ʼ��SPI
    Dri_SPI_Init();
    //1.ע��ص�����
    user_register_function();
    //2.��λw5500
    Int_ETH_Reset();
    // //3.����mac��ַ
    // Int_ETH_SetMac();
    // //4.����IP
    // Int_SetIP();
    wizchip_setnetinfo(&netinfo);
}

//��λ RST PG7
void Int_ETH_Reset()
{
    //ͨ���������
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN;
    GPIOG->CRL |= GPIO_CRL_MODE7;
    GPIOG->CRL &= ~GPIO_CRL_CNF7;

    //��PG7���ͣ�����500us����
    GPIOG->ODR &= ~GPIO_ODR_ODR7;
    Com_Delay_us(800);

    //�ٴ�����
    GPIOG->ODR |= GPIO_ODR_ODR7;

    //��λ���
    printf("��λ���!\n");
}

//����mac��ַ
// void Int_ETH_SetMac()
// {
//     printf("��ʼ����mac��ַ\n");
//     setSHAR(mac);
//     printf("���mac����\n");
// }
// //����IP���������룬����
// void Int_SetIP()
// {
//     printf("��ʼ����ip��ַ\n");
//     setSIPR(ip);
//     printf("���ip����\n");

//     printf("��ʼ������������\n");
//     setSUBR(submask);
//     printf("���������������\n");

//     printf("��ʼ��������\n");
//     setGAR(gateway);
//     printf("�����������\n");

//     printf("�豸IP��ַ��%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
// }