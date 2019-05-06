#pragma once
/*********************************** BIBLIOTECAS ***********************************/
#define FTD2XX_EXPORTS //Debe definirse la constante antes de la biblioteca
#include "ftd2xx.h"
/*********************************** CONSTANTES ***********************************/
//Asignacion de nombres a las posiciones fisicas de los bits
#define PORT_P0 0
#define PORT_P1 1
#define PORT_P2 2
#define PORT_P3 3
#define PORT_P4 4
#define PORT_P5 5
#define PORT_P6 6
#define PORT_P7 7

//Asignacion logica o funcional a cada bit fisico
#define LCD_E (1<<PORT_P0)
#define LCD_RS (1<<PORT_P1)
#define LCD_D4 (1<<PORT_P4)
#define LCD_D5 (1<<PORT_P5)
#define LCD_D6 (1<<PORT_P6)
#define LCD_D7 (1<<PORT_P7)

//Definicion de niveles logicos
//Activo alto
#define LCD_RS_ON	(LCD_RS)
#define LCD_D4_ON	(LCD_D4)			
#define LCD_D5_ON	(LCD_D5)
#define LCD_D6_ON	(LCD_D6)
#define LCD_D7_ON	(LCD_D7)
//Activo bajo
#define	LCD_RS_OFF	(LCD_RS ^ LCD_RS)
#define LCD_D4_OFF	(LCD_D4 ^ LCD_D4)	  
#define LCD_D5_OFF	(LCD_D5 ^ LCD_D5)
#define LCD_D6_OFF	(LCD_D6 ^ LCD_D6)
#define LCD_D7_OFF	(LCD_D7 ^ LCD_D7)


//Funcion set y config
#define FUNSET 0x02
#define FUNSET_8BITS (FUNSET | 0x01)
#define FUNSET_4BITS FUNSET
#define FUNSET_2LINES_5X8 ( (FUNSET_4BITS << 4) | 0x08 )	

//Display control con todo set off
#define DISPLAYONOFF 0x0E

//Instrucciones
#define LCD_CLEAR_DISPLAY			(1<<PORT_P0)
#define LCD_RETURN_HOME				(1<<PORT_P1)
#define LCD_ENTRY_MODE_SET			(1<<PORT_P2)
#define LCD_DISPLAY_CONTROL			(1<<PORT_P3)
#define LCD_CURSOR_OR_DISPLAY_SHIFT	(1<<PORT_P4)
#define LCD_FUNCTION_SET			(1<<PORT_P5)
#define LCD_SET_CGRAM_ADDRESS		(1<<PORT_P6)
#define LCD_SET_DDRAM_ADDRESS		(1<<PORT_P7)

#define LCD_ENABLE_ON 0x01
#define LCD_ENABLE_OFF 0xFE
#define RS_INST 1	//Flag identificador de instruccion de RS							
#define RS_DATA 0 //Flag identificador de data de RS
#define FUNCLR 0x01 //Funcion Clear
#define FUNSET 0x02 //Function Set
#define FUNSET_8BITS (FUNSET | 0x01) //Set LCD to 8 bits
#define FUNSET_4BITS FUNSET
#define FUNSET_2LINES_5X8 ( (FUNSET_4BITS << 4) | 0x08 )	
//#define DISPLAYONOFF 0x08 //Display control con todo set off
#define ENTRYMODESET 0x06 //Entry set mode para inicializacion
#define MS_NIBBLE(a)	(a << 4) //Most Significant Nybble
#define LS_NIBBLE(a)	(a >> 4) //Less Significant Nybble

/*mascaras*/
#define GET_MS_NIBBLE 0xF0
#define GET_LS_NIBBLE 0x0F

typedef unsigned long DWORD;

/*********************************** FUNCIONES ***********************************/
/*LCDINIT: Inicializa el display correctamente.
* RECIBE:	- displayName: nombre del display
*			- display: ...
*
* DEVUELVE: true si logro inicializarlo y false en caso contrario.
*/
bool lcdInit(const char * displayName, FT_HANDLE& display);



/*LCDWRITEBYTE: recibe un byte de informacion y manda dicha informacion al LCD. Tambien,
*				recibe el bool de RS y el puntero a handle para poder enviar info.
* RECIBE:	- handle: ...
*			- data: el byte de informacion.
*			- rs: el valor de rs que diferencia entre instruccion y dato.
*		
*/
void lcdWriteByte(FT_HANDLE& handle, byte data, bool rs_);

/*LCDWRITENIBBLE: discrimina entre instruccion y dato mediante "rs" y lo manda al lcd.
* RECIBE:	- h: ...
*			- data: el byte con la informacion o instruccion.
*			- rs: flag de instruccion o dato.
*/
void lcdWriteNibble(FT_HANDLE & h, byte d, bool rs_);

