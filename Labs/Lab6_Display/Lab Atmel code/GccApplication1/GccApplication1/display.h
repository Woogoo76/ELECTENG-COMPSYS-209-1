/*
 * display.h
 *
 * Created: 28/09/2026 8:07:56 pm
 *  Author: wilsc
 */ 
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>
#include <stdint.h>

void init_display(void);
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos);
void send_next_character_to_display(void);

#endif