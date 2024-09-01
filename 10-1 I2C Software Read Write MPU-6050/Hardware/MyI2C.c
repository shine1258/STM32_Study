#include "stm32f10x.h"
#include "Delay.h"
#include "MyI2C.h"

void MyI2C_W_SCL(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)bitValue);
    Delay_us(10);
}

void MyI2C_W_SDA(uint8_t bitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)bitValue);
    Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
    uint8_t bitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    Delay_us(10);
    return bitValue;
}

void MyI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

void MyI2C_Start(void)
{
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        MyI2C_W_SDA(byte & (0x80 >> i));
        MyI2C_W_SCL(1);
        MyI2C_W_SCL(0);
    }
}

uint8_t MyI2C_ReceiveByte(void)
{
    uint8_t byte = 0;
    MyI2C_W_SDA(1);

    for (uint8_t i = 0; i < 8; i++)
    {
        MyI2C_W_SCL(1);
        byte |= (MyI2C_R_SDA() << (7 - i));
        MyI2C_W_SCL(0);
    }

    return byte;
}

void MyI2C_SendAck(uint8_t ackBit)
{
    MyI2C_W_SDA(ackBit);
    MyI2C_W_SCL(1);
    MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
    MyI2C_W_SDA(1);

    MyI2C_W_SCL(1);
    uint8_t byte = MyI2C_R_SDA();
    MyI2C_W_SCL(0);

    return byte;
}
