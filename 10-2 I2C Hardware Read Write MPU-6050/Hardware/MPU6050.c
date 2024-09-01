#include "MPU6050.h"
#include "MPU6050_Reg.h"
#include "stm32f10x.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 50000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2, &I2C_InitStructure);

    I2C_Cmd(I2C2, ENABLE);

    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,
                     0x01); // 退出睡眠模式, 陀螺仪X轴作为时钟源
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

void MPU6050_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
    uint32_t timeout = 10000;

    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        timeout--;

        if (timeout == 0)
            break;
    }
}

uint8_t MPU6050_ReadReg(uint8_t reg)
{
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT); // 等待 EV5

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待 EV6

    I2C_SendData(I2C2, reg);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED); // 等待 EV8_2

    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT); // 等待 EV5

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED); // 等待 EV6

    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);                          // 只接收一个字节时要提前关闭应答位和设置停止位
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED); // 等待 EV7

    uint8_t data = I2C_ReceiveData(I2C2);
    I2C_AcknowledgeConfig(I2C2, ENABLE);

    return data;
}

void MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT); // 等待 EV5

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待 EV6

    I2C_SendData(I2C2, reg);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待 EV8

    I2C_SendData(I2C2, data);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED); // 等待 EV8_2

    I2C_GenerateSTOP(I2C2, ENABLE);
}

void MPU6050_GetData(int16_t *accX, int16_t *accY, int16_t *accZ,
                     int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ)
{
    uint8_t dataH;
    uint8_t dataL;

    dataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    dataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *accX = (int16_t)((dataH << 8) | dataL);

    dataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    dataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *accY = (int16_t)((dataH << 8) | dataL);

    dataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    dataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *accZ = (int16_t)((dataH << 8) | dataL);

    dataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    dataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *gyroX = (int16_t)((dataH << 8) | dataL);

    dataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    dataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *gyroY = (int16_t)((dataH << 8) | dataL);

    dataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    dataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *gyroZ = (int16_t)((dataH << 8) | dataL);
}
