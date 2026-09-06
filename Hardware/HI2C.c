#include "stm32f10x.h"                  // Device header

void HI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef G;
    G.GPIO_Mode = GPIO_Mode_Out_OD;
    G.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;   //0 SCL ; 1 SDA
    G.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&G);

}

void Serial_W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(BitValue));
}

void Serial_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(BitValue));
}

uint8_t Serial_R_SDA(void)
{
    uint8_t value;
    value = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
    return value;
}

void HI2C_Start(void)  
{
    Serial_W_SDA(1);
    Serial_W_SCL(1);
    Serial_W_SDA(0);
    Serial_W_SCL(0);
}

void HI2C_Stop(void)
{
    Serial_W_SDA(0);
    Serial_W_SCL(0);
    Serial_W_SCL(1);
    Serial_W_SDA(1);
}

void HI2C_SendByte(uint8_t Byte)
{
    uint8_t i ;

    for(i = 0;i<8;i++)
    {
        Serial_W_SCL(0);
        Serial_W_SDA(Byte & (0x80 >>i));
        Serial_W_SCL(1);
    }
}

uint8_t HI2C_ReciveByte(void)
{
    uint8_t Byte = 0x00;
    Serial_W_SDA(1);
    for(uint8_t i = 0;i<8;i++)
    {
        Serial_W_SCL(0);
        Serial_W_SCL(1);
        if(Serial_R_SDA() == 1)
        {
            Byte = Byte | (0X80>>i);
        }
    }
    return Byte;
}

void HI2C_SendACK(uint8_t ACK)
{
    Serial_W_SCL(0);
    Serial_W_SDA(ACK);
    Serial_W_SCL(1);
}

uint8_t HI2C_ReciveACK(void)
{
    uint8_t ACK;
    Serial_W_SDA(1);
    Serial_W_SCL(0);
    Serial_W_SCL(1);
    ACK = Serial_R_SDA();
	return ACK;
}
