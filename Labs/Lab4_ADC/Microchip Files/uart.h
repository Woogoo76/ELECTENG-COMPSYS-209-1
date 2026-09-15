/*
 * uart.h
 *
 * Created: 15/09/2026 12:52:06 pm
 *  Author: wilsc
 */ 
#ifndef UART_H
#define UART_H

#include <stdint.h>

void usart_init(uint16_t ubrr);
void usart_transmit(uint8_t data);
void extract_digits(uint16_t number, uint8_t *thousands, uint8_t *hundreds, uint8_t *tens, uint8_t *units);
uint8_t digit_to_ascii(uint8_t digit);
void usart_send_number(uint16_t number);

#endif