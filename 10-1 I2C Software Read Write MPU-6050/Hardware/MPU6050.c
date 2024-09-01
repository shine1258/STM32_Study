#include "stm32f10x.h"
#include "MyI2C.h"
#include "MPU6050.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_Init(void)
{
    MyI2C_Init();
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); // 退出睡眠模式, 陀螺仪X轴作为时钟源
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050_ReadReg(uint8_t reg)
{
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(reg); // 移动指针到寄存器
    MyI2C_ReceiveAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x1);
    MyI2C_ReceiveAck();
    uint8_t data = MyI2C_ReceiveByte();
    MyI2C_SendAck(1);
    MyI2C_Stop();

    return data;
}

void MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(reg);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(data);
    MyI2C_ReceiveAck();
    MyI2C_Stop();
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
