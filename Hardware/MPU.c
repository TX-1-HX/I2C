#include "stm32f10x.h"                  // Device header
#include"HI2C.h"
#include"MPU_Register.h"

void MPU_WriteRegister(uint8_t Register,uint8_t Value)
{
    //指定地址写：开始，指定设备地址，应答，指定寄存器地址，应答，写入数据，应答，停止
    HI2C_Start();
    HI2C_SendByte(0XD0);   
    HI2C_ReciveACK();
    HI2C_SendByte(Register);
    HI2C_ReciveACK();
    HI2C_SendByte(Value);
    HI2C_ReciveACK();
    HI2C_Stop();
}

uint8_t MPU_ReadRegister(uint8_t Register)
{
    uint8_t data;
    //指定地址读：开始，指定设备，应答，指定寄存器地址（因为此处指定的寄存器地址是写入的，对于读取通常需要地址加1，所以需要重新开始一次），
    //应答，重新开始，读取数据，应答，停止，返回数据
    HI2C_Start();
    HI2C_SendByte(0XD0);
    HI2C_ReciveACK();
    HI2C_SendByte(Register);
    HI2C_ReciveACK();

    HI2C_Start();
    HI2C_SendByte(0XD0 | 0X01);
    HI2C_ReciveACK();
    data = HI2C_ReciveByte();
    HI2C_SendACK(1);
    HI2C_Stop();
    
    return data;

}

void MPU_Init(void)
{
    HI2C_Init();
    MPU_WriteRegister(MPU6050_PWR_MGMT_1,0X1);
    MPU_WriteRegister(MPU6050_PWR_MGMT_2,0x00);
    MPU_WriteRegister(MPU6050_SMPLRT_DIV,0x09);
    MPU_WriteRegister(MPU6050_CONFIG,0x06);
    MPU_WriteRegister(MPU6050_GYRO_CONFIG,0x18);
    MPU_WriteRegister(MPU6050_ACCEL_CONFIG,0x18);
}


void MPU_GetData(int16_t *AX,int16_t *AY,int16_t *AZ,int16_t *GX,int16_t *GY,int16_t *GZ)
{
    int16_t Data_H,Data_L;

    Data_H = MPU_ReadRegister(MPU6050_ACCEL_XOUT_H);
    Data_L = MPU_ReadRegister(MPU6050_ACCEL_XOUT_L);
    *AX = (Data_H<<8) | Data_L;

    Data_H = MPU_ReadRegister(MPU6050_ACCEL_YOUT_H);
    Data_L = MPU_ReadRegister(MPU6050_ACCEL_YOUT_L);
    *AY = (Data_H<<8) | Data_L;

    Data_H = MPU_ReadRegister(MPU6050_ACCEL_ZOUT_H);
    Data_L = MPU_ReadRegister(MPU6050_ACCEL_ZOUT_L);
    *AZ = (Data_H<<8) | Data_L;
    
    Data_H = MPU_ReadRegister(MPU6050_GYRO_XOUT_H);
    Data_L = MPU_ReadRegister(MPU6050_GYRO_XOUT_L);
    *GX = (Data_H<<8) | Data_L;

    Data_H = MPU_ReadRegister(MPU6050_GYRO_YOUT_H);
    Data_L = MPU_ReadRegister(MPU6050_GYRO_YOUT_L);
    *GY = (Data_H<<8) | Data_L;

    Data_H = MPU_ReadRegister(MPU6050_GYRO_ZOUT_H);
    Data_L = MPU_ReadRegister(MPU6050_GYRO_ZOUT_L);
    *GZ = (Data_H<<8) | Data_L;
}
