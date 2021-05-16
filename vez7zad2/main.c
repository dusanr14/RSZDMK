/*
 * main.c
 *
 *  Created on: May 16, 2021
 *      Author: Dusan
 */


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



	int16_t broj_samoglasnika = 0;
	int16_t broj_samoglasnika_s[64];
	int8_t string[64];
	int16_t duzina;
	timer0InteruptInit();
	usartInit(9600);

	while(1)
	{
		broj_samoglasnika = 0;

		usartPutString("Unesi rec ");
		usartPutString("\r\n");

		while(!usartAvailable())
			;
		timer0DelayMs(100);
		duzina = usartGetString(string);
		string[duzina] = '\0';

		for(int16_t i = 0; i < duzina; i++)
		{
			if(string[i] == 97 ||
			   string[i] == 101 ||
			   string[i] ==105 ||
			   string[i] ==111 ||
			   string[i] ==117
			   )
			{
				broj_samoglasnika++;
			}

		}

		sprintf(broj_samoglasnika_s, "%d", broj_samoglasnika);
		usartPutString("\r\n");
		usartPutString("Rec ima ");
		usartPutString(broj_samoglasnika_s);
		usartPutString(" samoglasnika ");
		usartPutString("\r\n");


	}

	return 0;
}
