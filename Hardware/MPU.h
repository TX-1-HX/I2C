#ifndef __MPU_H
#define __MPU_H

uint8_t MPU_ReadRegister(uint8_t Register);
void MPU_WriteRegister(uint8_t Register,uint8_t Value);
void MPU_Init(void);

#endif
