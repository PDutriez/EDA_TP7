#include "Display.h"
#include <unistd>
#include <Windows.h>

bool initDisplay(const char * displayName, FT_HANDLE& display)
{
	bool init = false;
	if (FT_OpenEx((void* )displayName, FT_OPEN_BY_DESCRIPTION, &display) == FT_OK) 
	{
		byte allPins = 0xff, asyncMode = 1;
		if (FT_SetBitMode(display, allPins, asyncMode) == FT_OK)
		{
			init = true; //Se pudo inicializar
			// Mando 3 veces el modo de 8 bits
			lcdWriteNyble(display, FUNSET_8BITS, RS_INSTRUCTION);
			Sleep(5);
			lcdWriteNyble(display, FUNSET_8BITS, RS_INSTRUCTION);
			Sleep(1);
			lcdWriteNyble(display, FUNSET_8BITS, RS_INSTRUCTION);
			lcdWriteNyble(display, FUNSET_4BITS, RS_INSTRUCTION); // Mandamos el modo de 4 bits
			lcd_SendData(FUNSET_2LINES_5X8, RS_INSTRUCTION, display); //Enviamos Funcion set en modo 4 bits, 2 líneas y fuente de 5x8 
			//DiplayOnOff config
			lcd_SendData(DISPLAYONOFF, RS_INSTRUCTION, display);	//0x0E
			//limpiar la pantalla
			lcd_SendData(FUNCIONCLEAR, RS_INSTRUCTION, display);
			//Entry mode set
			lcd_SendData(ENTRYMODESET, RS_INSTRUCTION, display);	//0x0C
		}
	}
	return init;
}

void lcd_SendData(byte data, bool rs_, FT_HANDLE& handle)
{
	lcdWriteNyble(handle, data >> 4, rs_);		//mando el nybble mas significativo.
	lcdWriteNyble(handle, data, rs_);			//mando el nybble menos significativo.
}

void lcdWriteNyble(FT_HANDLE& h, byte d, bool rs_)
{
	DWORD sent = 0;
	unsigned char temp;
	temp = ((d << 4) & (byte)(0xF0));
	if (rs_)
	{	//Secuencia de envio de Nybles para la interpretacion de una instruccion del lcd
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);								//delay de 1 ms
		temp = (temp | (LCD_ENABLE_ON));
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(3);								//delay de 3ms.
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);								//delay de 1 ms
	}
	else
	{	//Idem para un dato
		temp = (temp | (0x02)) & (LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);								//delay de 1 ms
		sent = 0;
		temp = temp | (LCD_ENABLE_ON);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(3);								//delay de 3ms.
		sent = 0;
		temp = temp & (LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);
	}
}
