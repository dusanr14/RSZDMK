/**
* @file main.c
* @brief Aplikacija koja ispisuje broj unesen preko serijskog ulaza
* @author Dusan Radisic
* @date 15-5-2021
* @version 1.0
*/


#include <stdint.h>
#include <util\delay.h>
#include <stdlib.h>
#include "../usart/usart.h"

int main()
{
	///Promenljiva koja sluzi za skladistenje tekstualnog podatka
	int8_t str[64];
	///Promenljiva koja predstavlja borj
	int16_t number;
	///Inicijalizacija serijske komunikacije
	usartInit(9600);
	while(1)
	{
		usartPutString("Unesi broj: \r\n");
		while(!usartAvailable())
			;
		_delay_ms(100);

		number= usartParseInt();

		sprintf(str, "%d\0",number);
		usartPutString("Uneli ste broj = ");
		usartPutString(str);
		usartPutString("\r\n");
	}

	return 0;
}

