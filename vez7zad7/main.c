/**
* @file main.c
* @brief Aplikacija
* @author Dusan Radisic
* @date 16-05-2021
* @version 1.0
*/

#include<stdint.h>

#include "../usart/usart.h"
#include "../timer0/timer0.h"

int main()
{
	int8_t string[64];
	int16_t duzina;
	timer0InteruptInit();
	usartInit(9600);

	while(1)
	{
		usartPutString("\r\n ")
		usartPutString("Unesite sting: ")
		while(!usartAvailable())
			;
		timer0DelayMs(100);
		duzina=usartGetString(string);
		string[duzina]='\0';
	}

	return 0;
}
