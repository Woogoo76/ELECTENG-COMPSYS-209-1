/*
 * led.c
 *
 * Created: 21/09/2026 6:04:55 pm
 *  Author: wilsc
 */ 
#include "led.h"
#include <avr/io.h>

void led_toggle(){
	PORTB ^= (1 << PB5);
}