#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

int16_t accX, accY, accZ, gyroX, gyroY, gyroZ;

int main(void)
{
	OLED_Init();
	MPU6050_Init();

	while (1)
	{
		MPU6050_GetData(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);
		OLED_ShowSignedNum(2, 1, accX, 5);
		OLED_ShowSignedNum(3, 1, accY, 5);
		OLED_ShowSignedNum(4, 1, accZ, 5);
		OLED_ShowSignedNum(2, 8, gyroX, 5);
		OLED_ShowSignedNum(3, 8, gyroY, 5);
		OLED_ShowSignedNum(4, 8, gyroZ, 5);
	}
}
