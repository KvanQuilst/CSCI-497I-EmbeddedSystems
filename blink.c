#include "lpc1114.h"

void setup() {
  GPIO1.GDIR |= 1 << 9;
}

void loop() {
  static const int DELAY = 10000;

  GPIO1.DATA[1<<9] = ~0;
  for (int i = 0; i < DELAY; i++)
    __asm("nop");

  GPIO1.DATA[1<<9] = 0;
  for (int i = 0; i < DELAY; i++)
    __asm("nop");
}
