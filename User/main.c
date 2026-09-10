#include "stm32f10x.h"      
#include "OLED.h"
#include "HI2C.h"
#include "MPU.h"
/**/
int main(void)
{
	OLED_Init();
	MPU_Init();

	//MPU_WriteRegister(0X6B,0X00);
	//MPU_WriteRegister(0X19,0XAA);
	
	//uint8_t ID = MPU_ReadRegister(0X19);

	//OLED_ShowHexNum(1,1,ID,3);
	int16_t AX,AY,AZ,GX,GY,GZ;
	while(1)
	{
		MPU_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
		OLED_ShowNum(1,1,AX,5);
		OLED_ShowNum(2,1,AY,5);
		OLED_ShowNum(3,1,AZ,5);
		OLED_ShowNum(1,8,GX,5);
		OLED_ShowNum(2,8,GY,5);
		OLED_ShowNum(3,8,GZ,5);
	}
}


