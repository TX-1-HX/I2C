#ifndef __HI2C_H
#define __HI2C_H

void HI2C_Init(void);
void Serial_W_SCL(uint8_t BitValue);
void Serial_W_SDA(uint8_t BitValue);
uint8_t Serial_R_SDA(void);
void HI2C_Start(void) ;
void HI2C_Stop(void);
void HI2C_SendByte(uint8_t Byte);
uint8_t HI2C_ReciveByte(void);
void HI2C_SendACK(uint8_t ACK);
uint8_t HI2C_ReciveACK(void);

#endif
