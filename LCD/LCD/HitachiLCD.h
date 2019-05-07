#pragma once
#include "BasicLCD.h"

class HitachiLCD :public basicLCD
{
public:
	HitachiLCD();
	~HitachiLCD();
	/*=====================================================
	* Name: lcdInitOk
	* Entra: -
	* Resulta: No genera ningún cambio en el display.
	* Devuelve en su nombre “true” si el display se inicializó
	* correctamente (el constructor no tuvo errores) o “false
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdInitOk();
	/*=====================================================
	* Name: lcdGetError
	* Entra: -
	* Resulta: No genera ningún cambio en el display.
	* Devuelve en su nombre FT_OK si no existe ningún error.
	* Caso contrario devuelve en su nombre el error que se
	* haya producido trabajando con la librería ftd2xx
	*=====================================================*/
	virtual FT_STATUS lcdGetError();
	/*=====================================================
	* Name: lcdClear
	* Entra: -
	* Resulta: Borra el display y el cursor va a HOME
	* cadd =1
	* Devuelve en su nombre “true” si fue satisfactoria “false”
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdClear();
	/*=====================================================
	* Name: lcdClearToEOL
	* Entra: -
	* Resulta: Borra el display desde la posición actual
	* del cursor hasta el final de la línea.
	* cadd = No se altera
	* Devuelve en su nombre “true” si fue satisfactoria “false”
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdClearToEOL();
	/*=====================================================
	* Name: operator<<()
	* Entra: Un carácter
	* Resulta: Pone el carácter en la posición actual
	* del cursor del display y avanza el cursor a la próxima
	* posición respetando el gap (si el carácter no es imprimible
	* lo ignora)
	* Modifica: (cadd)
	* Devuelve en su nombre una referencia a un basicLCD que permite
	* encascar la función:
	* basicLCD lcd;
	* lcd << ‘a’ << ‘b’ << ‘c’;
	*=====================================================*/
	virtual basicLCD& operator<<(const unsigned char c);
	/*=====================================================
	* Name: operator<<()
	* Entra: Una cadena de caracteres NULL terminated
	* Resulta: imprime la cadena de caracteres en la posición actual
	* del cursor y avanza el cursor al final de la cadena respetando
	* el gap (si algún carácter no es imprimible lo ignora). Si recibe una
	* cadena de más de 32 caracteres, MUESTRA TODO.
	* NOTA ALUMNOS:
	* Entre los integrantes del grupo se decidio que la mejor forma de imprimir
	*	la cadena de caracteres es ir imprimiendolos hasta que se ocupe todo el diplay,
	*	borrar el diplay e imprimir el resto.
	*	Ej. lcd<< "Como ruedan las ruedas del ferrocarril".
	*	lcd:	|C|o|m|o| |r|u|e|d|a|n| |l|a|s| |
	*			|r|u|e|d|a|s| |d|e|l| |f|e|r|r|o|
	*
	*			|c|a|r|r|i|l| | | | | | | | | | |
	*			| | | | | | | | | | | | | | | | |
	*
	*
	* Modifica: (cadd)
	* Devuelve en su nombre una referencia a un basicLCD que permite
	* encascar la función:
	* basicLCD lcd;
	* lcd << “Hola” << “ “ << “Mundo”;
	*=====================================================*/
	virtual basicLCD& operator<<(const unsigned char * c);
	/*=====================================================
	* Name: lcdMoveCursorUp
	*
	* Entra: -
	* Resulta: Pasa el cursor a la primera línea del display sin
	* alterar la columna en la que estaba.
	* Modifica: (cadd)
	* Devuelve en su nombre “true” si fue satisfactoria “false”
	* en caso contrario.
	*=====================================================*/

	/*Phil*/
	virtual bool lcdMoveCursorUp();
	/*=====================================================
	* Name: lcdMoveCursorDown
	*
	* Entra: -
	* Resulta: Pasa el cursor a la segunda línea del display sin
	* alterar la columna en la que estaba.
	* Modifica: (cadd).
	* Devuelve en su nombre “true” si fue satisfactoria “false”
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdMoveCursorDown();
	/*=====================================================
	* Name: lcdMoveCursorRight
	*
	* Entra: -
	* Resulta: Avanza el cursor una posición
	* Modifica: (cadd).
	* Devuelve en su nombre “true” si fue satisfactoria “false”
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdMoveCursorRight();
	/*=====================================================
	* Name: lcdMoveCursorLeft
	*
	* Entra: -
	* Resulta: Retrocede el cursor una posición
	* Modifica: (cadd).
	* Devuelve en su nombre “true” si fue satisfactoria “false”
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdMoveCursorLeft();
	/*=====================================================
	* Name: lcdSetCursorPosition
	* Entra: Recibe una estructura tipo cursorPosition
	* Resulta: Posiciona el cursor en la posición dada
	* por row y column. row[0-1] col[0-15]. Ante un valor inválido
	* de row y/o column ignora la instrucción (no hace nada).
	* Modifica: (cadd).
	* Devuelve en su nombre “true” si fue satisfactoria “false”
	* en caso contrario.
	*=====================================================*/
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	/*=====================================================
	* Name: lcdGetCursorPosition
	* Entra: -
	* Resulta: Devuelve la posición actual del cursor.
	* cadd = No se altera
	*
	* Devuelve una estructura tipo cursorPosition
	*=====================================================*/
	virtual cursorPosition lcdGetCursorPosition();

private:
	FT_HANDLE handler;
	FT_STATUS status;
	bool cleardisplay;
	bool init_ok;
	virtual void lcdUpdateCursor();
};