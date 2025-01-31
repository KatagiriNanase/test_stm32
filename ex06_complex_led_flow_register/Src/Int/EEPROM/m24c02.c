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
    Dri_I2C_SendAddr(W_ADDR);

    //3.发送写入地址
    Dri_I2C_SendByte(addr);

    //4.发送data
    Dri_I2C_SendByte(byte);

    //5.发出停止信号
    Dri_I2C_Stop();


    //延时等待写入周期结束
    Com_Delay_ms(5);
}

//读取EEPROM一个字节
uint8_t Int_M24C02_ReadByte(uint8_t addr)
{
    uint8_t byte = 0;
    //1.start信号
    Dri_I2C_Start();

    //2.假写入
    Dri_I2C_SendAddr(W_ADDR);
    Dri_I2C_SendByte(addr);

    //3.真读
    Dri_I2C_Start();

    Dri_I2C_SendAddr(R_ADDR);

    //设置非应答
    Dri_I2C_Nack();

    //设置在接收下一个字节后发出停止信号
    Dri_I2C_Stop();

    //读取
    byte = Dri_I2C_ReadByte();

    return byte;
}

//连续写入多个字节（页写）
void Int_M24C02_WriteBytes(uint8_t addr, uint8_t* bytes, uint8_t size)
{
    //1.Start信号
    Dri_I2C_Start();

    //2.发送写地址（设备地址+写方向）
    Dri_I2C_SendAddr(W_ADDR);

    //4.发送写入地址
    Dri_I2C_SendByte(addr);

    //6.连续发送字节
    for (uint8_t i = 0;i < size;++i)
        Dri_I2C_SendByte(bytes[i]);

    //7.发出停止信号
    Dri_I2C_Stop();

    //延时等待写入周期结束
    Com_Delay_ms(5);
}

//连续读取多个字节
void Int_M24C02_ReadBytes(uint8_t addr, uint8_t* buffer, uint8_t size)
{
    //1.start信号
    Dri_I2C_Start();

    //2.假写入
    Dri_I2C_SendAddr(W_ADDR);
    Dri_I2C_SendByte(addr);

    //3.真读
    Dri_I2C_Start();

    Dri_I2C_SendAddr(R_ADDR);
    //4.连续读取
    for (uint8_t i = 0;i < size;++i)
    {
        //设置应答信号和非应答
        if (i < size - 1)
            Dri_I2C_Ack();
        else
        {
            Dri_I2C_Nack();
            //5.停止信号
            Dri_I2C_Stop();
        }
        buffer[i] = Dri_I2C_ReadByte();
    }

}