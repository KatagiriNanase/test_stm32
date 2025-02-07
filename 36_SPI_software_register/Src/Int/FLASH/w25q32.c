#include "w25q32.h"

//初始化
void Int_W25q32_Init()
{
    Dri_SPI_Init();
}

//读取ID
void Int_W25q32_ReadID(uint8_t* mid, uint16_t* did)
{
    Dri_SPI_Start();

    //1.发送指令 9fh
    Dri_SPI_SwapByte(0x9f);

    //2.获取制造商id(mid) 为了读取数据，发送什么不重要，为了不改变里面的数据，可以写为0xff
    *mid = Dri_SPI_SwapByte(0xff);

    //3.获取设备id
    *did = 0;
    *did |= Dri_SPI_SwapByte(0xff) << 8;
    *did |= Dri_SPI_SwapByte(0xff) & 0xff;

    Dri_SPI_Stop();


}

//开启写使能
void Int_W25q32_WriteEnable()
{
    Dri_SPI_Start();

    //发送指令 06h
    Dri_SPI_SwapByte(0x06);

    Dri_SPI_Stop();
}

//关闭写使能
void Int_W25q32_WriteDisable()
{
    Dri_SPI_Start();

    //发送指令 04h
    Dri_SPI_SwapByte(0x04);

    Dri_SPI_Stop();
}

//等待状态不为忙
void Int_W25q32_WaitNotBusy()
{
    Dri_SPI_Start();
    Dri_SPI_SwapByte(0x05);

    //等待收到数据的末位变成0
    while (Dri_SPI_SwapByte(0xff) & 0x01)
    {
        //
    }
    Dri_SPI_Stop();

}

//擦除段区
void Int_W25q32_EraseSector(uint8_t block, uint8_t sector)
{
    //等待状态不为忙
    Int_W25q32_WaitNotBusy();

    //开启写使能
    Int_W25q32_WriteEnable();
    //计算要发送的段首地址
    uint32_t addr = ((uint32_t)block << 16) + ((uint32_t)sector << 12);

    Dri_SPI_Start();

    //发送指令 20h
    Dri_SPI_SwapByte(0x20);

    //发送页写地址
    Dri_SPI_SwapByte(addr >> 16 & 0xff);
    Dri_SPI_SwapByte(addr >> 8 & 0xff);
    Dri_SPI_SwapByte(addr >> 0 & 0xff);

    Dri_SPI_Stop();
    //关闭写使能
    Int_W25q32_WriteDisable();


}

//写入（页写）
void Int_W25q32_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t* data, uint16_t len)
{

    //等待状态不为忙
    Int_W25q32_WaitNotBusy();

    //开启写使能
    Int_W25q32_WriteEnable();
    //计算要发送的页首地址
    uint32_t addr = ((uint32_t)block << 16) + ((uint32_t)sector << 12) + ((uint32_t)page << 8);

    Dri_SPI_Start();

    //发送指令 20h
    Dri_SPI_SwapByte(0x02);

    //发送页写地址
    Dri_SPI_SwapByte(addr >> 16 & 0xff);
    Dri_SPI_SwapByte(addr >> 8 & 0xff);
    Dri_SPI_SwapByte(addr >> 0 & 0xff);

    //发送数据
    for (uint16_t i = 0;i < len;++i)
        Dri_SPI_SwapByte(data[i]);

    Dri_SPI_Stop();

    Int_W25q32_WriteDisable();
}

//读取
void Int_W25q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t len)
{
    //等待状态不为忙
    Int_W25q32_WaitNotBusy();

    //计算要读取的地址
    uint32_t addr = ((uint32_t)block << 16) + ((uint32_t)sector << 12) + ((uint32_t)page << 8) + innerAddr;

    Dri_SPI_Start();

    //发送指令 03h
    Dri_SPI_SwapByte(0x03);

    //发送页写地址
    Dri_SPI_SwapByte(addr >> 16 & 0xff);
    Dri_SPI_SwapByte(addr >> 8 & 0xff);
    Dri_SPI_SwapByte(addr >> 0 & 0xff);

    //发送数据
    for (uint16_t i = 0;i < len;++i)
        data[i] = Dri_SPI_SwapByte(0xff);

    Dri_SPI_Stop();

}