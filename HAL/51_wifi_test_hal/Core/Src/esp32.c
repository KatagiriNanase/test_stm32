#include "esp32.h"
/******全局接收响应缓冲区*******/
uint8_t rBuff[1000];
uint16_t rDataLen;
uint16_t count;


//初始化
void ESP32_Init()
{
    //1.初始化usart2串口
    MX_USART2_UART_Init();

    //2.发送命令，复位ESP32
    uint8_t* cmd = "AT+RST=0\r\n";
    ESP32_SendCmd(cmd);

    //3.引入延时，确保重启成功
    HAL_Delay(2000);
}

//发送命令
void ESP32_SendCmd(uint8_t* cmd)
{
    uint16_t len = strlen((char*)cmd);
    memset(rBuff, 0, rDataLen);  // 清空缓冲区

    HAL_UART_Transmit(&huart2, cmd, len, 1000);


    uint32_t startTime = HAL_GetTick();
    const uint32_t timeout = 10000;  // 超时 5 秒

    do
    {
        ESP32_ReadResp(rBuff + count, &rDataLen);
        count = rDataLen;
         if (HAL_GetTick() - startTime > timeout)  // 超时处理
         {
             printf("ESP32 响应超时！\n");
             printf("ESP32 返回: %.*s\n", rDataLen, rBuff);
             return;
         }
    } while (strstr((char*)rBuff, "OK") == NULL);
    count = 0;
    printf("ESP32 返回: %.*s\n", rDataLen, rBuff);  // 打印完整 ESP32 返回值

}

//读取响应
void ESP32_ReadResp(uint8_t rBuff[], uint16_t* rDataLen)
{
    HAL_UARTEx_ReceiveToIdle(&huart2, rBuff, 1000, rDataLen, 1000);
}

void ESP32_WIFI_STA()
{
    /*设置WIFI的工作模式:STA*/
    ESP32_SendCmd("AT+CWMODE=1\r\n");
    HAL_Delay(1000);
    ESP32_SendCmd("AT+CWDHCP=1,1\r\n");
    HAL_Delay(500);
    /*设置WIFI要连接的AP*/
    ESP32_SendCmd("AT+CWJAP=\"Redmi K70\",\"050215jy\"\r\n");
    HAL_Delay(5000);
    ESP32_SendCmd("AT+CIPSTA?\r\n");
    ESP32_SendCmd("AT+CIPMUX=0\r\n");    // 设置为单连接模式
    HAL_Delay(500);




}

void ESP32_WIFI_AP()
{
    /*设置为AP模式*/
    ESP32_SendCmd("AT+CWMODE=2\r\n");
    printf("设置为AP模式\n");
    /*设置AP参数：SSID password 信号号 加密方式*/
    ESP32_SendCmd("AT+CWSAP=\"404女仆待机中\",\"1234567890\",5,3\r\n");
    printf("AP参数设置完成\n");

    /*设置AP的静态IP地址*/
    ESP32_SendCmd("AT+CIPAP=\"192.168.5.1\"\r\n");
    printf("AP静态IP为：192.168.5.1");
}

void ESP_TCP_StartTcpServer()
{
    /*设置tcp为多连接模式*/
    ESP32_SendCmd("AT+CIPMUX=1\r\n");
    printf("设置为多连接模式\n");

    /*设置接收数据显示格式 - 显示IP信息*/
    ESP32_SendCmd("AT+CIPDINFO=1\r\n");
    printf("设置接收数据显示格式\n");

    /*建立TCP服务器*/
    ESP32_SendCmd("AT+CIPSERVER=1,8080\r\n");
    printf("建立TCP服务器\n");

}

void ESP_TCP_RecvTcpData(uint8_t RxBuff[], uint16_t* rMsglen, uint8_t* id, uint8_t* ip, uint16_t* port)
{
    //printf("进来了吗\n");
    //HAL_UART_Transmit(&huart1, "进来了吗?", 13, 1000);
    /*TCP传输数据的接收缓冲区*/
    uint8_t tcpBuff[1000] = { 0 };
    uint16_t tcpLen = 0;
    //printf("1!5!\n");
    HAL_UARTEx_ReceiveToIdle(&huart2, tcpBuff, 1000, &tcpLen, 3000);
    //printf("接收到数据\n");
    /*找到+IPD*/
    if (strstr((char*)tcpBuff, "+IPD") != NULL)
    {
        /*使用sscanf进行过滤筛选数据*/
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
    printf("准备发送\n");
    /*发送数据*/
    HAL_UART_Transmit(&huart2, msg, len, 1000);
    memset(recvBuff, 0, 10);
    /*等待接收SEND OK*/
    while (strstr((char*)recvBuff, "SEND OK") == NULL)
        HAL_UARTEx_ReceiveToIdle(&huart2, recvBuff, 10, &recvLen, 1000);
    printf("发送成功！\n");
}

void ESP_TCP_SendTcpDataSingle(uint8_t* msg, uint16_t len)
{
    char sendCmd[100] = { 0 };
    uint8_t recvBuff[10];
    uint16_t recvLen;
    sprintf(sendCmd, "AT+CIPSEND=%d\r\n", len);
    ESP32_SendCmd((uint8_t*)sendCmd);
    printf("\n准备发送\n");
    /*发送数据*/
    HAL_UART_Transmit(&huart2, msg, len, 1000);
    memset(recvBuff, 0, 10);
    /*等待接收SEND OK*/
    while (strstr((char*)recvBuff, "SEND OK") == NULL)
        HAL_UARTEx_ReceiveToIdle(&huart2, recvBuff, 10, &recvLen, 1000);
    printf("\n发送成功！\n");
}
