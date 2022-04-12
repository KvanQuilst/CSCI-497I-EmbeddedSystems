extern void* __INITIAL_SP;
extern void* __VECTOR_CHECKSUM;

void __reset();
void NMI() __attribute__((weak));
void Hardfault() __attribute__((weak));
void svcall() __attribute__((weak));

unsigned vector[48] __attribute__ ((section(".vector"))) = {
  (unsigned) (&__INITIAL_SP),
  (unsigned) (&__reset) + 1,
  (unsigned) (&NMI) + 1,
  (unsigned) (&Hardfault),
  0, 0, 0,
  (unsigned) (&__VECTOR_CHECKSUM),
  0, 0, 0, 0
};
