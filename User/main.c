#include "stm32f10x.h"      
#include "OLED.h"
#include "HI2C.h"

/**/
int main(void)
{
	OLED_Init();
	HI2C_Init();
	OLED_ShowChar(1,1,'a');

	HI2C_Start();
	HI2C_SendByte(0xD0);
	uint8_t ACK = HI2C_ReciveACK();
	HI2C_Stop();

	OLED_ShowNum(2,1,ACK,3);
	while(1)
	{

	}
}


