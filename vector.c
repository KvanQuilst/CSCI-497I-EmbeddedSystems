extern void* __INITIAL_SP;
extern void* __VECTOR_CHECKSUM;

void __reset();
void NMI() __attribute__((weak));
void Hardfault() __attribute__((weak));
void svcall() __attribute__((weak));

void IRQ0() __attribute__((weak));
void IRQ1() __attribute__((weak));
void IRQ2() __attribute__((weak));
void IRQ3() __attribute__((weak));
void IRQ4() __attribute__((weak));
void IRQ5() __attribute__((weak));
void IRQ6() __attribute__((weak));
void IRQ7() __attribute__((weak));
void IRQ8() __attribute__((weak));
void IRQ9() __attribute__((weak));
void IRQ10() __attribute__((weak));
void IRQ11() __attribute__((weak));
void IRQ12() __attribute__((weak));
void IRQ13() __attribute__((weak));
void IRQ14() __attribute__((weak));
void IRQ15() __attribute__((weak));
void IRQ16() __attribute__((weak));
void IRQ17() __attribute__((weak));
void IRQ18() __attribute__((weak));
void IRQ19() __attribute__((weak));
void IRQ20() __attribute__((weak));
void IRQ21() __attribute__((weak));
void IRQ22() __attribute__((weak));
void IRQ23() __attribute__((weak));
void IRQ24() __attribute__((weak));
void IRQ25() __attribute__((weak));
void IRQ26() __attribute__((weak));
void IRQ27() __attribute__((weak));
void IRQ28() __attribute__((weak));
void IRQ29() __attribute__((weak));
void IRQ30() __attribute__((weak));
void IRQ31() __attribute__((weak));

/* Ch 28, Table 101 (pg. 469) */
unsigned vector[48] __attribute__ ((section(".vector"))) = {
  (unsigned) (&__INITIAL_SP),
  (unsigned) (&__reset) + 1,
  (unsigned) (&NMI) + 1,
  (unsigned) (&Hardfault) + 1,
  0, 0, 0,
  (unsigned) (&__VECTOR_CHECKSUM),
  0, 0, 0, 0, 0, 0, 0, 0,
  (unsigned) (&IRQ0) + 1,
  (unsigned) (&IRQ1) + 1,
  (unsigned) (&IRQ2) + 1,
  (unsigned) (&IRQ3) + 1,
  (unsigned) (&IRQ4) + 1,
  (unsigned) (&IRQ5) + 1,
  (unsigned) (&IRQ6) + 1,
  (unsigned) (&IRQ7) + 1,
  (unsigned) (&IRQ8) + 1,
  (unsigned) (&IRQ9) + 1,
  (unsigned) (&IRQ10) + 1,
  (unsigned) (&IRQ11) + 1,
  (unsigned) (&IRQ12) + 1,
  (unsigned) (&IRQ13) + 1,
  (unsigned) (&IRQ14) + 1,
  (unsigned) (&IRQ15) + 1,
  (unsigned) (&IRQ16) + 1,
  (unsigned) (&IRQ17) + 1,
  (unsigned) (&IRQ18) + 1,
  (unsigned) (&IRQ19) + 1,
  (unsigned) (&IRQ20) + 1,
  (unsigned) (&IRQ21) + 1,
  (unsigned) (&IRQ22) + 1,
  (unsigned) (&IRQ23) + 1,
  (unsigned) (&IRQ24) + 1,
  (unsigned) (&IRQ25) + 1,
  (unsigned) (&IRQ26) + 1,
  (unsigned) (&IRQ27) + 1,
  (unsigned) (&IRQ28) + 1,
  (unsigned) (&IRQ29) + 1,
  (unsigned) (&IRQ30) + 1,
  (unsigned) (&IRQ31) + 1
};

void NMI() {}
