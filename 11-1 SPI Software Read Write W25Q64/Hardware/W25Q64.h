#ifndef __W25Q64_H
#define __W25Q64_H

#include "stm32f10x.h"

void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q64_PageProgram(uint32_t address, uint8_t *data, uint16_t count);
void W25Q64_SectorErase(uint32_t address);
void W25Q64_ReadData(uint32_t address, uint8_t *data, uint32_t count);

#endif