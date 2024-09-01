#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f10x.h"

void MPU6050_Init(void);
uint8_t MPU6050_ReadReg(uint8_t reg);
void MPU6050_WriteReg(uint8_t reg, uint8_t data);
void MPU6050_GetData(int16_t *accX, int16_t *accY, int16_t *accZ,
                     int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ);

#endif