#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint32_t ms = 500;

int main(void)
{
	Buzzer_Init();
	LightSensor_Init();
	
	while(1)
	{
		if (LightSensor_Get() == 1)
		{
			Buzzer_On();
		}
		else
		{
			Buzzer_Off();
		}
	}
}
