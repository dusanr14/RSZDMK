/**
* @file main.c
* @brief Aplikacija
* @author Dusan Radisic
* @date 16-05-2021
* @version 1.0
*/

#include <stdint.h>
#include <stdlib.h>
#include<util/delay.h>
#include <avr/pgmspace.h>
#include "../timer0/timer0.h"
#include "../usart/usart.h"

#define BR_KORISNIKA 4

 int8_t  korisnici[BR_KORISNIKA][32] = {
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

int8_t duzine[BR_KORISNIKA]=
{
		11,23,13,11
};

int8_t pinovi[BR_KORISNIKA][4]=
{
		"1111","2222","3333","4444"
};

int main()
{
	timer0InteruptInit();
	usartInit(9600);
	int8_t tmp[50];
	int8_t korisnicko_ime[32];
	int8_t pin[10];
	uint8_t duzina;
	uint8_t poklapanje;
	uint8_t pronadjeno;

	while(1)
	{
		sprintf(tmp, "Unesite ime i prezime: \r\n\0");
		usartPutString(tmp);
		while(!usartAvailable())
			;
		_delay_ms(100);

		duzina=usartGetString(korisnicko_ime);
		pronadjeno = 0;
		poklapanje = 1;
		int8_t broj_korisnika;
		for(uint8_t i = 0; i < BR_KORISNIKA; i++)
		{
			if(duzina != duzine[i])
				poklapanje = 0;
			else
				poklapanje = 1;

			for(uint8_t j = 0; j < duzina ; j++)
			{
				if(korisnicko_ime[j] != korisnici[i][j])
				{
					poklapanje = 0;
					break;
				}
			}

			if(poklapanje == 1)
			{
				pronadjeno = 1;
				broj_korisnika = i;
				break;
			}
		}

		if(pronadjeno)
		{
			sprintf(tmp,"Unesite pin: \r\n\0");
			usartPutString(tmp);
			while(!usartAvailable())
				;
			_delay_ms(100);
			uint8_t duzina_pina = usartGetString(pin);
			pin[duzina_pina] = 0;
			if(duzina_pina != 4)
			{
				usartPutString("Pogresno unet pin. \r\n\r\n\0");
			}
			else
			{
				int8_t tacan_unos = 1;
				for(uint8_t j= 0; j<4 ; j++)
				{
					if(pin[j]!= pinovi[broj_korisnika][j])
					{
						tacan_unos=0;
						break;
					}
				}

		if(tacan_unos)
		{
			usartPutString_P(PSTR("Dobro unet pin, DOBRODOSAO! \r\n\r\n\0"));
		}
		else
		{
			int8_t tacan_unos = 1;

			          for(uint8_t j = 0; j < 4; j++)
				         {
					       if(pin[j] != pinovi[broj_korisnika][j])
					      {
						   tacan_unos=0;
						   break;
					      }
				        }
			      if(tacan_unos)
			      {
				      usartPutString_P(PSTR("dOBRO UNET PIN. dOBRODOSAO \r\n\r\n\0"));
			      }
			else
			{
				usartPutString("Pogresno unet pin \r\n\r\n\0");
			}
		}

		    _delay_ms(1000);
	      }
		}
	}
	return 0;

}
