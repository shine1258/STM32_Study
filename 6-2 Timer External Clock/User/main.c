#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t num = 0;
uint32_t ms = 500;

int main(void)
{	
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1, 1, "Num: ");
	OLED_ShowString(2, 1, "CNT: ");
	 
	while(1)		
	{
		OLED_ShowNum(1, 6, num, 5);
		OLED_ShowNum(2, 6, Timer_GetCounter(), 5);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}