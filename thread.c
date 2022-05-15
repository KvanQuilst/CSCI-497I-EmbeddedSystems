#include "list.h"
#include "thread.h"

SYS_THREAD(__main__, 0, 3, 64, 0, 0, 0, 0);
const char *__PSP = ((char *) &(__main__) + sizeof(__main__));
thread_t *CURCTX = (thread_t *) (&__main__);
priority runlist[4] = {0};
extern thread_t *__THREAD;

static void runlist_pop();

__attribute__((constructor)) 
static void thread_init() {
  thread_t **p = &__THREAD;
  while (*p != 0) {
    runlist_append(*p);
    p++;
  }
}

void schedule() {
  if (CURCTX)
    runlist_append(CURCTX);
  if (runlist[0].next != 0) {
    CURCTX = runlist[0].next;
    runlist[0].next = CURCTX->next;
    if (runlist[0].next == 0)
      runlist[0].end = 0;
  } else if (runlist[1].next != 0) {
    CURCTX = runlist[1].next;
    runlist[1].next = CURCTX->next;
    if (runlist[1].next == 0)
      runlist[1].end = 0;
  } else if (runlist[2].next != 0) {
    CURCTX = runlist[2].next;
    runlist[2].next = CURCTX->next;
    if (runlist[2].next == 0)
      runlist[2].end = 0;
  } else {
    CURCTX = runlist[3].next;
    runlist[3].next = CURCTX->next;
    if (runlist[3].next == 0)
      runlist[3].end = 0;
  }
  CURCTX->next = 0;
}

void runlist_append(thread_t *thread)
{
  if (thread->priority > 3)
    thread->priority = 3;
  thread->next = 0;

  if (runlist[thread->priority].next == 0) {
    runlist[thread->priority].next = thread;
    runlist[thread->priority].end = thread;
  } else {
    runlist[thread->priority].end->next = thread;
    runlist[thread->priority].end = thread;
  }
}
