/*
 * main.c
 *
 *  Created on: May 25, 2021
 *      Author: Dusan
 */


#include "pls7.h"

int main()
{
init();
	while(1)
	{
		writeDisplay(LEDS, readSwitches());
		if (buttonState(LEFT))
			writeDisplay(D1, 0x0c);
		else
			writeDisplay(D1, 0xfe);
		if (buttonState(DOWN))
			writeDisplay(D2, 0xa4);
		else
			writeDisplay(D2, 0xfe);
		if (buttonState(RIGHT))
	writeDisplay(D3, 0x27);
		else
			writeDisplay(D3, 0xfe);
		if (buttonState(UP))
			writeDisplay(D4, 0xc4);
		else
			writeDisplay(D4, 0xfe);
	}
	return 0;
}
