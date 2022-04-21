#include "lpc1114.h"

void setup() {
  /* Enable bit 8 in AHBCLKCTRL (pg. 34) CT16B1 */
  SYCON.AHBCLKCTRL.CT16B1 = 1;
  /* MR0 pulse width, turn light/servo on */
  /* MR1 for counter reset task */
}
