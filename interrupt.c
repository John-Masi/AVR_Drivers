#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool flag;

ISR(TIMER1_COMPA_vect) {
  flag = 1;
}

void toggle(void) {
  PORTB ^= (1 << 7);
}

void timer(void) {
  OCR1A = 1561;
  TCCR1B |= (1 << WGM12);
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
}

int main(void) {

  DDRB |= (1 << 7);

  timer();

  sei(); // Sets the intterupt bit in SREG to one 

  while(1) {
    if(flag){
      flag = 0;
      toggle();
    }
  }
}
