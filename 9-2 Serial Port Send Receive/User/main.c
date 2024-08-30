#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t rxData;
uint32_t ms = 500;

int main(void)
{
	OLED_Init();
	Serial_Init();

	OLED_ShowString(1, 1, "RxData: ");

	while (1)
	{
		if (Serial_GetRxFlag() == 1)
		{
			rxData = Serial_GetRxData();
			Serial_SendByte(rxData);
			OLED_ShowHexNum(1, 1, rxData, 2);
		}
	}
}
