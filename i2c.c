#include "i2c.h"
#include "lpc1114.h"
#include "thread.h"

#define ADDR 0x78

struct buffer buf = {
  {0}, 0, 0, { 8, 0 }, { 0, 0 }
};

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
  sem_down(&buf.empty);
  buf.buf[buf.first] = c;
  buf.first++;
  sem_up(&buf.full);
}

char buf_pop() {
  if (buf.empty.value != 8) {
    sem_down(&buf.full);
    char c = buf.buf[buf.last];
    buf.last++;
    sem_up(&buf.empty);
    return c;
  } else 
    return -1;
}

void i2c_write() {
  I2C0.CONSET = (1<<5);
  I2C0.DAT = 0x78;

  while (1)
    __asm("wfi");
}
THREAD(disp, i2c_write, 2, 32, 0, 0, 0, 0);
