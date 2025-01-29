#include "m24c02.h"
//初始化
void Int_M24C02_Init()
{
    Dri_I2C_Init();
}

//写入EEPROM一个字节
void Int_M24C02_WriteByte(uint8_t addr, uint8_t byte)
{
    //1.Start信号
    Dri_I2C_Start();

    //2.发送写地址（设备地址+写方向）
    Dri_I2C_SendByte(W_ADDR);

    //3.接收应答
    uint8_t ack = Dri_I2C_Wait4Ack();

    if (ack == ACK)
    {
        //4.发送写入地址
        Dri_I2C_SendByte(addr);

        //5.接收应答
        Dri_I2C_Wait4Ack();

        //6.发送data
        Dri_I2C_SendByte(byte);

        //7.接收应答
        Dri_I2C_Wait4Ack();

        //8.发出停止信号
        Dri_I2C_Stop();
    }

    //延时等待写入周期结束
    Com_Delay_ms(5);
}

//读取EEPROM一个字节
uint8_t Int_M24C02_ReadByte(uint8_t addr)
{
    uint8_t byte;
    //1.start信号
    Dri_I2C_Start();

    //2.假写入
    Dri_I2C_SendByte(W_ADDR);
    Dri_I2C_Wait4Ack();
    Dri_I2C_SendByte(addr);
    Dri_I2C_Wait4Ack();

    //3.真读
    Dri_I2C_Start();

    Dri_I2C_SendByte(R_ADDR);
    Dri_I2C_Wait4Ack();
    byte = Dri_I2C_ReadByte();
    //4.结束
    Dri_I2C_Nack();
    Dri_I2C_Stop();

    return byte;
}

//连续写入多个字节（页写）
void Int_M24C02_WriteBytes(uint8_t addr, uint8_t* bytes, uint8_t size)
{
    //1.Start信号
    Dri_I2C_Start();

    //2.发送写地址（设备地址+写方向）
    Dri_I2C_SendByte(W_ADDR);

    //3.接收应答
    uint8_t ack = Dri_I2C_Wait4Ack();

    if (ack == ACK)
    {
        //4.发送写入地址
        Dri_I2C_SendByte(addr);

        //5.接收应答
        Dri_I2C_Wait4Ack();

        //6.连续发送字节
        for (uint8_t i = 0;i < 8;++i)
        {
            Dri_I2C_SendByte(bytes[i]);
            Dri_I2C_Wait4Ack();
        }

        //7.发出停止信号
        Dri_I2C_Stop();
    }

    //延时等待写入周期结束
    Com_Delay_ms(5);
}

//连续读取多个字节
void Int_M24C02_ReadBytes(uint8_t addr, uint8_t* buffer, uint8_t size)
{
    //1.start信号
    Dri_I2C_Start();

    //2.假写入
    Dri_I2C_SendByte(W_ADDR);
    Dri_I2C_Wait4Ack();
    Dri_I2C_SendByte(addr);
    Dri_I2C_Wait4Ack();

    //3.真读
    Dri_I2C_Start();

    Dri_I2C_SendByte(R_ADDR);
    Dri_I2C_Wait4Ack();

    //4.连续读取
    for (uint8_t i = 0;i < 8;++i)
    {
        buffer[i] = Dri_I2C_ReadByte();
        if (i < size - 1)
            Dri_I2C_Ack();
        else
            Dri_I2C_Nack();
    }

    //5.停止信号
    Dri_I2C_Stop();
}