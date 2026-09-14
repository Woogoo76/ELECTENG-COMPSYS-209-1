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
	chan &= 0x07; 
	ADMUX = (ADMUX & 0xF0) | chan; //selects the channel, but keeps top 4 bits (REFS1:0,ADLAR,reserved bit)
	ADCSRA |= (1<< ADSC); //enables adc working bit
	while (ADCSRA & (1 << ADSC)); //waits for adc working bit to be off
	return ADC; // returns the value
}

uint16_t adc_convert_mv(uint16_t uvalue){
	
return	(uint32_t)uvalue * 5000/1024; // scale raw ADC count to mV (Vref = 5V) 
	
}