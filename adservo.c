#include "lpc1114.h"

void setup() {
  /* Enable bit 8 in AHBCLKCTRL (pg. 34) CT16B1 */
  SYSCON.AHBCLKCTRL.CT16B1 = 1;

  /* Clock */
  IOCON.PIO1_9.FUNC = 1;  /* Servo uses clock */
  IOCON.PIO1_9.MODE = 0;

  TMR16B1.TCR.EN = 1;
  TMR16B1.PR.PR = 47;     /* Set prescalar value to get 1us = 1hz */
  TMR16B1.MR1 = 19999;    /* Set max clock count MR1 */
  /* MR0 pulse width, turn light/servo on */
  TMR16B1.MR0 = 15000;    /* Set max clock count MR0 */

  /* MR1 for counter reset task */

  /* ADC */
  IOCON.R_PIO0_11.FUNC = 2;
  IOCON.MODE = 0;
}

void IRQ17() {

}

void IRQ24() {

}
