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

#define DS1_PIN PB0
#define DS2_PIN PB1
#define SG_PIN  PB4
#define PB_PIN  PB7

const uint8_t seg_pattern[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static volatile uint8_t counter = 0;
static volatile uint8_t active_digit = 0;

void init_io(void) {
	DDRC |= 0x3F;
	DDRB |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << SG_PIN);
	DDRB &= ~(1 << PB_PIN);
	PORTB |= (1 << PB_PIN);
	
	PORTB |= (1 << DS1_PIN) | (1 << DS2_PIN);
}

void timer0_init(void) {
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02) | (1 << CS00);
	OCR0A = 155;
	TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	uint8_t digit_val = (active_digit == 0) ? (counter / 10) : (counter % 10);
	uint8_t pattern = seg_pattern[digit_val];

	PORTB |= (1 << DS1_PIN) | (1 << DS2_PIN);

	PORTC = (PORTC & 0xC0) | (pattern & 0x3F);
	if (pattern & (1 << 6)) {
		PORTB |= (1 << SG_PIN);
		} else {
		PORTB &= ~(1 << SG_PIN);
	}

	if (active_digit == 0) {
		PORTB &= ~(1 << DS1_PIN);
		active_digit = 1;
		} else {
		PORTB &= ~(1 << DS2_PIN);
		active_digit = 0;
	}
}

int main(void) {
	init_io();
	timer0_init();
	sei();

	while (1) {
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
			if (counter > 99) {
				counter = 0;
			}
		}
	}

	return 0;
}