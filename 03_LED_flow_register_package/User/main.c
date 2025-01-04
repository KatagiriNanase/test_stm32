#include <stm32f10x.h>
#include "Int_LED.h"
#include "Com_Util.h"
int main()
{
	uint8_t i;
	//LED��ʼ��
	Int_LED_Init();

	//����һ��LED����
	uint16_t leds[] = { LED1,LED2,LED3 };

	//ȫ���ر�
	Int_LED_OffAll(leds, 3);

	//���δ�
	while (1)
	{
		for(i=0;i<3;++i)
		{
			Int_LED_On(leds[i]);
			Com_Delay_ms(500);
			Int_LED_Off(leds[i]);
		}
	}

}
