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


uint8_t counter = 0;
void timer0_init(){
	//TODO: initialise and configure timer0 to count to 10ms
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02);
	OCR0A = 78;
	TIMSK0 |= (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	counter++;
	if(counter == 10){
		led_toggle();
		counter = 0;
	}
}