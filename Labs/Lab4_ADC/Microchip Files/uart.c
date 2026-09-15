/*
 * uart.c
 *
 * Created: 15/09/2026 12:50:21 pm
 *  Author: wilsc
 */ 
#include "uart.h"
#include <avr/io.h>

void usart_init(uint16_t ubrr) {
	UCSR0A = 0b00000000;
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_transmit(uint8_t data) {
	while ((UCSR0A & (1 << UDRE0)) == 0) {
		;
	}
	UDR0 = data;
}

void extract_digits(uint16_t number, uint8_t *thousands, uint8_t *hundreds, uint8_t *tens, uint8_t *units) {
	*thousands = (number / 1000) % 10;
	*hundreds  = (number / 100) % 10;
	*tens      = (number / 10) % 10;
	*units     = number % 10;
}

uint8_t digit_to_ascii(uint8_t digit) {
	return digit + 48;
}

void usart_send_number(uint16_t number) {
	uint8_t thousands, hundreds, tens, units;
	extract_digits(number, &thousands, &hundreds, &tens, &units);

	usart_transmit(digit_to_ascii(thousands));
	usart_transmit(digit_to_ascii(hundreds));
	usart_transmit(digit_to_ascii(tens));
	usart_transmit(digit_to_ascii(units));
	usart_transmit('\r');
	usart_transmit('\n');
}