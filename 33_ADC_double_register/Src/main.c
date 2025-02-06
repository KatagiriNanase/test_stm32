#include "Dri_USART.h"
#include "ADC.h"
#include "Com_Util.h"

//�������飬����ת������ź�ֵ
uint16_t data[2] = { 0 };
//����������飬���ڴ洢��������ROM������
int main()
{
    Dri_USART_Init();
    Dri_ADC1_Init();
    Dri_ADC1_DMA_Init();
    //��ӡ������ַ�ͳ�����ַ
    printf("===== ?^?��?^? ADC��ѹ��׽ʵ������ =====\n"
        "| �̼��汾: V1.0 ��צ�ȶ���\n"
        "| ��ǰ��������: 7.5*12M Hz\n"
        "| Ŀ��ͨ��: ADC_IN10,ADC_IN12 (��Ӧ���ǵ�ѹ�ӿ�)\n"
        "| �ο���ѹ: 3.3V (���������ͷһ����׼)\n"
        "======================================\n");
    //����ADC
    Dri_ADC1_DMA_StartConvert((uint32_t)data, 2);
    while (1)
    {
        //�򴮿ڴ�ӡģ���ѹ
        printf("������ = %.2f,V_PC2= %.2f\n", data[0] * 3.3 / 4095, data[1] * 3.3 / 4095);
        Com_Delay_ms(1000);
    }
}