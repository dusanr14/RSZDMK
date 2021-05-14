#include <util/delay.h>
#include "../usart/usart.h"

int main()
{
	int8_t str[64];
	usartInit(9600);

	while(1)
	{
		usartPutString("Unesite svoje ime i prezime: \r\n");
		while(!usartAvailable())
			;

		_delay_ms(100);

		usartGetString(str);

		usartPutString("Zdravo, ");
		usartPutString(str);
		usartPutString(":) \r\n");
	}
}
