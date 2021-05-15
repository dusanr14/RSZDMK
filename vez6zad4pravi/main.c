/**
* @file main.c
* @brief Aplikacija koja implementira konverziju dec u hexdec broj
* @author Dusan Radisic
* @date 15-05-2021
* @version 1.0
*/

#include "../usart/usart.h"
#include "../timer0/timer0.h"

/**
* ConvertToHex - Funkcija koja konvertuje decimalne u heksadecimalne
* brojeve
* @param *s - string u okviru kog cemo da smestamo heksadecimalne cifre
* milisekundama
* @param *num - broj koji zelimo da konvertujemo
* @return - nema povratnu vrednost
*/
void ConvertToHex(int8_t *s, uint16_t num)
{
	/// Promenljiva koja uzima vrednost parametra num
	uint16_t temp = num;

	///Promenljiva koja sluzi kao iterator
	uint8_t index = 0;

	while (temp > 0)
	{
		if(temp % 16 < 10)
			s[index] = temp % 16 + '0';
		else
			s[index]=(temp % 16 - 10) + 'A';
		temp = temp / 16;
		index++;
	}

	for(int8_t i = 0; i< index/2; i++)
	{
		s[i] ^= s[index - 1 - i];
		s[index -1 -i] ^= s[i];
		s[i] ^= s[index - 1 - i];
	}

	s[index] = '\0';
}

int main()
{
	/// Promenljiva koja sluzi za upis stringa
	int8_t str[64];

	///Promenljiva koja predstavlja decimalni broj
	int16_t decimal_number;

	//Inicijalizacija serijske komunikacije i rada sa bibliotekom timer0
	usartInit(9600);
	timer0InteruptInit();

	while(1)
	{
		usartPutString(" Unesi broj: \r\n");
		while(!usartAvailable())
			;
		timer0DelayMs(100);
		decimal_number=usartParseInt();
		//sprintf(str, "%x\0", decimal_number);
		ConvertToHex(str, decimal_number);
		usartPutString("Konvertovan broj iznosi = ");
		usartPutString(str);
		usartPutString("\r\n");
	}

	return 0;
}
