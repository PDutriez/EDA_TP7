#include "HitachiLCD.h"
/*********************************** CONSTANTES ***********************************/
#define MIN_ROW 0				//Cantidad Minima de filas
#define MAX_ROW 1				//Cantidad Maxima de filas
#define MIN_COL 0				//Cantidad Minima de columnas
#define MAX_COL 15				//Cantidad Maxima de columnas
#define BEGIN_FIRST_LINE 0		//Inicio de la primera linea
#define END_FIRST_LINE 15		//Fin de la primera linea
#define BEGIN_SECOND_LINE 16	//Inicio de la Segunda linea
#define END_SECOND_LINE 31		//Final de la segunda linea
#define FirstLine(a) (( a>=BEGIN_FIRST_LINE)&&( a<=END_FIRST_LINE)) //Estoy en la primer linea?
#define SecondLine(a) (( a>=BEGIN_SECOND_LINE)&&( a<=END_SECOND_LINE)) //Estoy en la segunda linea?
#define DDRAM_ADRESS 0x80		//Comando para setear DDRAM
#define OFFSET_SECOND_LINE 0x30	//Distancia entre primer y segunda linea
#define ERROR_POS -1 //Valor de error para posiciones
bool HitachiLCD::lcdInitOk()
{

}

FT_STATUS HitachiLCD::lcdGetError()
{

}

bool HitachiLCD::lcdClear()
{

}

bool HitachiLCD::lcdClearToEOL()
{

}

basicLCD& HitachiLCD::operator<<(const unsigned char c)
{

}

basicLCD& HitachiLCD::operator<<(const unsigned char * c)
{

}

/*Phil*/
bool
HitachiLCD::lcdMoveCursorUp()
{
	if (FirstLine(cadd))
		return true; 	//Ya estamos arriba de todo
	else if (SecondLine(cadd))
	{
		cursorPosition newPos;
		newPos.column = cadd - MAX_COL;
		newPos.row = 0;
		return(lcdSetCursorPosition(newPos));
	}
	else return false; //No se donde estoy...
}

bool
HitachiLCD::lcdMoveCursorDown()
{
	if (SecondLine(cadd))
		return true;	//No se puede ir mas bajo que el infierno
	else if (FirstLine(cadd))
	{
		cursorPosition newPos;
		newPos.column = cadd;
		newPos.row = 1;
		return(lcdSetCursorPosition(newPos));
	}
	else
		return false; //No se donde estoy...
}

bool
HitachiLCD::lcdMoveCursorRight()
{
	if ((cadd>=BEGIN_FIRST_LINE)&&(cadd < END_SECOND_LINE))//Todo menos la ultima
	{
		cursorPosition newPos;
		if (SecondLine(cadd)) 
		{
			newPos.row = 1;
			newPos.column = cadd - MAX_COL;//NO es necesario hacer +1!
		}
		else if (FirstLine(cadd) && (cadd != END_FIRST_LINE))//Todo menos la ultima
		{
			newPos.row = 0;
			newPos.column = cadd + 1;
		}
/* PARA CUANDO RICHARD SE DECIDA!!!
		else if (cadd == END_FIRST_LINE) //Estoy en la primer linea al final
		{
			newPos.row = 1;
			newPos.column = 0;
		}
*/
		return(lcdSetCursorPosition(newPos));
		
	}
	else return false;//Estoy al final
}

bool
HitachiLCD::lcdMoveCursorLeft()
{
	if ((cadd > BEGIN_FIRST_LINE) && (cadd <= END_SECOND_LINE))//Todo menos la primera
	{
		cursorPosition newPos;
		if (FirstLine(cadd))
		{
			newPos.row = 0;
			newPos.column = cadd - 1;
		}
		else if (SecondLine(cadd) && (cadd != BEGIN_SECOND_LINE))
		{
			newPos.row = 1;
			newPos.column = cadd - (MAX_COL+1) -1;//Escritura para mejor entendimiento
		}
/* PARA CUANDO RICHARD SE DECIDA!!
		else if (cadd == BEGIN_SECOND_LINE)
		{
			newPos.row = 0;
			newPos.column = END_FIRST_LINE;
		}
*/
		return(lcdSetCursorPosition(newPos));
	}
	else return false;//Estoy al principio
}

bool
HitachiLCD::lcdSetCursorPosition(const cursorPosition pos)
{
	if (pos.column <= MAX_COL && pos.column >= MIN_COL && pos.row <= MAX_ROW && pos.row >= MIN_ROW)
	{
		cadd = pos.column + MAX_COL * pos.row;
		lcdUpdateCursor();
		return true;
	}
	else return false; //A donde queres ir?
}

cursorPosition
HitachiLCD::lcdGetCursorPosition()
{
	cursorPosition currPos;
	if (FirstLine(cadd))
	{
		currPos.row = 0;
		currPos.column = cadd;
	}
	else if (SecondLine(cadd))
	{
		currPos.row = 1;
		currPos.column = cadd - (MAX_COL+1);
	}
	else 
	{
		currPos.column = ERROR_POS;
		currPos.row = ERROR_POS;
	}

	return currPos;
}

void
HitachiLCD::lcdUpdateCursor()
{
	unsigned char cadd_ = cadd; //Copia para envio

	if (SecondLine(cadd))
		cadd_ += OFFSET_SECOND_LINE;

	lcdWriteByte(handler,DDRAM_ADRESS | cadd_, RS_INST);
}