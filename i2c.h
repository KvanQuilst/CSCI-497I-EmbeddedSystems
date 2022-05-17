#pragma once

#include "lock.h"

#define AA    (1<<2)
#define SI    (1<<3)
#define STO   (1<<4)
#define STA   (1<<5)
#define I2EN  (1<<6)

struct buf_info {
  unsigned first : 3;
  unsigned last  : 3;
  unsigned used  : 4;
  unsigned       : 0;
};

extern sem_t wait;

void buf_push(char c);
char buf_pop();
unsigned buf_empty();

void i2c_write(char addr, char (*underflow)(unsigned), unsigned size);
