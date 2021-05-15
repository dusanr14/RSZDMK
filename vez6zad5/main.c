/**
 * @file main.c
 * @brief Aplikacija koja racuna upisanu jednacinu
 * @author Dusan Radisic
 * @date 15-5-2021
 * @version 1.0
 */

#include "../timer0/timer0.h"
#include "../usart/usart.h"
#include <stdint.h>
/**
* timer0DelayMs - Funkcija koja implementira pauzu u broju milisekundi koji
je prosledjen
* kao parametar
* @param delay_length - ulaz tipa unsigned long - Duzina pauze u
milisekundama
* @return Povratna vrednost je tipa unsigned long i ima vrednost broja
milisekundi
* proteklih od pocetka aplikacije do trenutka izlaska iz funkcije
*/

int16_t rezultat(int16_t broj1, int16_t broj2, int8_t c)
{
	int16_t rez;
	switch( c )
	{
	case '+':
		rez=broj1+broj2;
		break;
	case '-':
		rez=broj1-broj2;
		break;
	case '*':
		rez=broj1*broj2;
		break;
	case '/':
		rez=broj1/broj2;
		break;
	default:
		rez=-1;
	}
	return rez;
}


int main()
{

	int16_t num1;
	int8_t string_num1[64];
	int16_t num2;
	int8_t string_num2[64];
	int8_t operand;
	int8_t string_resenje[64];

	timer0InteruptInit();
	usartInit(9600);
		while(1)
		{

			usartPutString("Unesi jednacinu: ");
			while(!usartAvailable())
				;
			timer0DelayMs(1000);

			num1 = usartParseInt();
			operand = usartGetChar();
			num2 = usartParseInt();

			sprintf(string_num1, "%d\0", num1);
			sprintf(string_num2, "%d\0", num2);
			sprintf(string_resenje, "%d\0", rezultat( num1, num2, operand));

			usartPutString(string_num1);
			usartPutString(" ");
			usartPutChar(operand);
			usartPutString(" ");
			usartPutString(string_num2);
			usartPutString(" ");
			usartPutString(" = ");
			usartPutString(string_resenje);
			usartPutString("\r\n");
		}

	return 0;
}
