#include "stm32f10x.h"                  // Device header
#include"HI2C.h"

void MPU_Init(void)
{
    HI2C_Init();
}

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
    HI2C_Start();
    HI2C_SendByte(0XD0 | 0X01);
    data = HI2C_ReciveByte();
    HI2C_SendACK(1);
    HI2C_Stop();
    
    return data;

}