#include "../usart/usart.h"
#include <util\delay.h>
#include <stdint.h>

int main()
{

	int8_t a;
	int8_t str1[64];
	int16_t number1;
	int8_t str2[64];
	int16_t number2;
	int16_t rezultat;
	int8_t str3[64];
	usartInit(9600);
	while(1)
	{
		//Upisivanje prvog broja
		usartPutString("\r\n Unesi prvi broj :");
		while(!usartAvailable())
			;
		_delay_ms(100);
		number1=usartParseInt();
		sprintf(str1, "%d\0",number1);

		//Upisivanje drugog broja
		usartPutString("\r\n");
		usartPutString("Unesi drugi broj :");
		while(!usartAvailable())
				;
		_delay_ms(100);
		number2=usartParseInt();
		sprintf(str2, "%d\0",number2);

		//upis operatora
		usartPutString("\r\n");
		usartPutString("Unesi jedan od operatora : + - * /");
		while(!usartAvailable())
					;
		a=usartGetChar();
		usartPutString(" \r\n ");

		if(a == '+')
		{
		rezultat= number1 + number2;
		sprintf(str3, "%d\0",rezultat);
		}
		else if(a == '-')
		{
		rezultat= number1 - number2;
		sprintf(str3, "%d\0", rezultat);
		}
		else if(a == '*')
		{
			rezultat = number1 * number2;
			sprintf(str3, "%d\0", rezultat);
		}
		else if(a == '/')
		{
			rezultat = number1 / number2;
			sprintf(str3, "%d\0", rezultat);
		}
		else
		{
			usartPutString("Pogresan unos, moras iz pocetka!!! \r\n");
		}

		usartPutString(str1);
		usartPutString(" ");
		usartPutChar(a);
		usartPutString(" ");
		usartPutString(str2);
		usartPutString(" = ");
		usartPutString(str3);
		usartPutString("\r\n");
		a=' ';
	}
	return 0;
}
