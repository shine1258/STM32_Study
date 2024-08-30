#include "stm32f10x.h" // Device header
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

	//	Serial_SendNumber(12345, 5);

	//	printf("Num = %d\r\n", 666);

	// char str[100];
	// sprintf(str, "Num = %d\r\n", 666);
	// Serial_SendString(str);

	Serial_Printf("Num = %d\r\n", 666);
	Serial_Printf("你好, 世界！\r\n");

	while (1)
	{
	}
}
