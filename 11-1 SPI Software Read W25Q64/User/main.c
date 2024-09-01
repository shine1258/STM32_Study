#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

uint8_t MID = 0;
uint16_t DID = 0;
uint8_t writeData[] = {0x01, 0x02, 0x03, 0x04};
uint8_t readData[4] = {0};

int main(void)
{
	OLED_Init();
	W25Q64_Init();

	OLED_ShowString(1, 1, "MID:");
	OLED_ShowString(1, 8, "DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");

	W25Q64_ReadID(&MID, &DID);
	OLED_ShowHexNum(1, 5, MID, 2);
	OLED_ShowHexNum(1, 12, DID, 4);

	W25Q64_SectorErase(0x000000);
	W25Q64_PageProgram(0x000000, writeData, 4);
	W25Q64_ReadData(0x000000, readData, 4);

	OLED_ShowHexNum(2, 3, writeData[0], 2);
	OLED_ShowHexNum(2, 6, writeData[1], 2);
	OLED_ShowHexNum(2, 9, writeData[2], 2);
	OLED_ShowHexNum(2, 12, writeData[3], 2);

	OLED_ShowHexNum(3, 3, readData[0], 2);
	OLED_ShowHexNum(3, 6, readData[1], 2);
	OLED_ShowHexNum(3, 9, readData[2], 2);
	OLED_ShowHexNum(3, 12, readData[3], 2);

	while (1)
	{
		}
}
