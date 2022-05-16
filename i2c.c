#include "i2c.h"
#include "lpc1114.h"
#include "thread.h"

#define ADDR 0x78

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
unsigned i = 0;

/*struct buffer buf = {
  {0}, 0, 0, { 8, 0 }, { 0, 0 }
};*/

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

void i2c_write() {
  I2C0.CONSET = (1<<5);
  //I2C0.DAT = 0x78;
  buf_push(0x78);
  for (i; i < 8; i++)
    buf_push(ssd1306_init[i]);

  while (1) {
    //__asm("wfi");
    if (i < sizeof(ssd1306_init)) {
      buf_push(ssd1306_init[i]); 
    } else {
      buf_push(0x55);
    }
  }

}
THREAD(disp, i2c_write, 2, 32, 0, 0, 0, 0);
