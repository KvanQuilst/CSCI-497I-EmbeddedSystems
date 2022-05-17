#include "i2c.h"
#include "lpc1114.h"
#include "thread.h"
#include "lock.h"

void readTimer();
void setPulse();

THREAD(irq17, readTimer, 1, 32, 0, 0, 0, 0);
THREAD(irq24, setPulse, 1, 32, 0, 0, 0, 0);
sem_t tmr = { 0, 0 };
sem_t data_avail = { 0, 0 };
unsigned i17 = 0;
unsigned i24 = 0;
unsigned data;

void setup() {
  /* Enable bit 8 in AHBCLKCTRL (pg. 34) CT16B1 */
  SYSCON.SYSAHBCLKCTRL.IOCON = 1;

  /* Clock */
  SYSCON.SYSAHBCLKCTRL.CT16B1 = 1;
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
  SYSCON.SYSAHBCLKCTRL.ADC = 1;
  SYSCON.PDRUNCFG.ADC_PD = 0;
  IOCON.R_PIO0_11.FUNC = 2;
  IOCON.R_PIO0_11.MODE = 0;
  IOCON.R_PIO0_11.ADMODE = 0;

  ADC.CR = (10 << 8) | (0 << 17) | (0 << 16) | (1 << 0) | (1 << 24);
  ADC.INTEN.ADINTEN = (1<<0);
  ADC.INTEN.ADGINTEN = 0;

  /* Enable Interrupts */
  ISER.SETENA |= (1<<17) | (1<<24);
}

void IRQ15() {
  switch (I2C0.STAT>>3) {
    case 1: /* STAT condiiton has been transmitted */
    case 2: /* Repeated START condition has been transmitted */

      if (buf_empty())
        I2C0.CONSET = STO;
      else
        I2C0.DAT = buf_pop();
      I2C0.CONCLR = AA | SI | STA;

      break;

    case 3: /* SLA+W has been transmitted; ACK has been received */
    case 5: /* Data byte has been trasmitted; ACK has been received */
      
      if (buf_empty()) {
        sem_up(&wait);
        I2C0.CONSET = STO;
        I2C0.CONCLR = AA | SI | STA;  
      } else {
        I2C0.DAT = buf_pop();
        I2C0.CONCLR = AA | SI | STA;
      }

      break;

    case 4: /* SLA+W has been transmitted; NOT ACK has been recieved */
    case 6: /* Data byte in DAT has been transmitted; NOT ACK has been received */

      sem_up(&wait);
      I2C0.CONSET = STO;
      I2C0.CONCLR = AA | SI | STA;

      break;

    case 7: /* Arbitration lost in SLA+R/W or Data bytes */
      break;
  }
}

void IRQ17() {
  TMR16B1.IR.MR1 = 1;
  sem_up(&tmr);
}

void IRQ24() {
  data = ADC.DR0.V_VREF;
  sem_up(&data_avail);
}

void readTimer() {
  /* Start read */
  i17 = 1;
  while (1) {
    sem_down(&tmr);
    ADC.CR = (10 << 8) | (0 << 17) | (0 << 16) | (1 << 0) | (1 << 24);
  }
}

void setPulse() {
  /* Set pulse length */  
  i24 = 1;
  while (1) {
    sem_down(&data_avail);
    TMR16B1.MR0.MATCH = TMR16B1.MR1.MATCH - 500 - data;
    ADC.DR0.DONE;
  }
}
