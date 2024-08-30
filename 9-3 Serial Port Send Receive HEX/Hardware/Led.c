#include "stm32f10x.h"

void Led_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);
}

void Led_1_On(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}

void Led_1_Off(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
}

void Led_1_Turn(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3));
}

void Led_2_On(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void Led_2_Off(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

void Led_2_Turn(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, 1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4));
}