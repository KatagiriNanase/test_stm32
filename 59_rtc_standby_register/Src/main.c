#include "Int_LED.h"
#include "Com_Util.h"
#include "Dri_USART.h"
#include "rtc.h"
void enter_standbymode();
uint8_t flag = 0;


int main()
{
    Dri_USART_Init();
    Int_LED_Init();
    Dri_RTC_Init();
    Drt_RTC_SetALR(5);
    Int_LED_On(LED2);
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    printf("%d\n", flag);
    //�жϱ�־λ��������ѱ�־λΪ1������Ҫ���
    if (PWR->CSR & PWR_CSR_WUF)
    {
        printf("�����˻����¼���\n");
        PWR->CR |= PWR_CR_CWUF;
    }

    // �жϱ�־λ�����������־λΪ1������Ҫ���
    if (PWR->CSR & PWR_CSR_SBF)
    {
        printf("�Ӵ���ģʽ���ѣ�\n");
        PWR->CR |= PWR_CR_CSBF;
    }
    //RTC->CRL &= ~RTC_CRL_ALRF;
    //printf("3���������ģʽ\n");
    Com_Delay_ms(3000);
    //printf("�������ģʽ\n");
    Com_Delay_ms(1);
    enter_standbymode();
    while (1)
    {
        //printf("3��������ͨ˯��ģʽ\n");
        // Com_Delay_ms(3000);
        // //printf("����ͣ��ģʽ\n");
        // Com_Delay_ms(1);
        // printf("%d\n", RTC->CNTL);
        // Com_Delay_ms(500);
    }
}

void enter_standbymode()
{
    // 1. ������˯��ģʽ
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    // 3. ����PDDS = 1������ģʽ
    PWR->CR |= PWR_CR_PDDS;

    PWR->CR |= PWR_CR_CWUF;
    // 5. �������ģʽ���ȴ�����
    __WFI();
}

