/*
 * GccApplication1.c
 *
 * Created: 17/09/2026 4:08:07 PM
 * Author : wsco929
 */ 

#include <avr/io.h>
#define F_CPU 2000000UL
#include <util/delay.h>


#define TOGGLE_LED PORTB ^= (1 << PB5)

int main(void)
{
	DDRB = 0xFF; //maybe dont need to include
	DDRC = 0;
	DDRD = 0;
	
    /* Replace with your application code */
    while (1) 
    {
		TOGGLE_LED;
		_delay_ms(375);
		TOGGLE_LED;
		_delay_ms(125);
    }
}


