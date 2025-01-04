#include <stm32f10x.h>

void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void Delay_s(uint16_t s);

int main()
{
	//配置时钟
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;


	//配置工作模式
	GPIOA->CRL &= ~(GPIO_CRL_CNF0);
	GPIOA->CRL |= (GPIO_CRL_MODE0);

	GPIOA->CRL &= ~(GPIO_CRL_CNF1);
	GPIOA->CRL |= (GPIO_CRL_MODE1);

	GPIOA->CRH &= ~(GPIO_CRH_CNF8);
	GPIOA->CRH |= (GPIO_CRH_MODE8);

	//PA0,PA1,PA8输出高电平，关灯
	GPIOA->ODR |= (GPIO_ODR_ODR0);
	GPIOA->ODR |= (GPIO_ODR_ODR1);
	GPIOA->ODR |= (GPIO_ODR_ODR8);


	//依次打开
	while (1)
	{
		GPIOA->ODR &= ~GPIO_ODR_ODR0; //开灯
		Delay_ms(500);	//延时500ms
		GPIOA->ODR |= GPIO_ODR_ODR0;	//关灯

		GPIOA->ODR &= ~GPIO_ODR_ODR1; //开灯
		Delay_ms(500);	//延时500ms
		GPIOA->ODR |= GPIO_ODR_ODR1;	//关灯

		GPIOA->ODR &= ~GPIO_ODR_ODR8; //开灯
		Delay_ms(500);	//延时500ms
		GPIOA->ODR |= GPIO_ODR_ODR8;	//关灯
	}

}

//延时函数，微妙为单位，利用系统嘀嗒定时器，72MHz,一次嘀嗒 1/72us
void Delay_us(uint16_t us)
{
	//1.装载计数值，72*us
	SysTick->LOAD = 72 * us;

	//2.配置，使用系统时钟(1)，计数结果不产生中断（0），使能开关（1）
	SysTick->CTRL |= 0x05;

	//3.等待计数器变为0，判断ctrl里的标志位countflag是否不为零
	while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0)
	{
		//如果变为1，就说明到时间了
	}

	//4.关闭定时器
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
