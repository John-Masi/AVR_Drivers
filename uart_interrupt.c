#include <avr/interrupt.h> 
#include <avr/io.h>
#include <string.h>
#include "uart.h"

volatile char rx_buffer[32];
volatile uint8_t i = 0;
volatile uint8_t ready = 0;

// Interrupt when RX Line has data from the TX Line and then intterupts the cpu and reads the data 
ISR(USART0_RX_vect){

  char c = UDR0;
  if(c == '\n' || c == '\r') {
    

    rx_buffer[i] = '\0';
    ready = 1;
    UDR0 = '\r';
    UDR0 = '\n';
  
  else if (i < sizeof(rx_buffer) - 1) {
    rx_buffer[i++] = c;
    UDR0 = c;
  }
}


int main() {
  DDRB |= (1 << 7);
  usart2_init();
  sei();

  send_string("Hey\n\r");
  while(1) {
    if(ready) {
      ready = 0;
      if(strcmp(rx_buffer,"On") == 0) {
        PORTB |= (1 << 7);
      }
      else if(strcmp(rx_buffer,"Off") == 0) {
        PORTB &= ~(1 << 7);
      }
      i = 0;
    }
    
  }
}
