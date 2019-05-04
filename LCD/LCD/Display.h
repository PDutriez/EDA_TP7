#pragma once
/*********************************** BIBLIOTECAS ***********************************/
#define FTD2XX_EXPORTS //Debe definirse la constante antes de la biblioteca
#include "ftd2xx.h"
//#include "Timer.h"
/*********************************** CONSTANTES ***********************************/
//Flag to recieve or not bits info
#define LCD_ENABLE_ON 0x01
#define LCD_ENABLE_OFF 0xFE
#define RS_INSTRUCTION 1	//Flag identificador de instruccion de RS							
#define RS_DATA 0 //Flag identificador de data de RS
#define FUNCIONCLEAR 0x01 //Funcion Clear
//Funcion set y config
#define FUNSET 0x02
#define FUNSET_8BITS (FUNSET | 0x01)
#define FUNSET_4BITS FUNSET
#define FUNSET_2LINES_5X8 ( (FUNSET_4BITS << 4) | 0x08 )	

//Display control con todo set off
#define DISPLAYONOFF 0x0E

//Entry set mode para inicializacion
#define ENTRYMODESET 0x0C

typedef unsigned long DWORD;

/*Secuencia de incialización del lcd*/
bool initDisplay(const char * displayName, FT_HANDLE& display);

/*La funcion lcd_SendData recibe un byte de información e invoca a lcdWriteNyble enviando el Nyble mas significativo
en primer lugar y luego el menos significativo, tambien recibe el bool de RS y el puntero a handle para poder enviar al
lcd la info*/
void lcd_SendData(byte data, bool rs, FT_HANDLE& handle);

/*La función lcdWriteNyble toma la información del byte y mediante el bool rs_ decide si lo que le llegó es dato a
imprimir en pantalla o una instruccion para el lcd */
void lcdWriteNyble(FT_HANDLE & h, byte d, bool rs_);
