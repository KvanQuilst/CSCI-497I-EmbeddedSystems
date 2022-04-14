void setup() __attribute__((weak));
void loop() __attribute__((weak));

void reset() {
  /* Set clock speed to 48MHz */
  /*SYSCON.MAINCLKSEL = 0;
  SYSCON.MAINCLKUEN = 0;
  SYSCON.MAINCLKUEN = 1;
  SYSCON.PLLCTRL    = 0x23;
  SYSCON.PLLCLKSEL  = 0;
  SYSCON.PLLCLKUEN  = 0;
  SYSCON.PLLCLKUEN  = 1;
  SYSCON.PDFUNCFG   &= ~(1<<7);
  while (SYSCON.SYSPLLSTAT == 0) {}
  SYSCON.MAINCLKSEL = 0x3;
  SYSCON.MAINCLKUEN = 0;
  SYSCON>MAINCLKUEN = 1;*/

  if (setup) setup();
  if (loop) while (1) loop();
  else while (1) __asm("wfi");
}
