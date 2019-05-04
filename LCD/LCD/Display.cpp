#include "Display.h" 

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
			Sleep(1);
			//A partir de ahora se envia en 2 nybbles
			lcdWriteNyble(display, FUNSET_4BITS, RS_INST); // Mandamos el modo de 4 bits
			lcd_SendData(FUNSET_2LINES_5X8, RS_INST, display); //Enviamos Funcion set en modo 4 bits, 2 líneas y fuente de 5x8 
			lcd_SendData(DISPLAYONOFF, RS_INST, display);	//DiplayOnOff control
			lcd_SendData(FUNCLR, RS_INST, display);	//limpiar la pantalla
			Sleep(10);
			lcd_SendData(ENTRYMODESET, RS_INST, display);	//Entry mode set
		}
	}
	return init;
}

void lcd_SendData(byte data, bool rs_, FT_HANDLE& handle)
{
	lcdWriteNyble(handle, LS_NYBBLE(data), rs_);		//mando el nybble mas significativo.
	lcdWriteNyble(handle, data, rs_);			//mando el nybble menos significativo.
}

void lcdWriteNyble(FT_HANDLE& handle, byte data, char rs_)
{
	DWORD sent = 0;
	unsigned char temp;
	temp = (MS_NYBBLE(data) & (byte)(0xF0)); //Casteo a byte por si acaso...

	if (rs_ == RS_INST)  //INGRESO DE INSTRUCCIONES
	{	
		temp = (temp & LCD_ENABLE_OFF); //Apago el enable
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent); //Mando la instruccion
		Sleep(1); //delay de 1 ms
		temp = (temp | (LCD_ENABLE_ON));
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent); //Hago "ENTER"
		Sleep(3); //delay de 3ms.
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent); //Mando la instruccion de nuevo...
		Sleep(1);								//delay de 1 ms
	}
	else				//INGRESO DE DATOS
	{
		temp = (temp | (0x02)) & (LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);	//delay de 1 ms
		sent = 0;
		temp = temp | (LCD_ENABLE_ON);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(3);	//delay de 3ms.
		sent = 0;
		temp = temp & (LCD_ENABLE_OFF);
		FT_Write(handle, (LPVOID)&temp, sizeof(temp), &sent);
		Sleep(1);
	}
}
