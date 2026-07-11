#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma once

#define DDRA ((volatile uint8_t *)0x21)
#define PORTA ((volatile uint8_t *)0x22)

#define DDRB ((volatile uint8_t *)0x24)
#define PORTB ((volatile uint8_t *)0x25)
#define PINB ((volatile uint8_t *)0x23)


// TCCRB1 : Timer 1 control register B 
// TIMSK1 : Timer 1 intterupt register 
// OCR1A : Compare Match value for timer 
// OCIE1A : Output compare match A intterupt enable at bit 6
// WGM12 : Waveform generation Mode for TCCRB1 at bit 4
#define TCCR1B ((volatile uint8_t *) 0x81) 
#define TIMSK1 ((volatile uint8_t *) 0x6F)
#define OCIE1A 6
#define CS12 3
#define CS10 0
#define WGM12 4

void turn_led() { 
  *DDRB |= (1U << 7);
  //*PORTB |= (1U << 7);
}

void turn_off_led() {
  *PORTB &= ~(1U << 7);
}

void setPIN(volatile uint8_t n) {
  *PORTA |= (1U << n);
}

void clearPIN(volatile uint8_t n) {
  *PORTA &= ~(1U << n);
}

bool checkPIN(volatile uint8_t n) {
  uint8_t mode = (*DDRA >> n) & 1;
  if(*PORTA & (1U << n)) {


    return true;
  }
  return false;
}
