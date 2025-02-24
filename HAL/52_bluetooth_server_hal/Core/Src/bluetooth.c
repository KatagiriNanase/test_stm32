#include "bluetooth.h"

//��ʼ��BLEΪ�����
void Bluetooth_Init(void)
{
    ESP32_SendCmd("AT+RST\r\n");
    HAL_Delay(2000);
    /*��ʼ��BLEΪsever*/
    ESP32_SendCmd("AT+BLEINIT=2\r\n");
    printf("\n��ʼ��BLEΪsever\n");

    /*��������*/
    ESP32_SendCmd("AT+BLEGATTSSRVCRE\r\n");
    printf("\n��������\n");

    /*��������*/
    ESP32_SendCmd("AT+BLEGATTSSRVSTART\r\n");
    printf("\n��������\n");

    /*�����豸����*/
    printf("\n�����豸����\n");
    ESP32_SendCmd("AT+BLENAME=\"GATTJi\"\r\n");
    HAL_Delay(5000);

    /*�����豸��ַ��������ַ*/
    // ESP32_SendCmd("AT+BLEADDR=0\r\n");
    // printf("\n�豸��ַΪ������ַ\n");
    /*���ù㲥����*/
    ESP32_SendCmd("AT+BLEADVPARAM=50,50,0,0,7,0,,\r\n");
    printf("\n���ù㲥����\n");

    /*���ù㲥����*/
    ESP32_SendCmd("AT+BLEADVDATAEX=\"GATTJi\",\"A002\",\"0102030405\",1\r\n");
    printf("\n���ù㲥����\n");
    
    ESP32_SendCmd("AT+BLEGATTSSRV?\r\n");
    //�����Զ��崮�ڷ���
    BLE_SetupSPPService();

    /*��������״̬�ı���ʾ��Ϣ*/
    ESP32_SendCmd("AT+SYSMSG=4\r\n");

    /*��ʼ�㲥*/
    ESP32_SendCmd("AT+BLEADVSTART\r\n");
    printf("\n��ʼ�㲥\n");

}


void BLE_SetupSPPService(void)
{
    /*�������⴮�ڲ���*/
    ESP32_SendCmd("AT+BLESPPCFG=1,1,7,1,5\r\n");
    printf("\n����SSP����\n");
}

uint8_t Bluetooth_ReadData(uint8_t* rxBuff, uint16_t* rxLen)
{
    HAL_UARTEx_ReceiveToIdle(&huart2, rxBuff, 1000, rxLen, 1000);

    if (*rxLen == 0)
        return 1;

    /*�������ӱ仯*/
    if (Bluetooth_HandleConnChange())
    {
        return 2;
    }


    return 0;
}

/*����ȫ�ֻ�����*/
extern uint8_t rBuff[1000];
extern uint16_t rDataLen;
uint8_t Bluetooth_HandleConnChange(void)
{
    /*WIFI����״̬�仯�������κδ���*/
    if ((strstr((char*)rBuff, "+STA_CONNECTED") != NULL)
        || (strstr((char*)rBuff, "+STA_DISCONNECTED:") != NULL)
        || (strstr((char*)rBuff, "+DIST_STA_IP:") != NULL))
    {
        printf("\nWIFI ����״̬�����仯\n");
        return 1;
    }

    if (strstr((char*)rBuff, "+BLECONN:") != NULL)
    {
        printf("\n�������ͻ���\n");
        ESP32_SendCmd("AT+BLESPP\r\n");
        printf("\n����SSPģʽ\n");
        /*�̵�һ��>*/
        uint8_t tmp;
        HAL_UART_Receive(&huart2, &tmp, 1, 1000);
        return 1;
    }

    if (strstr((char*)rBuff, "+BLEDISCONN:") != NULL)
    {
        printf("\n�ͻ��˶Ͽ�����\n");
        HAL_UART_Transmit(&huart2, "+++", 3, 1000);
        /*���ټ��һ��*/
        HAL_Delay(2000);
        printf("\n�˳�SSPģʽ\n");
        return 1;
    }

    return 0;
}

void Bluetooth_SendData(uint8_t txBuff[], uint16_t txLen)
{
    HAL_UART_Transmit(&huart2, txBuff, txLen, 10000);
}
