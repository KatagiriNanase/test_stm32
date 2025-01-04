#include <stm32f10x.h>
int main()
{
	//1.时钟配置
		//*(uint32_t*)(0x40021000+0x18)=4;
	//RCC->APB2ENR=4;
	
	//RCC->APB2ENR|=(1<<2);
	RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;
	
	//2.GPIO引脚配置
	//*(uint32_t*)(0x40010800+0x00)=0x33;
	//*(uint32_t*)(0x40010800+0x04)=0x03;
	//第一次优化
	//GPIOA->CRL=0x33;
	//GPIOA->CRH=0x03; 
	
	//第二次优化
	//GPIOA->CRL &=~((1<<3) | (1<<2));
	//GPIOA->CRL &=~(1<<2);
	//GPIOA->CRL |=(1<<1) | (1<<0);
	//GPIOA->CRL |=(1<<0);
	
	//第三次优化
	GPIOA->CRL &=~(GPIO_CRL_CNF0);
	GPIOA->CRL |=(GPIO_CRL_MODE0);
	
	GPIOA->CRL &=~(GPIO_CRL_CNF1);
	GPIOA->CRL |=(GPIO_CRL_MODE1);
	
	GPIOA->CRH &=~(GPIO_CRH_CNF8);
	GPIOA->CRH |=(GPIO_CRH_MODE8);
	
	//3.PA0,PA1,PA8输出低电平
	//*(uint32_t*)(0x40010800+0x0C)=0xFEFC;
	//GPIOA->ODR=0xfefc;
	
	//第二次优化
	//GPIOA->ODR &=~(1<<0);
	
	//第三次优化
	GPIOA->ODR &=~(GPIO_ODR_ODR0);
	GPIOA->ODR &=~(GPIO_ODR_ODR1);
	GPIOA->ODR &=~(GPIO_ODR_ODR8);
	
	
	//4.死循环
	while(1);
	
}
