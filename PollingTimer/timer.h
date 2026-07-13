#include <stdio.h>
#include <stdlib.h>

#define TCCR0B (*(volatile uint8_t *)0x45)
#define TCCR0A (*(volatile uint8_t *)0x44)
#define TCNT0 (*(volatile uint8_t *)0x46)
#define OCR0B (*(volatile uint8_t *)0x47)
#define OCR0A (*(volatile uint8_t *)0x48)
#define TIFR0 (*(volatile uint8_t *)0x35)
#define DDRB (*(volatile uint8_t *)0X24)
#define PORTB (*(volatile uint8_t *)0x25)

#define CS02 2
#define CS01 1
#define CS00 0
#define OCF0A 1

#define WGM02 3

void gpio_init(void) {
  DDRB |= (1 << 7);
  PORTB |= (1 << 7);
}

void toggle_pin(void) {
  PORTB ^= (1 << 7);
}

void timer_init(void) {
  // Prescaler
  OCR0B = 249;
  TCCR0B |= (1 << CS01) | (1 << CS00);
  TCCR0B |= (1 << WGM02);
}

void poll_timer(void) {
  if(TIFR0 & (1 << OCF0A)) {

    PORTB |= (1 << 7);

    TIFR0 |= (1 << OCF0A);

  }
}

