#include "stm32f10x.h"
#include "MyFlash.h"

#define STORE_PAGE_ADDRESS 0x0800FC00
#define STORE_DATA_SIZE 512

uint16_t Store_Data[STORE_DATA_SIZE] = {0};

void Store_Init(void)
{
    if (MyFlash_ReadHalfWord(STORE_PAGE_ADDRESS) != 0xA5A5)
    {
        MyFlash_ErasePage(STORE_PAGE_ADDRESS);
        MyFlash_ProgramHalfWord(STORE_PAGE_ADDRESS, 0xA5A5);

        // for 从1开始，0位置存储标志位
        for (uint16_t i = 1; i < STORE_DATA_SIZE; i++)
        {
            MyFlash_ProgramHalfWord(STORE_PAGE_ADDRESS + i * 2, 0x0000);
        }

        Store_Data[0] = 0xA5A5;
    }
    else
    {
        for (uint16_t i = 0; i < STORE_DATA_SIZE; i++)
        {
            Store_Data[i] = MyFlash_ReadHalfWord(STORE_PAGE_ADDRESS + i * 2);
        }
    }
}

void Store_Save(void)
{
    MyFlash_ErasePage(STORE_PAGE_ADDRESS);

    for (uint16_t i = 0; i < STORE_DATA_SIZE; i++)
    {
        MyFlash_ProgramHalfWord(STORE_PAGE_ADDRESS + i * 2, Store_Data[i]);
    }
}

void Store_Clear(void)
{
    for (uint16_t i = 1; i < STORE_DATA_SIZE; i++)
    {
        Store_Data[i] = 0x0000;
    }

    Store_Save();
}