#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h> 


volatile uint16_t timer_ticks = 0;
ISR(TIMER1_COMPA_vect) {
  timer_ticks++;
}

void timer(void) {
  OCR1A = 7811;
  TCCR1B |= (1 << WGM12);
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B |= (1 << CS12) | (1 << CS10);
}

int main(void) {
  uint16_t ticks;
  DDRB |= (1 << 7);
  timer();
 
  sei(); 
  while(1) {

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      ticks = timer_ticks;
    }

    
    if(ticks >= 2) {
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        timer_ticks = 0;
      }
      PORTB ^= (1 << 7);
    }
  }
}
