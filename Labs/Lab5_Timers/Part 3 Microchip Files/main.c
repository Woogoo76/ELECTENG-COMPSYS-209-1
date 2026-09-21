/*
 * GccApplication2.c
 *
 * Created: 21/09/2026 6:02:43 pm
 * Author : wilsc
 */ 
#define F_CPU 2000000UL

#include "timer0.h"
#include "led.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	//TODO: set direction of LED port to OUTPUT
	DDRB |= (1 << DDB5);
	
	timer0_init();
	
	sei();
	
	while(1){
		
	}
}
