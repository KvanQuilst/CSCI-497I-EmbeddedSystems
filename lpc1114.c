#include "lpc1114.h"

void setup() __attribute__((weak));
void loop() __attribute__((weak));

void reset() {
  /* Set clock speed to 48MHz */
  SYSCON.MAINCLKSEL.SEL = 0;
  SYSCON.MAINCLKUEN.ENA = 0;
  SYSCON.MAINCLKUEN.ENA = 1;
  SYSCON.SYSPLLCTRL.MSEL = 3;
  SYSCON.SYSPLLCTRL.PSEL = 1;
  SYSCON.SYSPLLCLKSEL.SEL  = 0;
  SYSCON.SYSPLLCLKUEN.ENA  = 0;
  SYSCON.SYSPLLCLKUEN.ENA  = 1;
  SYSCON.PDRUNCFG.ADC_PD = 0;
  SYSCON.PDRUNCFG.SYSPLL = 0;
  while (SYSCON.SYSPLLSTAT.LOCK == 0) {}
  SYSCON.MAINCLKSEL.SEL = 3;
  SYSCON.MAINCLKUEN.ENA = 0;
  SYSCON.MAINCLKUEN.ENA = 1;

  if (setup) setup();
  if (loop) while (1) loop();
  else while (1) __asm("wfi");
}
