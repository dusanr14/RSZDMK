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
#include "util.h"
#include "pin.h"

/**
* main- Glavna funkcija u aplikaciji
* @return - Povratna vrednost je uvek 0
*/
int main()
{
	int16_t broj_clanova;
	int8_t broj_clanova_s[64];

	uint8_t CLANOVI[broj_clanova];

	timer0InteruptInit();
	usartInit(9600);
	pinInit(PORTD, 13,OUTPUT);

	while(1)
	{
		usartPutString("\r\n ");
		usartPutString("Unesite duzinu niza: ");

		while(!usartAvailable())
			;
		broj_clanova = usartParseInt();
		sprintf(broj_clanova_s,"%d\0",broj_clanova);

		usartPutString("\r\n");
		usartPutString("Unesite elemente niza: ");

		//paljenje diode
		pinSetValue(PORTD, 13, HIGH);

		for(int8_t i = 0; i < broj_clanova; i++)
			{
				CLANOVI[i] = usartParseInt();
			}
			CLANOVI[broj_clanova] = "\0";

			//gasenje diode
			pinSetValue(PORTD, 13, LOW);

		Sort(CLANOVI, broj_clanova, UP);

		usartPutString("\r\n");

		for(int8_t i = 0; i < broj_clanova; i++)
		{
		   usartPutString(CLANOVI[i]);
		   usartPutString(" ");
		}

		if(Check(CLANOVI) == 1)
		{
			usartPutString("\r\n");
			usartPutString("Niz je aritmeticki");
		}
		else
		{
			usartPutString("\r\n");
			usartPutString("Niz nije aritmeticki");
		}

	}

	return 0;
}
