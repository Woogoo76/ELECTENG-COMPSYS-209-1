/*
 * GccApplication1.c
 *
 * Created: 28/09/2026 6:01:05 pm
 * Author : wilsc
 */ 


#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

// Shift Register Control Pins (PORTC)
#define SH_CP_PIN PC3
#define SH_DS_PIN PC4
#define SH_ST_PIN PC5

// Digit Enable Pins (PORTD)
#define DS1_PIN PD4
#define DS2_PIN PD5
#define DS3_PIN PD6
#define DS4_PIN PD7

const uint8_t seg_pattern[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void init_display(void) {
	// Configure shift register control pins (PC3, PC4, PC5) as outputs
	DDRC |= (1 << SH_CP_PIN) | (1 << SH_DS_PIN) | (1 << SH_ST_PIN);

	// Configure digit enable pins (PD4, PD5, PD6, PD7) as outputs
	DDRD |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << DS3_PIN) | (1 << DS4_PIN);

	// Set Ds1, Ds2, Ds3 = 1 (disabled) and Ds4 = 0 (enabled)
	PORTD |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << DS3_PIN);
	PORTD &= ~(1 << DS4_PIN);
}

void send_next_character_to_display(void) {
	// 1. Ensure SH_CP and SH_ST are both set to 0
	PORTC &= ~((1 << SH_CP_PIN) | (1 << SH_ST_PIN));

	// 2. Get bit pattern for number "7"
	uint8_t pattern = seg_pattern[7];

	// 3. Shift out 8 bits starting with MSB (dp down to a)
	for (int8_t i = 7; i >= 0; i--) {
		if (pattern & (1 << i)) {
			PORTC |= (1 << SH_DS_PIN);
			} else {
			PORTC &= ~(1 << SH_DS_PIN);
		}

		// Toggle SH_CP High then Low to shift bit
		PORTC |= (1 << SH_CP_PIN);
		PORTC &= ~(1 << SH_CP_PIN);
	}

	// 4. Toggle SH_ST High then Low to latch data to outputs
	PORTC |= (1 << SH_ST_PIN);
	PORTC &= ~(1 << SH_ST_PIN);
}

int main(void) {
	init_display();
	send_next_character_to_display();

	while (1) {
		// Hold static display
	}

	return 0;
}