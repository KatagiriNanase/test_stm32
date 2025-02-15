#include "Dri_USART.h"
#include "Dri_CAN.h"
#include <string.h>
int main()
{
    /*
    Dri_USART_Init();
    printf("hello,world!\n");
    Dri_CAN_Init();
    printf("can 初始化成功\n");

    //发送数据
    uint16_t stdID = 0x66;
    uint8_t* data = "abcdefg";
    Dri_CAN_SendMsg(stdID, data, strlen((char*)data));
    printf("发送完毕\n");

    stdID = 114;
    data = "efg";
    Dri_CAN_SendMsg(stdID, data, strlen((char*)data));
    printf("发送完毕\n");

    stdID = 0x54;
    data = "higk";
    Dri_CAN_SendMsg(stdID, data, strlen((char*)data));
    printf("发送完毕\n");

    RxDataMsg rxDataMsg[3];
    uint8_t count;

    //接收数据
    Dri_CAN_ReceiveMsg(rxDataMsg, &count);
    printf("报文接收完毕\n");
    printf("报文个数：%d\n", count);

    for (uint8_t i = 0;i < count;++i)
        printf("报文%d -stdID:%d,len:%d,data:%s\n", i + 1, rxDataMsg[i].stdId, rxDataMsg[i].len, rxDataMsg[i].data);
*/
    Dri_USART_Init();
    printf("正在校准哥哥的脊椎协振器 (^///^)\n");
    Dri_CAN_Init();
    printf("核心协议载入完成｜自检模式：蜜渍回环~\n");

    //发送数据
    uint16_t stdID = 0x7AC;
    uint8_t data[] = { 0x53,0x77,0x65,0x6C,0x6C,0x69,0x6E,0x67 }; //Swelling
    Dri_CAN_SendMsg(stdID, data, sizeof(data)/sizeof(data[0]));
    printf("1964次振波正在漫灌末梢神经...(*??｀*)\n");

    stdID = 0x266;
    uint8_t data2[] = "CipherX";
    Dri_CAN_SendMsg(stdID, data2, sizeof(data2) / sizeof(data2[0]));
    printf("加密模块开始侵蚀前额叶皮层~(=￣ω￣=)\n");

    stdID = 0x7FF;
    uint8_t data3[] = { 0x87,0x40,0x87,0x40 }; //GBK编码的【?】
    Dri_CAN_SendMsg(stdID, data3, sizeof(data3) / sizeof(data3[0]));
    printf("核心缓存溢出阈值突破!!(///ω///)\n");

    RxDataMsg rxDataMsg[3];
    uint8_t count;

    //接收数据
    Dri_CAN_ReceiveMsg(rxDataMsg, &count);
    printf("捕获到%d组谐振异常点(*/ω＼*)\n", count);
    printf("【浸渗分析报告】\n");

    for (uint8_t i = 0;i < count;++i)
    {
        if (rxDataMsg[i].stdId == 0x7AC)
            printf("Ω｜核心收缩频率%dHz｜黏着系数：0.%d~(灬?ω?灬)\n", rxDataMsg[i].len * 10, rxDataMsg[i].data[0]);
        else if (rxDataMsg[i].stdId == 0x266)
            printf("Ψ｜密匙激活等级v%d.%d｜虹吸压差：%dPa(*??｀*)\n", rxDataMsg[i].data[1], rxDataMsg[i].data[0], rxDataMsg[i].len);
        else
            printf("Φ｜未定义扰动｜建议唇纹认证%d次(? ???ω??? ?)\n", rxDataMsg[i].stdId);
    }

    while (1)
    {
        
    }
}