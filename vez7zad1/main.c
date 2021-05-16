/**
* @file main.c
* @brief Aplikacija koja omogucava logovanje pomocu
* korisnickog imena i lozinke
* @author Dusan Radisic
* @date 15-05-2021
* @version 1.0
*/

#include <stdint.h>
#include <stdlib.h>

#include "../usart/usart.h"
#include "../timer0/timer0.h"

#define DUZINA1 10
#define DUZINA2 11

int8_t provera(int8_t string1[],int8_t string2[], int8_t duzina,int8_t DUZINA)
{

	///indikator da li su stringovi isti (1) ili razliciti (2)
	int8_t indikator = 1;

	if(duzina != DUZINA)
		return 0;


	for(int8_t i = 0; i < duzina; i++ )
	{
		if(string1[i] != string2[i])
		{

		}
	}
	return 1;
}
int main()
{
	usartInit(9600);
	timer0InteruptInit();

	int8_t username_p[DUZINA1]= "dusanr1999";
	int8_t username[64];
	int8_t duzina1;
	int8_t password_p[DUZINA2]="password123";
	int8_t password[64];
	int8_t duzina2;

	while(1)
	{
		//Unosenje korisniskog imena
		usartPutString("\r\n");
		usartPutString(" Unesite korisnicko ime: ");
		while(!usartAvailable())
			;
		timer0DelayMs(100);
		duzina1=usartGetString(username);
		username[duzina1] = '\0';
		usartPutString("\r\n");

		//unosenje sifre
		usartPutString("Unesite sifru: ");
		while(!usartAvailable())
			;
		timer0DelayMs(100);
		duzina2 = usartGetString(password);
		password[duzina2] = '\0';
		usartPutString("\r\n");

			if(provera(username, username_p, duzina1,DUZINA1) &&
					provera(password, password_p, duzina2,DUZINA2) )
			{
				usartPutString(" Dobrodosao, ");
		        usartPutString(username);
		        usartPutString("\r\n");
		        timer0DelayMs(5000);
			}
			else
			{
				usartPutString(" Neispravan unos ");
				usartPutString("\r\n");
				timer0DelayMs(5000);
			}


	}

	return 0;
}
