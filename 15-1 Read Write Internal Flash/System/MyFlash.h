#ifndef __MY_FLASH_H
#define __MY_FLASH_H

#include "stm32f10x.h"

uint32_t MyFlash_ReadWord(uint32_t address);
uint16_t MyFlash_ReadHalfWord(uint32_t address);
uint8_t MyFlash_ReadByte(uint32_t address);
void MyFlash_EraseAllPages(void);
void MyFlash_ErasePage(uint32_t pageAddress);
void MyFlash_ProgramWord(uint32_t address, uint32_t data);
void MyFlash_ProgramHalfWord(uint32_t address, uint16_t data);

#endif