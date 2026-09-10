#ifndef __MPU_H
#define __MPU_H

uint8_t MPU_ReadRegister(uint8_t Register);
void MPU_WriteRegister(uint8_t Register,uint8_t Value);
void MPU_Init(void);
void MPU_GetData(int16_t *AX,int16_t *AY,int16_t *AZ,int16_t *GX,int16_t *GY,int16_t *GZ);

#endif
