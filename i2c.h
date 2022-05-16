#pragma once

#include "lock.h"

struct buf_info {
  unsigned first : 3;
  unsigned last  : 3;
  unsigned used  : 4;
  unsigned       : 0;
};

void buf_push(char c);
char buf_pop();
