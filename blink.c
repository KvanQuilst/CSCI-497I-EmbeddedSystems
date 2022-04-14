#include "lpc1114.h"

void setup() {
  GPIO1.GDIR |= 1 << 9;
}

void loop() {
  const int scale = 5000;
  const int DOT = 25*scale;
  const int DASH = 75*scale;
  const int INDOT = 25*scale;
  const int INCHAR = 50*scale;
  const int INWORD = 150*scale;

  static const int helloworld[] = {
    0,0,0,0,2,  // H
    0,2,        // E
    0,1,0,0,2,  // L
    0,1,0,0,2,  // L
    1,1,1,      // O
    3,
    0,1,1,2,    // W
    1,1,1,2,    // O
    0,1,0,2,    // R
    0,1,0,0,2,  // L
    1,0,0,      // D
    3
  };

  int length = sizeof(helloworld)/sizeof(int);
  for (int i = 0; i < length; i++) {
    switch (helloworld[i]) {
      case 0:
        GPIO1.DATA[1<<9] = ~0;
        for (int j = 0; j < DOT; j++)
          __asm("nop");
        GPIO1.DATA[1<<9] = 0;
        for (int j = 0; j < INDOT; j++)
          __asm("nop");
        break;
      case 1:
        GPIO1.DATA[1<<9] = ~0;
        for (int j = 0; j < DASH; j++)
          __asm("nop");
        GPIO1.DATA[1<<9] = 0;
        for (int j = 0; j < INDOT; j++)
          __asm("nop");
        break;
      case 2:
        for (int j = 0; j < INCHAR; j++)
          __asm("nop");
        break;
      case 3:
        for (int j = 0; j < INWORD; j++)
          __asm("nop");
        break;
    }
  }
}
