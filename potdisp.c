#include "i2c.h"
#include "lpc1114.h"
#include "thread.h"
#include "lock.h"

/*static const unsigned char ssd1306_init[] = {
  0x78,
  0x80, 0xA8, 0x80, 0x3f,
  0x80, 0xD3, 0x80, 0x00,
  0x80, 0x40,
  0x80, 0xA1,
  0x80 ,0xC8,
  0x80, 0xDA, 0x80, 0x12,
  0x80, 0x81, 0x80, 0x7f,
  0x80, 0xA4,
  0x80, 0xA6,
  0x80, 0xD5, 0x80, 0x80,
  0x80, 0x8D, 0x80, 0x14,
  0x80, 0xAF,

  0x80, 0x21, 0x80, 0x00, 0x80, 0x7f,
  0x80, 0x22, 0x80, 0x00, 0x80, 0x07,
  0x80, 0x20, 0x80, 0x00,

  0x40,
  0x55, 0x55, 0x55, 0x55, 0x55,
  0x55, 0x55, 0x55, 0x55, 0x55
};*/

void readTimer();
void setPulse();

THREAD(irq17, readTimer, 1, 32, 0, 0, 0, 0);
THREAD(irq24, setPulse, 1, 32, 0, 0, 0, 0);
sem_t tmr = { 0, 0 };
sem_t data_avail = { 0, 0 };
unsigned data;
//unsigned i = 0;

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
  /*if (i < sizeof(ssd1306_init)) {
    I2C0.DAT = ssd1306_init[i];
    I2C0.CONCLR = (1<<3) | (1<<5);
    i++;
  } else {
    I2C0.DAT = 0x55;
    I2C0.CONCLR = (1<<3) | (1<<5);
  }*/
  char c = buf_pop();
  if (c != -1)
    I2C0.DAT = c;
  I2C0.CONCLR = (1<<3) | (1<<5);
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
  while (1) {
    sem_down(&tmr);
    ADC.CR = (10 << 8) | (0 << 17) | (0 << 16) | (1 << 0) | (1 << 24);
  }
}

void setPulse() {
  /* Set pulse length */  
  while (1) {
    sem_down(&data_avail);
    TMR16B1.MR0.MATCH = TMR16B1.MR1.MATCH - 500 - data;
    ADC.DR0.DONE;
  }
}
