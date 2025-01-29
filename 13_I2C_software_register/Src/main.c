#include "Dri_USART.h"
#include "m24c02.h"

int main()
{
    Dri_USART_Init();
    Int_M24C02_Init();

    printf("I2C协议觉醒测试 启动!\n");
    Com_Delay_ms(200);
    //printf("へぇ～I²C这种小事也太简单了わよ！你这クソッタレ的破烂代码，就让我看看能不能动起来んだからねっ！(｀Д´)ﾉ⌒☆\n");

    //1.向EEPROM写入单个字节
    Int_M24C02_WriteByte(0x00, 'a');
    Int_M24C02_WriteByte(0x01, 'b');
    Int_M24C02_WriteByte(0x02, 'c');

    //2.读取字符
    uint8_t byte1 = Int_M24C02_ReadByte(0x00);
    uint8_t byte2 = Int_M24C02_ReadByte(0x01);
    uint8_t byte3 = Int_M24C02_ReadByte(0x02);

    //3.串口输出打印
    printf("byte1=%c\t byte2=%c\t byte3=%c\n", byte1, byte2, byte3);

    //4.写入字符串
    Int_M24C02_WriteBytes(0x00, "123456", 6);

    //5.读取多个字节
    uint8_t buffer[100] = { 0 };
    Int_M24C02_ReadBytes(0x00, buffer, 6);
    printf("buffer=%s\n", buffer);
    while (1)
    {

    }
}