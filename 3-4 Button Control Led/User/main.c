#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"

uint8_t keyNum;
uint32_t ms = 500;

int main(void)
{
	Led_Init();
	Key_Init();	
	
	while(1)
	{
		keyNum = Key_GetNum();
		
		if (keyNum == 1)
		{
			Led_1_Turn();
		}
		else if (keyNum == 2)
		{
			Led_2_Turn();
		}
	}
}
