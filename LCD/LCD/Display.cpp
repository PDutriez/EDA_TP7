#include "Display.h"
#include <Windows.h>

bool initDisplay(const char * displayName, FT_HANDLE& display)
{
	bool init = false;
	if (FT_OpenEx((LPVOID)displayName, FT_OPEN_BY_DESCRIPTION, &display) == FT_OK) 
	{
		byte allPins = 0xff, asyncMode = 1;
		if (FT_SetBitMode(display, allPins, asyncMode) == FT_OK)
		{
			init = true; //Se pudo inicializar
			// Mando 3 veces el modo de 8 bits
			lcdWriteNyble(display, FUNSET_8BITS, RS_INST);
			Sleep(5);
			lcdWriteNyble(display, FUNSET_8BITS, RS_INST);
			Sleep(1);
			lcdWriteNyble(display, FUNSET_8BITS, RS_INST);
			lcdWriteNyble(display, FUNSET_4BITS, RS_INST); // Mandamos el modo de 4 bits
			lcd_SendData(FUNSET_2LINES_5X8, RS_INST, display); //Enviamos Funcion set en modo 4 bits, 2 líneas y fuente de 5x8 
			lcd_SendData(DISPLAYONOFF, RS_INST, display);	//DiplayOnOff config
			lcd_SendData(FUNCLR, RS_INST, display);	//limpiar la pantalla
			lcd_SendData(ENTRYMODESET, RS_INST, display);	//Entry mode set
		}
	}
	return init;
}

void lcd_SendData(byte data, bool rs_, FT_HANDLE& handle)
{
	lcdWriteNyble(handle, data >> 4, rs_);		//mando el nybble mas significativo.
	lcdWriteNyble(handle, data, rs_);			//mando el nybble menos significativo.
}

void lcdWriteNyble(FT_HANDLE& handle, byte data, bool rs_)
{
	DWORD sent = 0;
	unsigned char temp;
	temp = ((data << 4) & (byte)(0xF0));
	if (rs_)
	{	
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);								//delay de 1 ms
		temp = (temp | (LCD_ENABLE_ON));
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(3);								//delay de 3ms.
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);								//delay de 1 ms
	}
	else
	{
		temp = (temp | (0x02)) & (LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);								//delay de 1 ms
		sent = 0;
		temp = temp | (LCD_ENABLE_ON);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(3);								//delay de 3ms.
		sent = 0;
		temp = temp & (LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);
	}
}
