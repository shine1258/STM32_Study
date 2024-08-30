#include "stm32f10x.h" // Device header
#include <stdio.h>
#include <stdarg.h>

static uint8_t rxFlag;
uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t byte)
{
	USART_SendData(USART1, byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		;
}

void Serial_SendArray(uint8_t *array, uint16_t length)
{
	for (uint16_t i = 0; i < length; i++)
	{
		Serial_SendByte(array[i]);
	}
}

void Serial_SendString(char *str)
{
	for (uint16_t i = 0; str[i] != '\0'; i++)
	{
		Serial_SendByte(str[i]);
	}
}

uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
	uint32_t result = 1;

	while (y--)
	{
		result *= x;
	}

	return result;
}

void Serial_SendNumber(uint32_t num, uint8_t len)
{
	for (uint8_t i = 0; i < len; i++)
	{
		Serial_SendByte(num / Serial_Pow(10, len - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char buffer[100];

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	Serial_SendString(buffer);
}

void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket, 4);
	Serial_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)
{
	if (rxFlag == 1)
	{
		rxFlag = 0;
		return 1;
	}

	return 0;
}

void USART1_IRQHandler(void)
{
	static uint8_t rxState = 0;
	static uint8_t rxIndex = 0;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t rxData = USART_ReceiveData(USART1);

		if (rxState == 0)
		{
			if (rxData == 0xFF)
			{
				rxState = 1;
				rxIndex = 0;
			}
		}
		else if (rxState == 1)
		{
			Serial_RxPacket[rxIndex++] = rxData;

			if (rxIndex >= 4)
			{
				rxState = 2;
			}
		}
		else if (rxState == 2)
		{
			if (rxData == 0xFE)
			{
				rxState = 0;
				rxFlag = 1;
			}
		}

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}