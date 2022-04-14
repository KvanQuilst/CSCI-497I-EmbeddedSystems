/* Ch 3, Table 21 */
extern struct { 
  volatile const unsigned SYS       : 1;
  volatile const unsigned ROM       : 1;
  volatile const unsigned RAM       : 1;
  volatile const unsigned FLASHREG  : 1;
  volatile const unsigned FLASHARRAY: 1;
  volatile const unsigned I2C       : 1;
  volatile const unsigned GPIO      : 1;
  volatile const unsigned CT16B0    : 1;
  volatile const unsigned CT16B1    : 1;
  volatile const unsigned CT32B0    : 1;
  volatile const unsigned CT32B1    : 1;
  volatile const unsigned SSP0      : 1;
  volatile const unsigned UART      : 1;
  volatile const unsigned ADC       : 1;
  volatile const unsigned           : 1;
  volatile const unsigned WDT       : 1;
  volatile const unsigned IOCON     : 1;
  volatile const unsigned CAN       : 1;
  volatile const unsigned SSP1      : 1;
  volatile const unsigned           : 10;
  volatile const unsigned           : 0;
} SYSABHCLKCTRL;

/* Ch 12, Table 173 (pg. 192) */
struct gpio {
  volatile unsigned DATA[1<<12];
  volatile unsigned PADDING[4096];
  volatile unsigned GDIR;
  volatile unsigned IS;
  volatile unsigned IBE;
  volatile unsigned IEV;
  volatile unsigned IE;
  volatile unsigned RIS;
  volatile unsigned MIS;
  volatile unsigned IC;
};

extern struct gpio GPIO0;
extern struct gpio GPIO1;
