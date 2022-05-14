#include "thread.h"

//SYS_THREAD(main, 0, 3, 64, 0, 0, 0, 0);
THREAD(__main__, 0, 64, 0, 0, 0, 0);
const char *__PSP = ((char *) &(__main__) + sizeof(__main__));
thread_t *CURCTX = (thread_t *) (&__main__);
//priority runlist[4] = {0};
thread_t *runlist = 0;
extern thread_t *__THREAD;

static void runlist_append(thread_t *thread);

__attribute__((constructor)) 
static void thread_init() {
  thread_t **p = &__THREAD;
  while (*p != 0) {
    runlist_append(*p);
    p++;
  }
}

/*void schedule() {
  if (CURCTX)
    runlist_append(CURCTX);
  if (runlist[0].next != 0) {
    CURCTX = runlist[0].next;
    runlist[0].next = CURCTX->next;
  } else if (runlist[1].next != 0) {
    CURCTX = runlist[1].next;
    runlist[1].next = CURCTX->next;
  } else if (runlist[2].next != 0) {
    CURCTX = runlist[2].next;
    runlist[2].next = CURCTX->next;
  } else {
    CURCTX = runlist[3].next;
    if (CURCTX != __main__)
      runlist[3].next = CURCTX->next;
  }
}

static void runlist_append(thread_t *thread)
{
  if (thread->priority > 3)
    return;
  thread->next = 0;
  if (runlist[thread->priority].end)
    runlist[thread->priority].end->next = thread;
  else
    runlist[thread->priority].next = thread;
  runlist[thread->priority].end = thread;
}*/

void schedule() {
  if (CURCTX) {
    CURCTX->next = 0;
    runlist_append(CURCTX);
  }
  CURCTX = runlist;
  runlist = runlist->next;
}

static void runlist_append(thread_t *thread) {
  thread_t **list = &runlist;
  while (*list != 0)
    list = &((*list)->next);
  *list = thread;
}
