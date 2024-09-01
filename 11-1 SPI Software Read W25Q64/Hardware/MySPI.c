#include "stm32f10x.h"

void MySPI_W_SS(uint8_t bitValue);
void MySPI_W_SCK(uint8_t bitValue);

/// @brief MySPI初始化, 使用SPI模式0
/// @param
void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    MySPI_W_SS(1);  // 默认不选中从机
    MySPI_W_SCK(0); // 默认时钟低电平
}

void MySPI_W_SS(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)bitValue);
}

void MySPI_W_SCK(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)bitValue);
}

void MySPI_W_MOSI(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)bitValue);
}

uint8_t MySPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Start(void)
{
    MySPI_W_SS(0);
}

void MySPI_Stop(void)
{
    MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t byte)
{
    uint8_t received = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(byte & (0x80 >> i));
        MySPI_W_SCK(1);
        received |= (MySPI_R_MISO() << (7 - i));
        MySPI_W_SCK(0);
    }

    return received;
}
