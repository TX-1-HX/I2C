#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//配置GPIO结构体，PB10,PB11，分别为开漏输出，速率为50KHz
void HI2C_Init(void)
{
    //使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

void HI2C_W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
    Delay_us(10);
}

void HI2C_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
    Delay_us(10);
}

uint8_t HI2C_R_SDA(void)
{
    return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
}

void HI2C_Start(void)
{
    HI2C_W_SDA(1);
    HI2C_W_SCL(1);
    HI2C_W_SDA(0);
    HI2C_W_SCL(0);

}

void HI2C_Stop(void)
{
    HI2C_W_SDA(0);
    HI2C_W_SCL(1);
    HI2C_W_SDA(1);

}

void HI2C_SendByte(uint8_t Byte)
{
    for(uint8_t i = 0; i<8;i++)
    {
        HI2C_W_SDA(Byte & (0x80 >> i));
        HI2C_W_SCL(1);
        HI2C_W_SCL(0);
    }
}

uint8_t HI2C_ReciveByte(void)
{
    uint8_t Byte =0X00;
    HI2C_W_SDA(1);
    for(uint8_t i = 0;i<8;i++)
    {
        HI2C_W_SCL(1);
        if(HI2C_R_SDA() == 1)
        {
            Byte |= (0X80 >>i);
        }
        HI2C_W_SCL(0);
    }
    return Byte;
}

void HI2C_SendACK(uint8_t ACK)
{
    HI2C_W_SDA(ACK);
    HI2C_W_SCL(1);
    HI2C_W_SCL(0);
}

uint8_t HI2C_ReciveACK(void)
{
    HI2C_W_SDA(1);
    HI2C_W_SCL(1);
    uint8_t ACK = HI2C_R_SDA();
    HI2C_W_SCL(0);
    return ACK;
}
