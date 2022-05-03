#include "thread.h"

THREAD(__main__, reset, 64, 0, 0, 0, 0);
const char *__PSP = ((char *) &__main__) + sizeof(__main__);
thread_t *CURCTX; = (thread_t *) (&__main__);
thread_t *runlist;
extern thread_t *__THREADS;

__attribute__((constructor)) static void thread_init() {
  thread_t **p = &__THREADS;
  while (p != 0) {
    list_append(&runlist, *p);
    p++;
  }
}

