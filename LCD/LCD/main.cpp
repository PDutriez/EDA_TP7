#include <Windows.h>
#include "fase1.h"
#include <stdio.h>

int main(void)
{
	FT_HANDLE handle;
	const char * displayname = "EDA LCD 2 B";
	lcdInit(displayname, handle);
	const char text[] = "Phil, funciona!";
	
	lcdWriteByte(handle, 0x0F, RS_INST);
	for (int i = 0; i < 15; i++)
	{
		lcdWriteByte(handle, text[i], RS_DATA);
	}
	printf("press enter\n");
	getchar();
}
