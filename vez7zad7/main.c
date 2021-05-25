/**
 * @file main.c
 * @brief Zadatak 7, vezbe 7
 * @author Anja Tanovic
 * @version 2.0
 */

#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "../usart/usart.h"

/**
 * Opcija1- Funkcija koja pronalazi slovo koje se najvise ponavlja
 * @return - Vraca slovo koje se najvise ponavlja
 */
int8_t Opcija1(int8_t string[], uint8_t duzina);

/**
 * Opcija2- Funkcija koja uklanja sve ‘ ’ karaktere
 * @return - Nema povratnu vrednost
 */
void Opcija2(int8_t string[], uint8_t duzina, int8_t novi_string[]);

/**
 * Opcija3- Funkcija koja uklanja sve duple karaktere
 * @return - Nema povratnu vrednost
 */
void Opcija3(int8_t string[], uint8_t duzina, int8_t novi_string[]);

/**
 * main - Funkcija koja implementira glavnu funkciju programa
 * @return - nema povratnu vrednost
 */
int main()
{
	usartInit(9600);

	int8_t tmp[50];
	int8_t string[64];
	uint8_t duzina;
	int8_t opcija;

	while (1)
	{
		usartPutString_P(PSTR("Unesite string:\r\n\0"));

		while (usartAvailable() == 0)
		;
		_delay_ms(100);

		duzina = usartGetString(string);
		string[duzina] = '\0';

		do
		{
			usartPutString_P(PSTR("Izaberite opciju za modifikaciju unetog stringa:\r\n\0"));
			usartPutString_P(PSTR("1. Slovo koje se najvise ponavlja?\r\n\0"));
			usartPutString_P(PSTR("2. Ukloni sve ‘ ’ karaktere.\r\n\0"));
			usartPutString_P(PSTR("3. Ukloni sve duplikate karaktera.\r\n\0"));

			while (usartAvailable() == 0)
				;
			_delay_ms(100);
			opcija = usartGetChar();
		} while (opcija != '1' && opcija != '2' && opcija != '3');

		int8_t slovo;
		int8_t novi_string[duzina];

		switch (opcija)
		{
			case '1':
				slovo = Opcija1(string, duzina);
				sprintf(tmp, "Najcesce se pojavljuje slovo: %c\r\n\r\n\0", slovo);
				usartPutString(tmp);
				break;
			case '2':
				Opcija2(string, duzina, novi_string);
				break;
			case '3':
				Opcija3(string, duzina, novi_string);
				usartPutString(novi_string);
				usartPutString("\r\n\r\n\0");
				break;
			default:
				break;
		}



	}

	return 0;
}

/******************************************************************************************/

int8_t Opcija1(int8_t string[], uint8_t duzina)
{
	uint8_t ascii[123]; //niz koji ima clanove od 0 do z iz ascii tabele (posto je uint inicijalizovani su na 0 svi
	for (uint8_t i = 0; i < 123; i++)
		ascii[i] = 0;

	for (uint8_t i = 0; i < duzina; i++)
	{
		for (uint8_t j = 0; j < 123; j++)
		{
			if (string[i] == j)
			{
				ascii[j]++;
			}
		}
	}

	//sad se u nizu ascii nalaze clanovi koji su prebrojali karaktere unutar stringa

	int8_t max = ascii[0];
	int8_t slovo = 0;
	for (uint8_t i = 1; i < 123; i++)
	{
		if (ascii[i] > max)
		{
			max = ascii[i];
			slovo = i;
		}
	}

	return slovo;
}

/******************************************************************************************/

void Opcija2(int8_t string[], uint8_t duzina, int8_t novi_string[])
{
	int8_t tmp[5];
	usartPutString("Novi string je: \0");

	for (uint8_t i = 0; i < duzina; i++)
	{
		if (string[i] != ' ')
		{
			novi_string[i] = string[i];
			usartPutChar(string[i]);
		}
		else
			novi_string[i] = 0;
	}
	usartPutString("\r\n\r\n\0");

	//novi string ovde konkretno nije ni potreban
}

/******************************************************************************************/

void Opcija3(int8_t string[], uint8_t duzina, int8_t novi_string[])
{
	int8_t ascii[123];  //kao check niz
	uint8_t nova_duzina = 0;

	for(uint8_t i = 0; i < 123; i++)
	{
		ascii[i] = 0;
	}

	for (uint8_t i = 0; i < duzina; i++)
	{
		if (ascii[string[i]] == 0)
		{
			ascii[string[i]]++;
			novi_string[nova_duzina] = string[i];
			nova_duzina++;
		}
	}
	novi_string[nova_duzina] = 0;
}
