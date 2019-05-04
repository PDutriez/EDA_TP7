#pragma once
/*********************************** BIBLIOTECAS ***********************************/
#define FTD2XX_EXPORTS //Debe definirse la constante antes de la biblioteca
#include "ftd2xx.h"
//#include "Timer.h"
/************************************ CONSTANTES ***********************************/
#define LCD_ENABLE_ON 0x01
#define LCD_ENABLE_OFF 0xFE
#define RS_INST 1	//Flag identificador de instruccion de RS							
#define RS_DATA 0 //Flag identificador de data de RS
#define FUNCLR 0x01 //Funcion Clear
#define FUNSET 0x02 //Function Set
#define FUNSET_8BITS (FUNSET | 0x01) //Set LCD to 8 bits
#define FUNSET_4BITS FUNSET
#define FUNSET_2LINES_5X8 ( (FUNSET_4BITS << 4) | 0x08 )	
#define DISPLAYONOFF 0x0E //Display control con todo set off
#define ENTRYMODESET 0x0C //Entry set mode para inicializacion

typedef unsigned long DWORD;
/************************************ FUNCIONES ***********************************/
/*INITDISPLAY: Inicializa el display correctamente.
* RECIBE:	- displayName: nombre del display
*			- display: ...
*
* DEVUELVE: true si logro inicializarlo y false en caso contrario.
*/
bool initDisplay(const char * displayName, FT_HANDLE& display);

/*LCD_SENDDATA: recibe un byte de informacion y manda dicha informacion al LCD. Tambien,
*				recibe el bool de RS y el puntero a handle para poder enviar info.
* RECIBE:	- data: el byte de informacion.
*			- rs: el valor de rs que diferencia entre instruccion y dato.
*			- handle: ...
*/
void lcd_SendData(byte data, bool rs, FT_HANDLE& handle);

/*LCDWRITENYBLE: discrimina entre instruccion y dato mediante "rs" y lo manda al lcd.
* RECIBE:	- h: ...
*			- data: el byte con la informacion o instruccion.
*			- rs: flag de instruccion o dato.
*/
void lcdWriteNyble(FT_HANDLE & h, byte data, bool rs_);
