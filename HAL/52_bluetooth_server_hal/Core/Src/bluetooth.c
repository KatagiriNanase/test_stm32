#include "bluetooth.h"

//初始化BLE为服务端
void Bluetooth_Init(void)
{
    ESP32_SendCmd("AT+RST\r\n");
    HAL_Delay(2000);
    /*初始化BLE为sever*/
    ESP32_SendCmd("AT+BLEINIT=2\r\n");
    printf("\n初始化BLE为sever\n");

    /*创建服务*/
    ESP32_SendCmd("AT+BLEGATTSSRVCRE\r\n");
    printf("\n创建服务\n");

    /*开启服务*/
    ESP32_SendCmd("AT+BLEGATTSSRVSTART\r\n");
    printf("\n开启服务\n");

    /*设置设备名字*/
    printf("\n设置设备名字\n");
    ESP32_SendCmd("AT+BLENAME=\"GATTJi\"\r\n");
    HAL_Delay(5000);

    /*设置设备地址：公共地址*/
    // ESP32_SendCmd("AT+BLEADDR=0\r\n");
    // printf("\n设备地址为公共地址\n");
    /*设置广播参数*/
    ESP32_SendCmd("AT+BLEADVPARAM=50,50,0,0,7,0,,\r\n");
    printf("\n设置广播参数\n");

    /*设置广播数据*/
    ESP32_SendCmd("AT+BLEADVDATAEX=\"GATTJi\",\"A002\",\"0102030405\",1\r\n");
    printf("\n设置广播数据\n");
    
    ESP32_SendCmd("AT+BLEGATTSSRV?\r\n");
    //创建自定义串口服务
    BLE_SetupSPPService();

    /*设置连接状态改变提示信息*/
    ESP32_SendCmd("AT+SYSMSG=4\r\n");

    /*开始广播*/
    ESP32_SendCmd("AT+BLEADVSTART\r\n");
    printf("\n开始广播\n");

}


void BLE_SetupSPPService(void)
{
    /*设置虚拟串口参数*/
    ESP32_SendCmd("AT+BLESPPCFG=1,1,7,1,5\r\n");
    printf("\n设置SSP参数\n");
}

uint8_t Bluetooth_ReadData(uint8_t* rxBuff, uint16_t* rxLen)
{
    HAL_UARTEx_ReceiveToIdle(&huart2, rxBuff, 1000, rxLen, 1000);

    if (*rxLen == 0)
        return 1;

    /*处理连接变化*/
    if (Bluetooth_HandleConnChange())
    {
        return 2;
    }


    return 0;
}

/*引入全局缓冲区*/
extern uint8_t rBuff[1000];
extern uint16_t rDataLen;
uint8_t Bluetooth_HandleConnChange(void)
{
    /*WIFI连接状态变化，不做任何处理*/
    if ((strstr((char*)rBuff, "+STA_CONNECTED") != NULL)
        || (strstr((char*)rBuff, "+STA_DISCONNECTED:") != NULL)
        || (strstr((char*)rBuff, "+DIST_STA_IP:") != NULL))
    {
        printf("\nWIFI 连接状态发生变化\n");
        return 1;
    }

    if (strstr((char*)rBuff, "+BLECONN:") != NULL)
    {
        printf("\n连接至客户端\n");
        ESP32_SendCmd("AT+BLESPP\r\n");
        printf("\n进入SSP模式\n");
        /*吞掉一个>*/
        uint8_t tmp;
        HAL_UART_Receive(&huart2, &tmp, 1, 1000);
        return 1;
    }

    if (strstr((char*)rBuff, "+BLEDISCONN:") != NULL)
    {
        printf("\n客户端断开连接\n");
        HAL_UART_Transmit(&huart2, "+++", 3, 1000);
        /*至少间隔一秒*/
        HAL_Delay(2000);
        printf("\n退出SSP模式\n");
        return 1;
    }

    return 0;
}

void Bluetooth_SendData(uint8_t txBuff[], uint16_t txLen)
{
    HAL_UART_Transmit(&huart2, txBuff, txLen, 10000);
}
