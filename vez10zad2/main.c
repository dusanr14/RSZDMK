/**
* @file main.c
* @brief Aplikacija koja implementira rad lifta
* @author Dusan Radisic
* @date 23-05-2021
* @version 1.0
*/

#include<stdint.h>

#include "../usart/usart.h"
#include "../timer0/timer0.h"
#include "../pin_driver/pin.h"

void LED_ON()
{
	pinSetValue(PORTB, 5, LOW);
	pinSetValue(PORTB, 5, HIGH);
}

void LED_blink()
{
	pinSetValue(PORTB, 5, LOW);
	timer0DelayMs(500);
	pinSetValue(PORTB, 5, HIGH);
	timer0DelayMs(500);
	pinSetValue(PORTB, 5, LOW);
	timer0DelayMs(500);
}

int main()
{
	timer0InteruptInit();
	usartInit(9600);
	//inicijalizovanje diode kao izlaznog porta
	pinInit(PORT_B, 5 ,OUTPUT);

	int8_t c;
	enum state_t {OF0, OF1, OF2, CF0, CF1, CF2, CF0U, CF1D, CF1U, CF2D};
	enum state_t state = OF0;

	while(1)
	{
		if(state == OF0 || state == OF1 || state == OF2)
		{
			usartPutString("Upisi naredbu:\r\n");
			while(!usartAvailable())
				;
			timer0DelayMs(100);
			c = usartGetChar();
		}

		timer0DelayMs(200);

		switch(state)
		{
		case OF0:
				if(c == 'U')
				{
					state = CF0U;
					LED_blink();

					usartPutString("OF0 -> CF0U\r\n");
				}
				else
				{
					state = OF0;

					usartPutString("OF0 -> OF0\r\n");
				}
			break;
		case OF1:
				if( c == 'D')
				{
					state = CF1D;
					LED_blink();

					usartPutString("OF1 -> CF1D\r\n");
				}
				else if( c == 'U')
				{
					state = CF1U;
					LED_blink();

					usartPutString("OF1 -> CF1U\r\n");
				}
				else
				{
					state = OF1;
					usartPutString("OF1 -> OF1\r\n");
				}
			break;
		case OF2:
				if(c == 'D')
				{
					state = CF2D;
					usartPutString("OF2 -> CF2D\r\n");
				}
				else
				{
					state = OF2;
					usartPutString("OF2 -> OF2\r\n");
				}
			break;
		case CF0:
				state = OF0;
				LED_blink();
				LED_blink();
				LED_blink();
				usartPutString("CF0 -> OF0\r\n");
			break;
		case CF1:
				state = OF1;
				LED_blink();
				LED_blink();
				LED_blink();
				usartPutString("CF1 -> OF1\r\n");
			break;
		case CF2:
			    state = OF2;
			    LED_blink();
			    LED_blink();
			    LED_blink();
			    usartPutString("CF2 -> OF2\r\n");
			break;
		case CF0U:
				state = CF1;
				LED_ON();
				usartPutString("CF0U -> CF1\r\n");
			break;
		case CF1D:
				state = CF0;
				LED_ON();
				usartPutString("CF1D -> CF0\r\n");
			break;
		case CF1U:
				state = CF2;
				LED_ON();
				usartPutString("CF1U -> CF2\r\n");
			break;
		case CF2D:
				state = CF1;
				LED_ON();
				usartPutString("CF2D -> CF1\r\n");
			break;


		}
	}

	return 0;
}
