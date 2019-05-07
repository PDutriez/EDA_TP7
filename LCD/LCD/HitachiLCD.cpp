#include "HitachiLCD.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
/*********************************** CONSTANTES ***********************************/
#define MIN_ROW 0				//Cantidad Minima de filas
#define MAX_ROW 1				//Cantidad Maxima de filas
#define MIN_COL 1				//Cantidad Minima de columnas
#define MAX_COL 16				//Cantidad Maxima de columnas
#define BEGIN_FIRST_LINE 1		//Inicio de la primera linea
#define END_FIRST_LINE 16		//Fin de la primera linea
#define BEGIN_SECOND_LINE 17	//Inicio de la Segunda linea
#define END_SECOND_LINE 32		//Final de la segunda linea
#define FirstLine(a) (( a>=BEGIN_FIRST_LINE)&&( a<=END_FIRST_LINE)) //Estoy en la primer linea?
#define SecondLine(a) (( a>=BEGIN_SECOND_LINE)&&( a<=END_SECOND_LINE)) //Estoy en la segunda linea?
#define DDRAM_ADRESS 0x80		//Comando para setear DDRAM
#define OFFSET_SECOND_LINE 0x30	//Distancia entre primer y segunda linea
#define ERROR_POS -1 //Valor de error para posiciones

HitachiLCD::HitachiLCD()
{
	//cadd = 1;
	cadd = 0;
	const char * displayname = "EDA LCD 2 B";
	if (!lcdInit(displayname, handler))
	{
		printf("ERROR");
		init_ok = false;
		return;
	}
	init_ok = true;
	status = FT_OK;
	lcdWriteByte(handler, 0x0F, RS_INST);		//tratar de hacer un define de 0xf0(display on)
	//lcdUpdateCursor();


	//lcdWriteByte(handler, 'A', RS_DATA);
}
HitachiLCD::~HitachiLCD()
{
	FT_Close(handler);

}
bool HitachiLCD::lcdInitOk()
{
	return init_ok;
}

FT_STATUS HitachiLCD::lcdGetError()
{
	return status;
}

bool HitachiLCD::lcdClear()
{
	cursorPosition pos;
	pos.column = 0;
	pos.row = 0;
	lcdWriteByte(handler, LCD_CLEAR_DISPLAY, RS_INST);
	lcdSetCursorPosition(pos);
	return true;
}

bool HitachiLCD::lcdClearToEOL()
{
	for (int i = (cadd % (MAX_COL + 1)); i <= (MAX_COL + 1); i++)
	{
		*this << ' ';
		//lcdWriteByte(handler, ' ', RS_DATA);
	}
	lcdUpdateCursor();
	return true;
}

basicLCD& HitachiLCD::operator<<(const unsigned char c)
{
	lcdWriteByte(handler, c, RS_DATA);
	lcdMoveCursorRight();
	return *this;

}

basicLCD& HitachiLCD::operator<<(const unsigned char * c)
{
	//Aca hay que considerar algunas cosas (borrar display o sobreescritura).
	//Si no se discute esto el lunes, preguntar a Richi cuando se vea este mensaje.
	const char * str =(const char *) c;
	int len = strlen(str);
	if (len > 32)
	{
		int beg = len - 32;
		for (int i = beg; i <= len; i++)
		{
			*this << c[i];
			//lcdWriteByte(handler, c[i], RS_DATA);
		}
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			*this << c[i];
			//lcdWriteByte(handler, c[i], RS_DATA);
		}
	}
	return *this;
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
		newPos.column = cadd - (MAX_COL+1);//Diferencia entre cursor y cadd
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
		newPos.column = cadd-1;//Diferencia entre cursor y cadd 
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
			newPos.column = cadd;//NO es necesario hacer +1!
		}
		else if (cadd == END_FIRST_LINE) //Estoy en la primer linea al final
		{
			newPos.row = 1;
			newPos.column = 0;
		}
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
			newPos.column = cadd - 2;//Izquierda mas diferencia cursor con cadd
		}
		else if (SecondLine(cadd) && (cadd != BEGIN_SECOND_LINE))
		{
			newPos.row = 1;
			newPos.column = cadd - MAX_COL -1;//Escritura para mejor entendimiento
		}
		else if (cadd == BEGIN_SECOND_LINE)
		{
			newPos.row = 0;
			newPos.column = END_FIRST_LINE-1;//Diferencia entre cursor y cadd
		}
		return(lcdSetCursorPosition(newPos));
	}
	else return false;//Estoy al principio
}

bool
HitachiLCD::lcdSetCursorPosition(const cursorPosition pos)
{
	if (pos.column <= (MAX_COL-1) && pos.column >= (MIN_COL-1) && pos.row <= MAX_ROW && pos.row >= MIN_ROW)
	{
		cadd = (pos.column+1) + MAX_COL * pos.row;
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
		currPos.column = cadd-1;
	}
	else if (SecondLine(cadd))
	{
		currPos.row = 1;
		currPos.column = cadd - (MAX_COL+1);
	}
	else //No deberia entrar aca, "el que avisa no traiciona"
	{
		currPos.column = ERROR_POS;
		currPos.row = ERROR_POS;
		std::cout << "Error Pos" << std::endl;
	}
	return currPos;
}

void
HitachiLCD::lcdUpdateCursor()
{
	unsigned char cadd_ = cadd-1; //Copia para envio

	if (SecondLine(cadd))
		cadd_ += OFFSET_SECOND_LINE;

	lcdWriteByte(handler,DDRAM_ADRESS | cadd_, RS_INST);
}