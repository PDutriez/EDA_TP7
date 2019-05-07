#include <Windows.h>
#include <stdio.h>
#include "fase1.h"

bool lcdInit(const char * displayName, FT_HANDLE& display)
{
	bool init = false;
	if (FT_OpenEx((PVOID)displayName, FT_OPEN_BY_DESCRIPTION, &display) == FT_OK)
	{
		byte allPins = 0xFF, asyncMode = 1;
		if (FT_SetBitMode(display, allPins, asyncMode) == FT_OK)
		{
			init = true; //Se pudo inicializar
			// Mando 3 veces el modo de 8 bits
			lcdWriteNibble(display, FUNSET_8BITS, RS_INST);
			Sleep(5);
			lcdWriteNibble(display, FUNSET_8BITS, RS_INST);
			Sleep(1);
			lcdWriteNibble(display, FUNSET_8BITS, RS_INST);
			Sleep(1);
			//A partir de ahora se envia en 2 nybbles
			lcdWriteNibble(display, FUNSET_4BITS, RS_INST); // Mandamos el modo de 4 bits
			Sleep(1);
			lcdWriteByte(display,FUNSET_2LINES_5X8, RS_INST); //Enviamos Funcion set en modo 4 bits, 2 líneas y fuente de 5x8 
			Sleep(1);
			lcdWriteByte(display,LCD_DISPLAY_CONTROL, RS_INST);	//DiplayOnOff control
			Sleep(1);
			lcdWriteByte(display,FUNCLR, RS_INST);	//limpiar la pantalla
			Sleep(10);
			lcdWriteByte(display,ENTRYMODESET, RS_INST);	//Entry mode set
		}
		return init;
	}
	else
	{
		printf("Cannot open display\n");
		return init;
	}
	
}



void lcdWriteByte(FT_HANDLE& handle, byte data, bool rs_) 
{
	lcdWriteNibble(handle, LS_NIBBLE((data&GET_MS_NIBBLE)), rs_);
	lcdWriteNibble(handle, (data&GET_LS_NIBBLE), rs_);

}

void lcdWriteNibble(FT_HANDLE& handle, byte data, bool rs_)
{
	DWORD sent = 0;
	unsigned char temp;
	if ((data&GET_MS_NIBBLE) != 0)
	{
		printf("Error data invalid\n");
		return;
	}
	temp = (MS_NIBBLE(data) & (byte)(0xF0)); //Casteo a byte por si acaso...

	if (rs_ == RS_INST)  //INGRESO DE INSTRUCCIONES
	{
		temp = (temp & LCD_ENABLE_OFF); //Apago el enable
		if (FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent) != FT_OK)
		{
			printf("Cannot write\n");
			return;
		} //Mando la instruccion
		Sleep(1); //delay de 1 ms
		temp = (temp | (LCD_ENABLE_ON));
		if (FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent) != FT_OK)
		{
			printf("Cannot write\n");
			return;
		} //Hago "ENTER"
		Sleep(3); //delay de 3ms.
		temp = (temp & LCD_ENABLE_OFF);
		if (FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent) != FT_OK)
		{
			printf("Cannot write\n");
			return;
		} //Mando la instruccion de nuevo...
		Sleep(1);								//delay de 1 ms
	}
	else				//INGRESO DE DATOS
	{
		temp = (temp | (0x02)) & (LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);	//delay de 1 ms
		temp = temp | (LCD_ENABLE_ON);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(3);	//delay de 3ms.
		temp = temp & (LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);
	}
}

