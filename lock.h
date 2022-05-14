#pragma once

#include "thread.h"

typedef struct mutex_st {
  thread_t *owner;
  thread_t *waiting;  
} mut_t;

typedef struct sem_st {
  unsigned value;
  thread_t *waiting;
} sem_t;

extern void *sem_family[];

void sem_init(sem_t *s, unsigned i);
void sem_up(sem_t *s);
void sem_down(sem_t *s);
