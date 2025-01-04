#include <stm32f10x.h>

void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void Delay_s(uint16_t s);

int main()
{
	//����ʱ��
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;


	//���ù���ģʽ
	GPIOA->CRL &= ~(GPIO_CRL_CNF0);
	GPIOA->CRL |= (GPIO_CRL_MODE0);

	GPIOA->CRL &= ~(GPIO_CRL_CNF1);
	GPIOA->CRL |= (GPIO_CRL_MODE1);

	GPIOA->CRH &= ~(GPIO_CRH_CNF8);
	GPIOA->CRH |= (GPIO_CRH_MODE8);

	//PA0,PA1,PA8����ߵ�ƽ���ص�
	GPIOA->ODR |= (GPIO_ODR_ODR0);
	GPIOA->ODR |= (GPIO_ODR_ODR1);
	GPIOA->ODR |= (GPIO_ODR_ODR8);


	//���δ�
	while (1)
	{
		GPIOA->ODR &= ~GPIO_ODR_ODR0; //����
		Delay_ms(500);	//��ʱ500ms
		GPIOA->ODR |= GPIO_ODR_ODR0;	//�ص�

		GPIOA->ODR &= ~GPIO_ODR_ODR1; //����
		Delay_ms(500);	//��ʱ500ms
		GPIOA->ODR |= GPIO_ODR_ODR1;	//�ص�

		GPIOA->ODR &= ~GPIO_ODR_ODR8; //����
		Delay_ms(500);	//��ʱ500ms
		GPIOA->ODR |= GPIO_ODR_ODR8;	//�ص�
	}

}

//��ʱ������΢��Ϊ��λ������ϵͳ��શ�ʱ����72MHz,һ����� 1/72us
void Delay_us(uint16_t us)
{
	//1.װ�ؼ���ֵ��72*us
	SysTick->LOAD = 72 * us;

	//2.���ã�ʹ��ϵͳʱ��(1)����������������жϣ�0����ʹ�ܿ��أ�1��
	SysTick->CTRL |= 0x05;

	//3.�ȴ���������Ϊ0���ж�ctrl��ı�־λcountflag�Ƿ�Ϊ��
	while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0)
	{
		//�����Ϊ1����˵����ʱ����
	}

	//4.�رն�ʱ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}

void Delay_ms(uint16_t ms)
{
	while (ms--)
		Delay_us(1000);
}

void Delay_s(uint16_t s)
{
	while (s--)
		Delay_ms(1000);
}
