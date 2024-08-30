#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"                  // Device header
#include <stdio.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendArray(uint8_t *array, uint16_t length);
void Serial_SendString(char *str);
void Serial_SendNumber(uint32_t num, uint8_t len);

#endif