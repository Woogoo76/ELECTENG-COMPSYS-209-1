/*
 * GccApplication1.c
 *
 * Created: 28/09/2026 6:01:05 pm
 * Author : wilsc
 */ 


#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DS1_PIN PB0
#define DS2_PIN PB1
#define SG_PIN  PB4
#define PB_PIN  PB7

const uint8_t seg_pattern[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void display_digit(uint8_t digit) {
	if (digit > 9) return;

	uint8_t pattern = seg_pattern[digit];

	PORTC = (PORTC & 0xC0) | (pattern & 0x3F);

	if (pattern & (1 << 6)) {
		PORTB |= (1 << SG_PIN);
		} else {
		PORTB &= ~(1 << SG_PIN);
	}
}

void init_io(void) {
	DDRC |= 0x3F;
	DDRB |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << SG_PIN);
	DDRB &= ~(1 << PB_PIN);
	PORTB |= (1 << PB_PIN);

	PORTB |= (1 << DS1_PIN);
	PORTB &= ~(1 << DS2_PIN);
}

int main(void) {
	init_io();
	uint8_t counter = 0;

	while (1) {
		display_digit(counter);
		uint8_t button_pressed = 0;

		for (uint8_t i = 0; i < 10; i++) {
			_delay_ms(100);
			if (!(PINB & (1 << PB_PIN))) {
				button_pressed = 1;
				break;
			}
		}

		if (button_pressed) {
			counter = 0;
			} else {
			counter++;
			if (counter > 9) {
				counter = 0;
			}
		}
	}

	return 0;
}