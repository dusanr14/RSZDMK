/**
* @file main.c
* @brief Aplikacija
* @author Dusan Radisic
* @date 16-05-2021
* @version 1.0
*/

#include<stdint.h>
#include <avr/pgmspace.h>

#include "../usart/usart.h"
#include "../timer0/timer0.h"

#define BR_KORISNIKA 10

const int8_t  korisnici[BR_KORISNIKA][32] = {
		"Marko Markovic",
		"Janko Jankovic",
		"MIlica Milicevic",
		"Aleksa Aleksic",
		"Novak Novakovic",
		"Marija Maric",
		"Lazar Lazic",
		"Jovan Jovic",
		"Milan Milic",
		"Bane Banovic"
};

const int8_t PIN[BR_KORISNIKA][4] =
{
		"1233",
		"2232",
		"1111",
		"1234",
		"2222",
		"3333",
		"4444",
		"5555",
		"6666",
		"7777"
};

int main()
{
	///indikator da li je ime dobro uneto
	int8_t indikator=0;

	int8_t indikator_pina=1;

	///redni broj korisnika
	int8_t broj=-1;


	int16_t unesen_pin;
	int8_t unesen_pin_string[4];

	///ime koje se unosi
	int8_t ime[64];

	////duzina stringa imena koji se unosi
	uint8_t duzina;

	timer0InteruptInit();
	usartInit(9600);

	while(1)
	{
		//unos korisnickog imena
		usartPutString("\r\n");
		usartPutString("Korisnisko ime: ");

		while(!usartAvailable())
			;
		timer0DelayMs(100);
		duzina = usartGetString(ime);
		ime[duzina]='\0';


		//Provera da li je ime dobro uneto
		for(int8_t i=0; i < 10 ; i++)
		{
			indikator=1;
			for(int8_t j=0; j<duzina; j++ )
			{
				if(ime[j] !=  korisnici[i][j])
				{
					indikator=0;
				}
			}

			if(indikator == 1)
			{
				broj = i; //pamcenje rednog broja
				break;

			}
		}

		if(indikator == 0)
		{
			usartPutString("\r\n");
			usartPutString("Korisnika nema u tabeli.");
		}
		else{

			usartPutString("\r\n");
			usartPutString("Korisnika IMA u tabeli.");

			///unosenje pin-a
			usartPutString("\r\n");
			usartPutString("Unesi pin: ");

			while(!usartAvailable())
						;
			timer0DelayMs(100);
			unesen_pin = usartParseInt();
			sprintf(unesen_pin_string, "%d\0",unesen_pin);

			usartPutString("\r\n");
			usartPutString(unesen_pin_string);

			///indikator da li pin dobro unesen
			indikator_pina = 1;


			for(int8_t i = 0; i < 3 ; i++)
				{
					if(unesen_pin_string[i] != PIN[broj][i])
					{
						indikator_pina = 0;
						break;
					}
				}

				if(indikator_pina == 1)
				{
					usartPutString("\r\n");
					usartPutString("Ispravno unet pin. ");
					usartPutString("\r\n");
				}
				else{
						usartPutString("\r\n");
						usartPutString("Neispravno unet pin. ");
						usartPutString("\r\n");
				}
			}


	}


	return 0;
}
