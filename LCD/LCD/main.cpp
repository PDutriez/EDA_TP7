#include <Windows.h>
#include "fase1.h"
#include <stdio.h>
#include "HitachiLCD.h"
#include <iostream>

int main(void)
{
	HitachiLCD lcd;
	//FT_HANDLE handle;
	const char * displayname = "EDA LCD 2 B";
	//lcdInit(displayname, handle);
	const unsigned char text1[] = "El LCD funciona!";
	const unsigned char text2[] = "Como ruedan las ruedas del ferrocarril";
	const unsigned char text3[] = "habia una vez un ...";
	const unsigned char char1[] = "princeso";
	const unsigned char char2[] = "caballero";
	const unsigned char* chars[3] = { char1,char2 };
	const unsigned char text4[] = "Eso es todo     amigos !!!";
	cursorPosition pos;

	std::cout << "Start Test" << std::endl;
//Palabra de prueba (corta)
	lcd << text1;
	std::cout << "Press enter to continue"<<std::endl;
//Reinicio cursor position + limpieza
	getchar();
	lcd.lcdClear();
//Palabra mayor a 32 caracteres
	lcd << text2;
	std::cout << "Press enter to continue" << std::endl;
//Limpiamos todo
	getchar();
	lcd.lcdClear();
	lcd << text3;
	for (int i = 0; i < 2; ++i)
	{
		std::cout << "Press enter to continue" << std::endl;
		getchar();
		pos.column = 0;
		pos.row = 1;
		lcd.lcdSetCursorPosition(pos); //no funciona
		lcd.lcdClearToEOL();
		lcd << chars[i];
	}


	std::cout << "Press enter to continue" << std::endl;
	getchar();
	lcd.lcdClear();
	lcd << text4;
	std::cout << "Test ended" << std::endl;

}
