/*
 * adc.c
 *
 * Created: 14/09/2026 10:08:32 pm
 *  Author: wilsc
 */ 
#include "common.h"
#include "adc.h"
#include <avr/io.h>  //Necessary for definitions of ADMUX etc

void adc_init() {
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2);
}

uint16_t adc_read(uint8_t chan) {
//Code written in Part 3 goes here
}