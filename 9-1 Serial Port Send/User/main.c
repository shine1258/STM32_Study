#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint32_t ms = 500;

int main(void)
{	
	OLED_Init();	
	Serial_Init();
	
//	Serial_SendByte('A');
//	
//	uint8_t myArray[] = {0x42, 0x43, 0x44, 0x45};
//	Serial_SendArray(myArray, 4);
//	
//	Serial_SendString("\r\n");
//	
//	Serial_SendString("Hello world!\r\n");
	
	Serial_SendNumber(12345, 5);

	while(1)		
	{
		
	}
}
