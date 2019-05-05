#include <Windows.h>
#include "fase1.h"
#include <stdio.h>

int main(void)
{
	FT_HANDLE handle;
	const char * displayname = "EDA LCD 2 B";
	lcdInit(displayname, handle);
	const char text[] = "Phil, funciona!AAAA";
	
	lcdWriteByte(handle, 0x0F, RS_INST);
	for (int i = 0; i < 15; i++)
	{
		lcdWriteByte(handle, text[i], RS_DATA);
	}
	getchar();
	for (int i = 0; i < (5*8-15); i++)
	{
		lcdWriteByte(handle, 0x14, RS_INST);
	}
	getchar();
	for (int i = 15; i<19; i++)
	{
		lcdWriteByte(handle, text[i], RS_DATA);
	}
	printf("press enter\n");
	getchar();
	FT_Close(handle);
}
