#include "pulsing.h"

/// Makro za podesavanje visoke vrednosti signala na pinu
#define HIGH 1
/// Makro za podesavanje niske vrednosti signala na pinu
#define LOW 0

void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions)
{
	unsigned char i;

	// Implementacija num_of_repetitions perioda
	for (i = 0; i < num_of_repetitions; i++)
		pinPulse(port, pin, period);
}

/******************************************************************************************/

void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
    // Poluperioda u kojoj pin ima visoku vrednost
    pinSetValue(port, pin, HIGH);
    timer0DelayMs(calculateHalfPeriod(period));

    // Poluperioda u kojoj pin ima nisku vrednost
    pinSetValue(port, pin, LOW);
    timer0DelayMs(calculateHalfPeriod(period));
}
