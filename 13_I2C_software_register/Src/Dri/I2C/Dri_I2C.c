#include "Dri_I2C.h"

//初始化
void Dri_I2C_Init()
{
    //1.配置时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    //2.配置GPIO工作模式 通用开漏输出模式 PB10 PB11
    GPIOB->CRH |= GPIO_CRH_MODE10;
    GPIOB->CRH |= GPIO_CRH_CNF10_0;
    GPIOB->CRH &= ~GPIO_CRH_CNF10_1;

    GPIOB->CRH |= GPIO_CRH_MODE11;
    GPIOB->CRH |= GPIO_CRH_CNF11_0;
    GPIOB->CRH &= ~GPIO_CRH_CNF11_1;
}

//发出起始信号
void Dri_I2C_Start()
{
    //1.SDA,SCL拉高
    SCL_HIGH;
    SDA_HIGH;
    I2C_DELAY;

    //2.拉低SDA
    SDA_LOW;
    I2C_DELAY;
}

//发出停止信号
void Dri_I2C_Stop()
{
    //1.SCL拉高，SDA拉低
    SCL_HIGH;
    SDA_LOW;
    I2C_DELAY;

    //2.SCL高电平状态下拉高SDA
    SDA_HIGH;
    I2C_DELAY;
}

//主机发出 应答信号
void Dri_I2C_Ack()
{
    //1.SCL拉低，SDA拉高，准备发出应答信号
    SCL_LOW;
    SDA_HIGH;
    I2C_DELAY;
    //2.SDA拉低
    SDA_LOW;
    I2C_DELAY;

    //3.SCL拉高进行采样
    SCL_HIGH;
    I2C_DELAY;

    //4.释放SDA，结束采样
    SCL_LOW;
    SDA_HIGH;
    I2C_DELAY;
}

//主机发出非应答信号
void Dri_I2C_Nack()
{
    //1.SCL拉低，SDA拉高，准备发出应答信号
    SCL_LOW;
    SDA_HIGH;
    I2C_DELAY;

    //2.SCL拉高进行采样
    SCL_HIGH;
    I2C_DELAY;

    //3.结束采样
    SCL_LOW;
    I2C_DELAY;
}

//主机等待从设别发来应答信号
uint8_t Dri_I2C_Wait4Ack()
{
    //1.拉低SCL，释放SDA，让从机准备应答
    SCL_LOW;
    SDA_HIGH;
    I2C_DELAY;

    //2.拉高SCL进行采样
    SCL_HIGH;
    I2C_DELAY;
    uint16_t ack = READ_SDA;

    //3.拉低SCL，结束采样
    SCL_LOW;
    I2C_DELAY;

    return ack ? NACK : ACK;
}

//主机发送一个字节的数据
void Dri_I2C_SendByte(uint8_t byte)
{
    for (uint8_t i = 0;i < 8;++i)
    {
        //1.准备发送数据
        SCL_LOW;
        SDA_LOW;
        I2C_DELAY;
        //2.发送最高位
        if (byte & 0x80)
            SDA_HIGH;
        else
            SDA_LOW;
        I2C_DELAY;

        //3.采样
        SCL_HIGH;
        I2C_DELAY;

        //4.结束采样
        SCL_LOW;
        I2C_DELAY;

        //5.左移
        byte <<= 1;
    }
}

//主机接收一个字节的数据
uint8_t Dri_I2C_ReadByte()
{
    uint8_t byte = 0;

    for (uint8_t i = 0;i < 8;++i)
    {
        //准备接受数据
        SCL_LOW;
        I2C_DELAY;

        //接收1bit数据
        SCL_HIGH;
        I2C_DELAY;
        byte <<= 1;
        if (READ_SDA)
            byte |= 0x01;//先存入最低位，左移后才能是最高位
        // else
        //     byte |= 0x00;

        //拉低SCL
        SCL_LOW;
        I2C_DELAY;

    }
    return byte;
}
