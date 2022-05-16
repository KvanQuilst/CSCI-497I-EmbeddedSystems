#pragma once

#include "lock.h"

struct buffer {
  char buf[8];
  unsigned char first : 3;
  unsigned char last  : 3;
  unsigned char       : 2;
  sem_t empty;
  sem_t full;
};

void buf_push(char c);
char buf_pop();
