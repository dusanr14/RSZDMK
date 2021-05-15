/**
* @file main.c
* @brief Opis datoteke
* @author Dusan Radisic
* @date 5-4-2021
* @version 1.0
*/
#include <util/delay.h>
#include <stdint.h>
#include "../usart/usart.h"


int main()
{
	uint8_t duzina;
	///Promenljiva koja sluzi sa skladistenje stirng
	int8_t string1[64];
	///Promenljiva u koju se skladisti uvelican string
	int8_t string2[64];

	///Postavljanje baud-rate-a na  9600
	usartInit(9600);

	while(1)
	{
		usartPutString("Unesi rec: \r\n");
		while(!usartAvailable())
			;
		    _delay_ms(100);
		    duzina = usartGetString(string1);
		    string1[duzina]='\0';

			for(int8_t i=0;i<duzina;i++)
			{
				string2[i]=string1[i]-32;
			}
			string2[duzina]=0;

			usartPutString(string2);
			usartPutString("\r\n");


	}


		return 0;
	}


