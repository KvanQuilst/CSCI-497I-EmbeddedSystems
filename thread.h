typedef struct thread_st {
  thread_st *next;
  unsigned *sp;
} thread_t;

extern thread_t *CURCTX;
extern thread_t *runlist;

#define THREAD(name, startfun, stacksize, arg0, arg1, arg2, arg3) \
  struct {                                                        \
    thread_t thread;                                              \
    unsigned stack[(stacksize)-16];                               \
    unsigned r8, r9, r10, r11;                                    \
    unsigned r4, r5, r6, r7;                                      \
    unsigned r0, r1, r2, r3, r12, lr;                             \
    void (*pc)();                                                 \
    unsigned psr;                                                 \
  } static name = {                                               \
    { (void *) (0), &(name.r8) }, {0},                            \
      0, 0, 0, 0, 0, 0, 0, 0,                                     \
      arg0, arg1, arg2, arg3, 0, 0,                               \
      startfun, (1<<24)                                           \
  };                                                              \
  static void *__##name##__ptr __attribute__((section(".threads"))) = &name; \

void schedule();
