void __aeabi_uidiv(unsigned n, unsigned d) {
  unsigned q = 0;
  unsigned r = n;
  while (r >= d) {
    ++q;
    r -= d;
  }
  __asm("mov r1, %0":: "r"(r));
  __asm("mov r0, %0":: "r"(q));
}

void __aeabi_uidivmod(unsigned n, unsigned d) {
  unsigned q = 0;
  unsigned r = n;
  while (r >= d) {
    ++q;
    r -= d;
  }
  __asm("mov r1, %0":: "r"(r));
  __asm("mov r0, %0":: "r"(q));
}
