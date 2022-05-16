#include "lock.h"

typedef void (*SYS)(unsigned, unsigned, unsigned);
typedef SYS *family_t;

family_t families[] = {
  (family_t) sem_family
};

void svcall() {
  unsigned r0 = CURCTX->sp[8];
  unsigned r1 = CURCTX->sp[9];
  unsigned r2 = CURCTX->sp[10];
  unsigned r3 = CURCTX->sp[11];
  unsigned char *pc = (unsigned char *) CURCTX->sp[14];
  unsigned char *svc = (unsigned char *) pc-2;
  if (families[*svc][r0])
    families[*svc][r0](r1, r2, r3);
}
