#include "lpc1114.h"
#include "thread.h"
#include "lock.h"

void readTimer();
void setPulse();

THREAD(irq17, readTimer, 32, 0, 0, 0, 0);
sem_t s;

void setup() {
  /* Enable bit 8 in AHBCLKCTRL (pg. 34) CT16B1 */
  SYSCON.SYSAHBCLKCTRL.IOCON = 1;
  SYSCON.SYSAHBCLKCTRL.CT16B1 = 1;
  SYSCON.SYSAHBCLKCTRL.ADC = 1;
  SYSCON.PDRUNCFG.ADC_PD = 0;

  /* Clock */
  IOCON.PIO1_9.FUNC = 1;        /* Servo uses clock */
  IOCON.PIO1_9.MODE = 0;

  TMR16B1.TCR.CE = 1;
  TMR16B1.PR.PR = 47;           /* Set prescalar value to get 1us = 1hz */
  TMR16B1.MCR.MR1I = 1;         /* Enable MR1 Interrupts */
  TMR16B1.MCR.MR1R = 1;         /* Reset clock on MR1 */
  TMR16B1.MCR.MR1S = 0;
  TMR16B1.MR1.MATCH = 20000;    /* Set max clock count MR1 */
  TMR16B1.MR0.MATCH = 19500;    /* Set max clock count MR0 */
  TMR16B1.PWMC.PWMEN0 = 1;      /* On MR0, set PIO1_9 low */

  /* ADC */
  IOCON.R_PIO0_11.FUNC = 2;
  IOCON.R_PIO0_11.MODE = 0;
  IOCON.R_PIO0_11.ADMODE = 0;

  ADC.CR = (10 << 8) | (0 << 17) | (0 << 16) | (1 << 0) | (1 << 24);
  ADC.INTEN.ADINTEN = (1<<0);

  /* Enable Interrupts */
  ISER.SETENA |= (1<<17) | (1<<24);

  sem_init(&s, 0);
}

void IRQ17() {
  TMR16B1.IR.MR1 = 1;
  sem_up(&s);
}

void IRQ24() {
  /* Set pulse length */  
  TMR16B1.MR0.MATCH = TMR16B1.MR1.MATCH - 500 - ADC.DR0.V_VREF;
  ADC.DR0.DONE;
}

void readTimer() {
  /* Start read */
  while (1) {
    sem_down(&s);
    TMR16B1.IR.MR1 = 1;
    ADC.CR = (10 << 8) | (0 << 17) | (0 << 16) | (1 << 0) | (1 << 24);
  }
}

void setPulse() {

}
