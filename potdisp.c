#include "i2c.h"
#include "lpc1114.h"
#include "thread.h"
#include "lock.h"

// The ssd1306 will assume that every byte the follows a stream prefix is of
// that type.  For example, every byte from 0x40 to the stop bit is data. 
#define SSD1306_CMD_SINGLE  0x80
#define SSD1306_CMD_STREAM  0x00
#define SSD1306_DATA_STREAM 0x40

// Set contrast with following byte between 0x00 and 0xFF.
#define SSD1306_SET_CONTRAST   0x81

#define SSD1306_ENTIRE_ON_RAM    0xA4
#define SSD1306_ENTIRE_ON_NO_RAM 0xA5
#define SSD1306_NORMAL_DISP      0xA6
#define SSD1306_INVERT_DISP      0xA7
#define SSD1306_DISPLAY_SLEEP    0xAE
#define SSD1306_DISPLAY_ON       0xAF 
#define SSD1306_LOW_COL_START(x)  (0x00|((x)&0x0F)
#define SSD1306_HIGH_COL_START(x) (0x01|((x)&0x0F))

// Set Addressing mode with following byte.
#define SSD1306_SET_ADDR_MODE   0x20
#define SSD1306_ADDR_MODE_HORZ  0x00
#define SSD1306_ADDR_MODE_VIRT  0x01
#define SSD1306_ADDR_MODE_PAGE  0x02

// Set column range with following two bytes.
// Values from 0x00 to 0x7f are valid.
#define SSD1306_SET_COL_ADDR    0x21

// Set page range with following two bytes.
// Values from 0x00 to 0x07
#define SSD1306_SET_PAGE_ADDR   0x22

#define SSD1306_PAGE_START(x)   (0xB0|((x)&0x07))

#define SSD1306_DISP_START_LINE(x) (0x40|((x)&0x3F))
#define SSD1306_SEG_REMAP(x)       (0xA0|((x)&0x01))

// Set the multiplex ratio with following byte
// Values range from 0x0F to 0x3F
#define SSD1306_SET_MPLEX       0xA8

#define SSD1306_COM_FORWARD     0xC0
#define SSD1306_COM_REVERSE     0xC8

// Set the display offset with the following byte
// Values range from 0x00 to 0x3F
#define SSD1306_DISP_OFFSET     0xD3

// Set the hardware comm configuration with following byte
// Values are 0x02, 0x12, 0x22, 0x32
#define SSD1306_COM_HW_CONF     0xDA

// Set the display clock ratio with following byte
// Values are 0x00 to 0xFF
#define SSD1306_CLOCK_DIVIDE   0xD5

// The charge pump is controlled with the following byte
#define SSD1306_CHARGE_PUMP    0x8D
#define SSD1306_PUMP_ON        0x14
#define SSD1306_PUMP_OFF       0x10

// Set the Vcomh deselect level with the following byte
#define SSD1306_DESELECT_LEVEL 0xDB
#define SSD1306_DESELECT_65VCC 0x00
#define SSD1306_DESELECT_77VCC 0x20
#define SSD1306_DESELECT_83VCC 0x30

static const unsigned char ssd1306_init[] = {
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
};

void readTimer();
void setPulse();

THREAD(irq17, readTimer, 1, 32, 0, 0, 0, 0);
THREAD(irq24, setPulse, 1, 32, 0, 0, 0, 0);
sem_t tmr = { 0, 0 };
sem_t data_avail = { 0, 0 };
unsigned data;
unsigned i = 0;

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
  if (i < sizeof(ssd1306_init)) {
    I2C0.DAT = ssd1306_init[i];
    I2C0.CONCLR = (1<<3) | (1<<5);
    i++;
  } else {
    I2C0.CONSET = (1<<4);
    I2C0.CONCLR = (1<<2) | (1<<3) | (1<<5);
  }
}

void IRQ17() {
  TMR16B1.IR.MR1 = 1;
  sem_up(&tmr);
}

void IRQ24() {
  /* Set pulse length */  
  /*TMR16B1.MR0.MATCH = TMR16B1.MR1.MATCH - 500 - ADC.DR0.V_VREF;
  ADC.DR0.DONE;*/
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
