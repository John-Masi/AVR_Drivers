#include "timer.h"

int main() {
  gpio_init();
  timer_init();

  while(1) {

    poll_timer();
  }
}
