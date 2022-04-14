extern void* __INITIAL_SP;
extern void* __VECTOR_CHECKSUM;

void __reset();
void NMI() __attribute__((weak));
void Hardfault() __attribute__((weak));
void svcall() __attribute__((weak));

/* Ch 28, Table 101 (pg. 469) */
unsigned vector[48] __attribute__ ((section(".vector"))) = {
  (unsigned) (&__INITIAL_SP),
  (unsigned) (&__reset) + 1,
  (unsigned) (&NMI) + 1,
  (unsigned) (&Hardfault),
  0, 0, 0,
  (unsigned) (&__VECTOR_CHECKSUM),
  0, 0, 0, 0, 0, 0, 0, 0,
  0, /* IRQ0 */
  0, /* IRQ1 */
  0, /* IRQ2 */
  0, /* IRQ3 */
  0, /* IRQ4 */
  0, /* IRQ5 */
  0, /* IRQ6 */
  0, /* IRQ7 */
  0, /* IRQ8 */
  0, /* IRQ9 */
  0, /* IRQ10 */
  0, /* IRQ11 */
  0, /* IRQ12 */
  0, /* IRQ13 */
  0, /* IRQ14 */
  0, /* IRQ15 */
  0, /* IRQ16 */
  0, /* IRQ17 */
  0, /* IRQ18 */
  0, /* IRQ19 */
  0, /* IRQ20 */
  0, /* IRQ21 */
  0, /* IRQ22 */
  0, /* IRQ23 */
  0, /* IRQ24 */
  0, /* IRQ25 */
  0, /* IRQ26 */
  0, /* IRQ27 */
  0, /* IRQ28 */
  0, /* IRQ29 */
  0, /* IRQ30 */
  0, /* IRQ31 */
};

void NMI() {}
void Hardfault() {}
