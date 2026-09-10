#include "stm32f10x.h"      
#include "OLED.h"
#include "HI2C.h"
#include "MPU.h"
/**/
int main(void)
{
	OLED_Init();
	MPU_Init();

	MPU_WriteRegister(0X68,0X00);
	MPU_WriteRegister(0X19,0XAA);
	uint8_t ID = MPU_ReadRegister(0X19);

	OLED_ShowHexNum(1,1,ID,3);

	while(1)
	{

	}
}


