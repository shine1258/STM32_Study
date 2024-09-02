#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t keyNum = 0;
uint16_t arrWrite[] = {0x1234, 0x5678};
uint16_t arrRead[2] = {0};

int main(void)
{
	OLED_Init();

	OLED_ShowString(1, 1, "W: ");
	OLED_ShowString(2, 1, "R: ");

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);

	while (1)
	{
		keyNum = Key_GetNum();

		if (keyNum == 1)
		{
			arrWrite[0]++;
			arrWrite[1]++;

			BKP_WriteBackupRegister(BKP_DR1, arrWrite[0]);
			BKP_WriteBackupRegister(BKP_DR2, arrWrite[1]);

			OLED_ShowHexNum(1, 3, arrWrite[0], 4);
			OLED_ShowHexNum(1, 8, arrWrite[1], 4);
		}

		arrRead[0] = BKP_ReadBackupRegister(BKP_DR1);
		arrRead[1] = BKP_ReadBackupRegister(BKP_DR2);

		OLED_ShowHexNum(2, 3, arrRead[0], 4);
		OLED_ShowHexNum(2, 8, arrRead[1], 4);
	}
}
