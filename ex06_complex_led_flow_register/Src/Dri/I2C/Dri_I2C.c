#include "Dri_I2C.h"

//初始化
void Dri_I2C_Init()
{
    //1.配置时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    //2.配置GPIO工作模式 复用开漏输出模式 PB10 PB11
    GPIOB->CRH |= GPIO_CRH_MODE10;
    GPIOB->CRH |= GPIO_CRH_CNF10_0;
    GPIOB->CRH |= GPIO_CRH_CNF10_1;

    GPIOB->CRH |= GPIO_CRH_MODE11;
    GPIOB->CRH |= GPIO_CRH_CNF11_0;
    GPIOB->CRH |= GPIO_CRH_CNF11_1;

    //3.配置I2C模块
    //3.1硬件工作模式
    I2C2->CR1 &= ~I2C_CR1_SMBUS;
    I2C2->CCR &= ~I2C_CCR_FS;

    //3.2配置时钟频率
    I2C2->CR2 |= 36;

    //3.3配置CCR,100kb/s，SCL高电平时间为5us，所以需要系数36*5
    I2C2->CCR |= 180;

    //3.4配置TRISE SCL上升沿最大时钟周期数+1
    I2C2->TRISE |= 37;

    //3.5开启使能
    I2C2->CR1 |= I2C_CR1_PE;

}

//发出起始信号
uint8_t Dri_I2C_Start()
{
    //产生起始信号
    I2C2->CR1 |= I2C_CR1_START;

    //引入超时时间
    uint16_t timeout = 0xFFFF;

    //等待起始信号发出
    while ((I2C2->SR1 & I2C_SR1_SB) == 0 && timeout)
        timeout--;

    return timeout ? OK : FAIL;

}

//设置接收完成之后发出停止信号
void Dri_I2C_Stop()
{
    I2C2->CR1 |= I2C_CR1_STOP;
}

void Dri_I2C_Ack()
{
    I2C2->CR1 |= I2C_CR1_ACK;
}

//主机发出非应答信号
void Dri_I2C_Nack()
{
    I2C2->CR1 &= ~I2C_CR1_ACK;
}

uint8_t Dri_I2C_SendByte(uint8_t byte)
{
    uint16_t timeout = 0xFFFF;
    //1.等待当前DR为空(上一个字节的数据已经发送完毕)
    while ((I2C2->SR1 & I2C_SR1_TXE) == 0 && timeout)
        timeout--;

    //2.发送数据
    I2C2->DR = byte;

    //3.等待应答
    timeout = 0xFFFF;
    while ((I2C2->SR1 & I2C_SR1_BTF) == 0 && timeout)
        timeout--;

    return timeout ? OK : FAIL;
}

uint8_t Dri_I2C_SendAddr(uint8_t addr)
{
    //发送地址
    I2C2->DR = addr;

    uint16_t timeout = 0xFFFF;

    //等待应答
    while ((I2C2->SR1 & I2C_SR1_ADDR) == 0 && timeout)
        timeout--;
    //清除ADDR
    if (timeout > 0)
        I2C2->SR2;

    return timeout ? OK : FAIL;
}

uint8_t Dri_I2C_ReadByte()
{
    uint16_t timeout = 0xFFFF;
    //1.等待当前DR为满
    while ((I2C2->SR1 & I2C_SR1_RXNE) == 0 && timeout)
        timeout--;

    //2.返回字节
    return timeout ? I2C2->DR : FAIL;
}



