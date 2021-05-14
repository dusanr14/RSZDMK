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
	int8_t string1[64];
	int8_t string2[64];
	usartInit(9600);
	while(1)
	{
		while(!usartAvailable())
			;
		usartGetString(string1);
			for(int i=0;i<=63;i++)
			{
				string2[i]=string1[i]+32;
			}
			usartPutString(string2);

		}


		return 0;
	}


