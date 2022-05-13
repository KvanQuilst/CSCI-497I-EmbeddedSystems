extern void* __INITIAL_SP;
extern void* __VECTOR_CHECKSUM;

typedef void (*irq_t)();

void __reset();
void __irq();
void NMI() __attribute__((weak));
void Hardfault() __attribute__((weak));
void svcall() __attribute__((weak));
void pendingsvc() __attribute__((weak));
void systick() __attribute__((weak));

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
  (unsigned) (&__irq) + 1,  // NMI
  (unsigned) (&Hardfault) + 1,
  0, 0, 0,
  (unsigned) (&__VECTOR_CHECKSUM),
  0, 0, 0,
  (unsigned) (&__irq) + 1,  // SVCall
  0, 0, 0, 0,
  /*(unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,
  (unsigned) (&__irq) + 1,*/
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  (unsigned) (&IRQ17) + 1,
  //(unsigned) (__irq) + 1,
  0, 0, 0, 0, 0, 0, 
  (unsigned) (&IRQ24) + 1,
  //(unsigned) (__irq) + 1,
  0, 0, 0, 0, 0, 0, 0
};

const irq_t __handler[] = {
  0, 
  0, 
  &NMI, 
  &Hardfault,
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0,
  &svcall, 
  0, 
  0,
  &pendingsvc,
  &systick, 
  &IRQ0, 
  &IRQ1, 
  &IRQ2,
  &IRQ3, 
  &IRQ4, 
  &IRQ5, 
  &IRQ6, 
  &IRQ7,
  &IRQ8, 
  &IRQ9, 
  &IRQ10, 
  &IRQ11, 
  &IRQ12,
  &IRQ13, 
  &IRQ14, 
  &IRQ15, 
  &IRQ16, 
  &IRQ17,
  &IRQ18, 
  &IRQ19, 
  &IRQ20, 
  &IRQ21, 
  &IRQ22,
  &IRQ23, 
  &IRQ24, 
  &IRQ25, 
  &IRQ26, 
  &IRQ27,
  &IRQ28, 
  &IRQ29, 
  &IRQ30, 
  &IRQ31
};
