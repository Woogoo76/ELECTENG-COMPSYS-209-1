/*
 * timer0.c
 *
 * Created: 21/09/2026 6:04:17 pm
 *  Author: wilsc
 */ 
#include "timer0.h"
#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t timer_value = 0;
volatile uint8_t measurement_complete = 0;

void timer0_init(){
	// Initialise and configure timer
	TCCR1A = 0;
}

void int0_init(void) {
	DDRD &= ~(1 << DDD2);
	PORTD |= (1 << PORTD2);
	EICRA |= (1 << ISC00);
	EICRA &= ~(1 << ISC01);
	EIMSK |= (1 << INT0);
}

ISR(INT0_vect) {
	if (PIND & (1 << PD2)) {
		TCNT1 = 0;
		TCCR1B |= (1 << CS12);
	} else {
		TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
		timer_value = TCNT1;
		measurement_complete = 1;
	}
}