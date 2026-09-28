/*
 * display.c
 *
 * Created: 28/09/2026 8:08:13 pm
 *  Author: wilsc
 */ 
#include "display.h"

#define SH_CP_PIN PC3
#define SH_DS_PIN PC4
#define SH_ST_PIN PC5

#define DS1_PIN PD4
#define DS2_PIN PD5
#define DS3_PIN PD6
#define DS4_PIN PD7

const uint8_t seg_pattern[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static volatile uint8_t disp_characters[4] = {0, 0, 0, 0};
static volatile uint8_t disp_position = 0;

void init_display(void) {
	DDRC |= (1 << SH_CP_PIN) | (1 << SH_DS_PIN) | (1 << SH_ST_PIN);
	DDRD |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << DS3_PIN) | (1 << DS4_PIN);

	PORTD |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << DS3_PIN) | (1 << DS4_PIN);
}

void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos) {
	uint8_t d1 = (number / 1000) % 10;
	uint8_t d2 = (number / 100) % 10;
	uint8_t d3 = (number / 10) % 10;
	uint8_t d4 = number % 10;

	disp_characters[0] = seg_pattern[d1];
	disp_characters[1] = seg_pattern[d2];
	disp_characters[2] = seg_pattern[d3];
	disp_characters[3] = seg_pattern[d4];

	if (decimal_pos < 4) {
		disp_characters[decimal_pos] |= (1 << 7);
	}
}

void send_next_character_to_display(void) {
	PORTC &= ~((1 << SH_CP_PIN) | (1 << SH_ST_PIN));

	uint8_t pattern = disp_characters[disp_position];

	for (int8_t i = 7; i >= 0; i--) {
		if (pattern & (1 << i)) {
			PORTC |= (1 << SH_DS_PIN);
			} else {
			PORTC &= ~(1 << SH_DS_PIN);
		}

		PORTC |= (1 << SH_CP_PIN);
		PORTC &= ~(1 << SH_CP_PIN);
	}

	PORTD |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << DS3_PIN) | (1 << DS4_PIN);

	PORTC |= (1 << SH_ST_PIN);
	PORTC &= ~(1 << SH_ST_PIN);

	switch (disp_position) {
		case 0: PORTD &= ~(1 << DS1_PIN); break;
		case 1: PORTD &= ~(1 << DS2_PIN); break;
		case 2: PORTD &= ~(1 << DS3_PIN); break;
		case 3: PORTD &= ~(1 << DS4_PIN); break;
	}

	disp_position = (disp_position + 1) % 4;
}