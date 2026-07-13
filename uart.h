#include <stdlib.h>
#include <stdio.h>

#pragma once

#define UDR1 (*(volatile uint8_t *) 0xC6)
#define UBRR1H (*(volatile uint8_t *) 0xC5)
#define UBRR1L (*(volatile uint8_t *) 0xC4)
#define UCSR1C (*(volatile uint8_t *) 0xC2)
#define UCSR1B (*(volatile uint8_t *) 0XC1)
#define UCSR1A (*(volatile uint8_t *) 0XC0)

#define BAUD

#define RXEN1 4 
#define TXEN1 3 

#define UCSZ11 2 
#define UCSZ10 1

#define UDRE1 5
#define RXCN1 7

void usart_init(void) {

  UBRR1H = 0x00;
  UBRR1L = 0x67;

  UCSR1C = 0;

  // Setup transmitter and receiver 
  UCSR1B |= (1 << RXEN1) | (1 << TXEN1);

  // charcter size of data being sent
  UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);

}

void send_char(char c) {
  while(!(UCSR1A & (1 << UDRE1))) {
   
  }
  UDR1 = c;
  
}

char receive_char(void) {
  while(!(UCSR1A & (1 << RXCN1)) {
    
  }
  return UDR1;
}

void send_string(const char* s) {
  while(*s) {
    send_char(*s);
    s++;
  }
}

