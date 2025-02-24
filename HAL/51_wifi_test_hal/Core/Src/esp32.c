#include "esp32.h"
/******ȫ�ֽ�����Ӧ������*******/
uint8_t rBuff[1000];
uint16_t rDataLen;
uint16_t count;


//��ʼ��
void ESP32_Init()
{
    //1.��ʼ��usart2����
    MX_USART2_UART_Init();

    //2.���������λESP32
    uint8_t* cmd = "AT+RST=0\r\n";
    ESP32_SendCmd(cmd);

    //3.������ʱ��ȷ�������ɹ�
    HAL_Delay(2000);
}

//��������
void ESP32_SendCmd(uint8_t* cmd)
{
    uint16_t len = strlen((char*)cmd);
    memset(rBuff, 0, rDataLen);  // ��ջ�����

    HAL_UART_Transmit(&huart2, cmd, len, 1000);


    uint32_t startTime = HAL_GetTick();
    const uint32_t timeout = 10000;  // ��ʱ 5 ��

    do
    {
        ESP32_ReadResp(rBuff + count, &rDataLen);
        count = rDataLen;
         if (HAL_GetTick() - startTime > timeout)  // ��ʱ����
         {
             printf("ESP32 ��Ӧ��ʱ��\n");
             printf("ESP32 ����: %.*s\n", rDataLen, rBuff);
             return;
         }
    } while (strstr((char*)rBuff, "OK") == NULL);
    count = 0;
    printf("ESP32 ����: %.*s\n", rDataLen, rBuff);  // ��ӡ���� ESP32 ����ֵ

}

//��ȡ��Ӧ
void ESP32_ReadResp(uint8_t rBuff[], uint16_t* rDataLen)
{
    HAL_UARTEx_ReceiveToIdle(&huart2, rBuff, 1000, rDataLen, 1000);
}

void ESP32_WIFI_STA()
{
    /*����WIFI�Ĺ���ģʽ:STA*/
    ESP32_SendCmd("AT+CWMODE=1\r\n");
    HAL_Delay(1000);
    ESP32_SendCmd("AT+CWDHCP=1,1\r\n");
    HAL_Delay(500);
    /*����WIFIҪ���ӵ�AP*/
    ESP32_SendCmd("AT+CWJAP=\"Redmi K70\",\"050215jy\"\r\n");
    HAL_Delay(5000);
    ESP32_SendCmd("AT+CIPSTA?\r\n");
    ESP32_SendCmd("AT+CIPMUX=0\r\n");    // ����Ϊ������ģʽ
    HAL_Delay(500);




}

void ESP32_WIFI_AP()
{
    /*����ΪAPģʽ*/
    ESP32_SendCmd("AT+CWMODE=2\r\n");
    printf("����ΪAPģʽ\n");
    /*����AP������SSID password �źź� ���ܷ�ʽ*/
    ESP32_SendCmd("AT+CWSAP=\"404Ů�ʹ�����\",\"1234567890\",5,3\r\n");
    printf("AP�����������\n");

    /*����AP�ľ�̬IP��ַ*/
    ESP32_SendCmd("AT+CIPAP=\"192.168.5.1\"\r\n");
    printf("AP��̬IPΪ��192.168.5.1");
}

void ESP_TCP_StartTcpServer()
{
    /*����tcpΪ������ģʽ*/
    ESP32_SendCmd("AT+CIPMUX=1\r\n");
    printf("����Ϊ������ģʽ\n");

    /*���ý���������ʾ��ʽ - ��ʾIP��Ϣ*/
    ESP32_SendCmd("AT+CIPDINFO=1\r\n");
    printf("���ý���������ʾ��ʽ\n");

    /*����TCP������*/
    ESP32_SendCmd("AT+CIPSERVER=1,8080\r\n");
    printf("����TCP������\n");

}

void ESP_TCP_RecvTcpData(uint8_t RxBuff[], uint16_t* rMsglen, uint8_t* id, uint8_t* ip, uint16_t* port)
{
    //printf("��������\n");
    //HAL_UART_Transmit(&huart1, "��������?", 13, 1000);
    /*TCP�������ݵĽ��ջ�����*/
    uint8_t tcpBuff[1000] = { 0 };
    uint16_t tcpLen = 0;
    //printf("1!5!\n");
    HAL_UARTEx_ReceiveToIdle(&huart2, tcpBuff, 1000, &tcpLen, 3000);
    //printf("���յ�����\n");
    /*�ҵ�+IPD*/
    if (strstr((char*)tcpBuff, "+IPD") != NULL)
    {
        /*ʹ��sscanf���й���ɸѡ����*/
        //+IPD,<link_id>,<length>,<"remote_ip">,<remote_port>:<data>
        sscanf((char*)tcpBuff, "%*[\r\n]+IPD,%d,%d,\"%[^\"]\",%d", id, rMsglen, ip, port);
        char* pData = strstr((char*)tcpBuff, ":") + 1;
        memcpy(RxBuff, pData, *rMsglen);

    }
}

void ESP_TCP_SendTcpData(uint8_t id, uint8_t* msg, uint16_t len)
{
    char sendCmd[100] = { 0 };
    uint8_t recvBuff[10];
    uint16_t recvLen;
    sprintf(sendCmd, "AT+CIPSEND=%d,%d\r\n", id, len);
    ESP32_SendCmd((uint8_t*)sendCmd);
    printf("׼������\n");
    /*��������*/
    HAL_UART_Transmit(&huart2, msg, len, 1000);
    memset(recvBuff, 0, 10);
    /*�ȴ�����SEND OK*/
    while (strstr((char*)recvBuff, "SEND OK") == NULL)
        HAL_UARTEx_ReceiveToIdle(&huart2, recvBuff, 10, &recvLen, 1000);
    printf("���ͳɹ���\n");
}

void ESP_TCP_SendTcpDataSingle(uint8_t* msg, uint16_t len)
{
    char sendCmd[100] = { 0 };
    uint8_t recvBuff[10];
    uint16_t recvLen;
    sprintf(sendCmd, "AT+CIPSEND=%d\r\n", len);
    ESP32_SendCmd((uint8_t*)sendCmd);
    printf("\n׼������\n");
    /*��������*/
    HAL_UART_Transmit(&huart2, msg, len, 1000);
    memset(recvBuff, 0, 10);
    /*�ȴ�����SEND OK*/
    while (strstr((char*)recvBuff, "SEND OK") == NULL)
        HAL_UARTEx_ReceiveToIdle(&huart2, recvBuff, 10, &recvLen, 1000);
    printf("\n���ͳɹ���\n");
}
