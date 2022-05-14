#include "list.h"
#include "lock.h"

static int is_interrupt() {
  int r;
  __asm("mrs %0, psr" : "=r"(r));
  return r & 0x3F;
}

/*
    MUTEX
*/

void mut_action(unsigned action, ...) {

}

void sys_mut_init(mut_t *m) {

}

void mut_init(mut_t *m) {
  if (!is_interrupt())
    mut_action(0, m);
  else
    sys_mut_init(m);
}

void sys_mut_lock(mut_t *m) {
  __asm("cpsid i");

  if (m->owner == CURCTX) {
    char *fault = 0;
    *fault = 1;
  }

  if (m->owner != 0) {
    list_append((listnode_t **) &m->waiting, (listnode_t *) CURCTX);
    CURCTX = 0;
  }
  else
    m->owner = CURCTX;
  __asm("cpsie i");
}

void mut_lock(mut_t *m) {

}

void sys_mut_unlock(mut_t *m) {
  __asm("cpsid i");

  if (m->owner != CURCTX) {
    char *fault = 0;
    *fault = 1;
  }

  m->owner = (thread_t *) list_pop((listnode_t **) &m->waiting);
  runlist_append(m->owner);

  __asm("cpsie i");
}

void mut_unlock(mut_t *m) {

}


/*
    SEMAPHORE
*/

void* sem_family[] = { 
  &sem_init, 
  &sem_up, 
  &sem_down 
};

void sem_action(unsigned action, ...) {
  __asm("svc 0");
}

static void sys_sem_init(sem_t *s, unsigned i) {
  __asm("cpsid i");

  s->value = i;
  s->waiting = 0;

  __asm("cpsie i");
}
void sem_init(sem_t *s, unsigned i) {
  if (!is_interrupt())
    sem_action(0, s, i);
  else
    sys_sem_init(s, i);
}

static void sys_sem_up(sem_t *s) {
  __asm("cpsid i");

  if (s->waiting != 0)
    runlist_append((thread_t *) list_pop((list_t *) &s->waiting));
  else 
    s->value++;

  __asm("cpsie i");
}

void sem_up(sem_t *s) {
  if (!is_interrupt())
    sem_action(1, s);
  else
    sys_sem_up(s);
}

static void sys_sem_down(sem_t *s) {
  __asm("cpsid i");

  if (s->value == 0) {
    list_append((list_t *) &s->waiting, (listnode_t *) CURCTX);
    CURCTX = 0;
  } else
    s->value--;

  __asm("cpsie i");
}

void sem_down(sem_t *s) {
  if (!is_interrupt())
    sem_action(2, s);
  else
    sys_sem_down(s);
}
