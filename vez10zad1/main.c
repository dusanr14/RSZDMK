/**
* @file main.c
* @brief Aplikacija
* @author Dusan Radisic
* @date 16-05-2021
* @version 1.0
*/

#include<stdint.h>

#include "../usart/usart.h"
#include "../timer0/timer0.h"
#include "../pin_driver/pin.h"

int main()
{
	timer0InteruptInit();
	usartInit(9600);
	pinInit(PORT_B, 5 ,OUTPUT);
	int8_t c;
	enum state_t {LOCKED, NUM1, NUM2, UNLOCKED, BROKEN, REC2, REC1};
	enum state_t state = LOCKED;
	while(1)
	{
		usartPutString("Napisi!!!\r\n");
		while(!usartAvailable())
			;
		c = usartGetChar();
		switch(state)
		{
		case LOCKED:

			if(c == '1')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				state = NUM1;
				usartPutString("LOCKED -> NUM1\r\n");
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
				usartPutString("LOCKED -> BROKEN\r\n");
			}
			break;

		case NUM1:

			if(c == '2')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				state = NUM2;
				usartPutString("NUM1 -> NUM2\r\n");
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
			}
			break;
		case NUM2:

			if(c == '3')
			{
				for(int8_t i = 0; i < 3; i++)
				{
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(1000);
				}
				state = UNLOCKED;
				usartPutString("NUM2 -> UNLOCKED\r\n");
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
				usartPutString("NUM2 -> BROKEN\r\n");
			}
				break;

		case UNLOCKED:
			state = UNLOCKED;
			usartPutString("UNLOCKED -> UNLOCKED\r\n");
			break;
		case BROKEN:
			if(c == '7')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				state = REC1;
				usartPutString("BROKEN -> REC1\r\n");
			}
			else
			{
				for(int8_t i = 0; i < 2; i++)
				{
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(1000);
				}
				state = BROKEN;
				usartPutString("BROKEN -> BROKEN\r\n");
			}
			break;
		case REC1:
			if (c == '8')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				state = REC2;
				usartPutString("REC1 -> REC2\r\n");
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(1000);
				state = BROKEN;
				usartPutString("REC1 -> BROKEN\r\n");
			}
			break;
		case REC2:
			if(c == '9')
			{
				pinSetValue(PORT_B, 5, LOW);
				state = LOCKED;
				usartPutString("REC2 -> LOCKED\r\n");
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(1000);
				state = BROKEN;
				usartPutString("REC2 -> BROKEN\r\n");
			}
			break;
		}
	}

	return 0;
}
