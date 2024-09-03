#include "stm32f10x.h"

uint32_t MyFlash_ReadWord(uint32_t address)
{
    return *((__IO uint32_t *)(address));
}

uint16_t MyFlash_ReadHalfWord(uint32_t address)
{
    return *((__IO uint16_t *)(address));
}

uint8_t MyFlash_ReadByte(uint32_t address)
{
    return *((__IO uint8_t *)(address));
}

void MyFlash_EraseAllPages(void)
{
    FLASH_Unlock();
    FLASH_EraseAllPages();
    FLASH_Lock();
}

void MyFlash_ErasePage(uint32_t pageAddress)
{
    FLASH_Unlock();
    FLASH_ErasePage(pageAddress);
    FLASH_Lock();
}

void MyFlash_ProgramWord(uint32_t address, uint32_t data)
{
    FLASH_Unlock();
    FLASH_ProgramWord(address, data);
    FLASH_Lock();
}

void MyFlash_ProgramHalfWord(uint32_t address, uint16_t data)
{
    FLASH_Unlock();
    FLASH_ProgramHalfWord(address, data);
    FLASH_Lock();
}
