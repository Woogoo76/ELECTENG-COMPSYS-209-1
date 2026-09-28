/*
 * GccApplication1.c
 *
 * Created: 28/09/2026 6:01:05 pm
 * Author : wilsc
 */ 


#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"

static volatile uint16_t counter = 0;

void timer0_init(void) {
	TCCR0A = (1 << WGM01);              // CTC Mode
	TCCR0B = (1 << CS02) | (1 << CS00); // 1024 Prescaler
	OCR0A = 155;                        // ~10ms interrupt period
	TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	send_next_character_to_display();
}

int main(void) {
	init_display();
	timer0_init();
	sei();

	while (1) {
		seperate_and_load_characters(counter, 0xFF);

		_delay_ms(400);

		counter++;
		if (counter > 9999) {
			counter = 0;
		}
	}

	return 0;
}