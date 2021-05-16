/**
* @file main.c
* @brief Aplikacija koja racuna zbir cifara u broju
* @author Dusan Radisic
* @date 16-05-2021
* @version 1.0
*/

#include <stdint.h>
#include <util/delay.h>
#include "../usart/usart.h"
#include "../timer0/timer0.h"

int16_t saberiCifre(int16_t broj)
{
	int16_t suma = 0;
	int8_t ostatak = 0;
	int16_t pomocna = broj;

	while (pomocna != 0)
	{
		ostatak = pomocna % 10;
		suma += ostatak;
		pomocna = pomocna / 10;
	}

	return suma;
}

int main()
{
	usartInit(9600);
	char tmp[50];
	int16_t broj;
	int16_t suma_cifara = 0;

	while(1)
	{
		sprintf(tmp, "Unesite ceo broj\r\n\0");
		usartPutString(tmp);

		while(usartAvailable() == 0)
		;
		_delay_ms(100);
		broj = usartParseInt();

		suma_cifara = saberiCifre(broj);

		sprintf(tmp, "Suma cifara je %d.\r\n\r\n\0", suma_cifara);
		usartPutString(tmp);

	}

	return 0;
	return 0;
}
