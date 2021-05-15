/**
* @file main.c
* @brief Aplikacija koja proverava da li je rec palindrom
* @author Dusan Radisic
* @date 14-05-2021
* @version 1.0
*/

#include "../usart/usart.h"
#include <stdint.h>
#include <util/delay.h>

/**
* palindrom - Funkcija koja implementira proveru da li je string palindrom
* odgovarajucom brzinom
* @param string - ulaz tipa int8_t -unesen sa tastature
* @param duzina - duzina stringa u bajtovima
*
* @return indikator - moze da ima vrednosti 0 i 1, ako je 1 string je
* palindrom, ako ne 0, string nije palindrom
*/
int8_t palindrom(int8_t string[64], int8_t duzina)
{
	int8_t indikator;

		for(int8_t i = 0; i < duzina/2; i++)
		{
			if(string[i] != string[duzina-1-i])
			{
				indikator = 0;
			}
			else
			{
				indikator = 1;
			}
		}
	return indikator;
}

int main()
{
	int8_t string1[64];
	uint8_t duzina;
	usartInit(9600);
		while(1)
		{
			while(!usartAvailable())
				;
			_delay_ms(100);
			duzina=usartGetString(string1);
			string1[duzina]='\0';

			usartPutString("''");
			usartPutString(string1);
			usartPutString("''");

			if(palindrom(string1,duzina))
				{
					usartPutString(" jeste ");
				}
				else
				{
					usartPutString(" nije ");
				}

			usartPutString("palindrom.\r\n ");

		}
	return 0;
}
