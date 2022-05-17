#include "i2c.h"
#include "lpc1114.h"
#include "thread.h"

char buf[8];
struct buf_info bi = { 0, 0, 0 };
sem_t empty = { 8, 0 };
sem_t wait = { 0 , 0 };
sem_t lock = { 1, 0 };

__attribute__((constructor))
static void i2c_init() {
  SYSCON.PRESETCTRL.I2C_RST_N = 1;
  SYSCON.SYSAHBCLKCTRL.IOCON = 1;
  SYSCON.SYSAHBCLKCTRL.I2C = 1;
  IOCON.PIO0_4.FUNC = 1;
  IOCON.PIO0_4.I2CMODE = 0;
  IOCON.PIO0_5.FUNC = 1;
  IOCON.PIO0_5.I2CMODE = 0;
  I2C0.SCLH = 240;
  I2C0.SCLL = 240;
  I2C0.CONSET = (1<<6);
  ISER.SETENA |= (1<<15);
}

void buf_push(char c) {
  sem_down(&empty);
  buf[bi.first] = c;
  bi.first++;
  bi.used++;
}

char buf_pop() {
  if (bi.used != 0) {
    char c = buf[bi.last];
    bi.last++;
    bi.used--;
    sem_up(&empty);
    return c;
  } else 
    return -1;
}

unsigned buf_empty() { return bi.used == 0; }

void i2c_write(char addr, char (*underflow)(unsigned), unsigned size) {
  unsigned i = 0;
  sem_down(&lock);

  buf_push(addr);
  while (bi.used < 8 && i < size) {
    buf_push(underflow(i));
    ++i;
  }

  I2C0.CONSET = STA;

  while (i < size) {
    buf_push(underflow(i));
    ++i;
  }

  sem_down(&wait);
  sem_up(&lock);
}
