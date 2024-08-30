#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int16_t num;
uint32_t ms = 500;

int main(void)
{	
	OLED_Init();
	Encoder_Init();
 
	OLED_ShowString(1, 1, "Num: ");
	
	while(1)		
	{
		num += Encoder_Get();
		OLED_ShowSignedNum(1, 6, num, 5);
	}
}
