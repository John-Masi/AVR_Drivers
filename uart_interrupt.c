#include <avr/interrupt.h> 
#include <avr/io.h>
#include <string.h>

void usart2_init(void) {
  UBRR0H = 0x00;
  UBRR0L = 0x67;
  UCSR0C = 0;
  UCSR0B |= (1 << RXCIE0);
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

  // charcter size of data being sent
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);

}

volatile char buffer[32];
volatile uint8_t head = 0;
volatile uint8_t tail = 0;
volatile uint8_t ready;

volatile char tx_buffer[32];
volatile uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;
ISR(USART0_UDRE_vect) {

  UDR0 = tx_buffer[tx_tail++];
  if(tx_tail >= sizeof(tx_buffer)) {
    tx_tail = 0;
  }

  if(tx_head == tx_tail) {
    UCSR0B &= ~(1 << 5);
  }

}

// Non blocking char
void x_char(char c) {
  tx_buffer[tx_head] = c;
  tx_head++;
  if(tx_head >= sizeof(tx_buffer)) {
    tx_head = 0;
  }

    UCSR0B |= (1 << 5);

}

void tx_string(const char* str) {
  while(*str) {
    x_char(*str);
    str++;
  }

}

ISR(USART0_RX_vect){

  char c = UDR0;
  if(c == '\r' || c == '\n'){
    buffer[head] = '\0';
    x_char('\r');
    x_char('\n');
    ready = 1;
  }
  else { 
      buffer[head++] = c;
      x_char(c);
  }

}

int main() {
  DDRB |= (1 << 7);
  usart2_init();
  sei();

  while(1) {
    if(ready) {
      ready = 0;
      if(strcmp(buffer,"On") == 0) {
        PORTB |= (1 << 7);
        tx_string("LED ON\n\r");
      }
      else if(strcmp(buffer,"Off") == 0) {
        PORTB &= ~(1 << 7);
      }
      head = 0;
      buffer[0] = '\0';
    }
    
  }
}
