#include "Key.h"
#include "Int_LED.h"
#include "Com_Util.h"
#include "Dri_USART.h"

void enter_standbymode();



int main()
{
    Dri_USART_Init();
    Int_LED_Init();
    Int_LED_On(LED2);
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    //�жϱ�־λ��������ѱ�־λΪ1������Ҫ���
    if (PWR->CSR & PWR_CSR_WUF)
    {
        printf("�����˻����¼���\n");
    }

    // �жϱ�־λ�����������־λΪ1������Ҫ���
    if (PWR->CSR & PWR_CSR_SBF)
    {
        printf("�Ӵ���ģʽ���ѣ�\n");
        PWR->CR |= PWR_CR_CSBF;
    }

    printf("3���������ģʽ\n");
    Com_Delay_ms(3000);
    printf("�������ģʽ\n");
    Com_Delay_ms(1);
    enter_standbymode();
    while (1)
    {
        printf("3��������ͨ˯��ģʽ\n");
        Com_Delay_ms(3000);
        printf("����ͣ��ģʽ\n");
        Com_Delay_ms(1);

    }
}

void enter_standbymode()
{
    // 1. ������˯��ģʽ
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    // 3. ����PDDS = 1������ģʽ
    PWR->CR |= PWR_CR_PDDS;

    // 4. ʹ��WKUP��������
    PWR->CSR |= PWR_CSR_EWUP;

    PWR->CR |= PWR_CR_CWUF;
    // 5. �������ģʽ���ȴ�����
    __WFI();
}

