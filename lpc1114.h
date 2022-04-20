/* Ch 3, Table 7 (pg. 26) */
/* SYSCON */
extern struct {
  volatile unsigned SYSMEMREMAP;
  volatile unsigned PRESETCTRL;

  /* Table 10 (pg. 28) */
  struct {
    volatile unsigned MSEL  : 5;
    volatile unsigned PSEL  : 2;
    volatile unsigned       : 25; 
  } SYSPLLCTRL;
  //volatile unsigned SYSPLLCTRL;

  /* Table 11 (pg. 29) */
  struct {
    volatile unsigned LOCK  : 1;
    volatile unsigned       : 31;
  } SYSPLLSTAT;

  volatile unsigned PADDING0[4];
  volatile unsigned SYSOSCCTRL;
  volatile unsigned WDTOSCCTRL;
  volatile unsigned IRCCTRL;
  volatile unsigned PADDING1;
  volatile unsigned SYSRSTSTAT;
  volatile unsigned PADDING2[3];

  /* Table 16 (pg. 31) */
  struct {
    volatile unsigned SEL : 2;
    volatile unsigned     : 30;
  } SYSPLLCLKSEL;

  /* Table 17 (pg. 32) */
  struct {
    volatile unsigned ENA : 1;
    volatile unsigned     : 31;
  } SYSPLLCLKUEN;

  volatile unsigned PADDING3[10];

  /* Table 18 (pg. 32) */
  struct {
    volatile unsigned SEL : 2;
    volatile unsigned     : 30;
  } MAINCLKSEL;

  /* Table 19 (pg. 33) */
  struct {
    volatile unsigned ENA : 1;
    volatile unsigned     : 31;
  } MAINCLKUEN;

  volatile unsigned SYSAHBCLKDIV;
  volatile unsigned PADDING4;

  /* Table 21 (pg. 33) */
  struct { 
    volatile unsigned SYS       : 1;
    volatile unsigned ROM       : 1;
    volatile unsigned RAM       : 1;
    volatile unsigned FLASHREG  : 1;
    volatile unsigned FLASHARRAY: 1;
    volatile unsigned I2C       : 1;
    volatile unsigned GPIO      : 1;
    volatile unsigned CT16B0    : 1;
    volatile unsigned CT16B1    : 1;
    volatile unsigned CT32B0    : 1;
    volatile unsigned CT32B1    : 1;
    volatile unsigned SSP0      : 1;
    volatile unsigned UART      : 1;
    volatile unsigned ADC       : 1;
    volatile unsigned           : 1;
    volatile unsigned WDT       : 1;
    volatile unsigned IOCON     : 1;
    volatile unsigned CAN       : 1;
    volatile unsigned SSP1      : 1;
    volatile unsigned           : 10;
    volatile unsigned           : 0;
  } SYSAHBCLKCTRL;

  volatile unsigned PADDING5[4];
  volatile unsigned SSP0CLKDIV;
  volatile unsigned UARTCLKDIV;
  volatile unsigned SSP1CLKDIV;
  volatile unsigned PADDING6[12];
  volatile unsigned WDTCLKSEL;
  volatile unsigned WDTCLKUEN;
  volatile unsigned WDTCLKDIV;
  volatile unsigned PADDING7;
  volatile unsigned CLKOUTCLKSEL; 
  volatile unsigned CLKOUTUEN;
  volatile unsigned CLKOIUTCLKDIV;
  volatile unsigned PADDING8[5];
  volatile unsigned PIOPORCAP0;
  volatile unsigned PIOPORCAP1;
  volatile unsigned PADDING9[18];
  volatile unsigned BODCTRL;
  volatile unsigned SYSTCKCAL;
  volatile unsigned PADDING10[6];
  volatile unsigned IRQLATENCY;
  volatile unsigned NMISRC;
  volatile unsigned PADDING11[34];
  volatile unsigned STARTAPRP0;
  volatile unsigned STARTERP0;
  volatile unsigned STARTRSRP0CLR;
  volatile unsigned STARTSRP0;
  volatile unsigned PADDING12[8];
  volatile unsigned PDSLEEPCFG;
  volatile unsigned PDAWAKECFG;

  /* Table 44 (pg. 44) */
  struct {
    volatile unsigned IRCOUT_PD : 1;
    volatile unsigned IRC_PD    : 1;
    volatile unsigned FLASH_PD  : 1;
    volatile unsigned BOD_PD    : 1;
    volatile unsigned ADC_PD    : 1;
    volatile unsigned SYSOSC_PD : 1;
    volatile unsigned WDTOSC_PD : 1;
    volatile unsigned SYSPLL    : 1;
    volatile unsigned           : 24;
  } PDRUNCFG;

  volatile unsigned PADDING13[111];
} SYSCON;

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

/* Ch 18, Table 281 (pg. 337) */
extern struct {
  volatile unsigned IR;
  volatile unsigned TCR;
  volatile unsigned TC;
  volatile unsigned PR;
  volatile unsigned PC;
  volatile unsigned MCR;
  volatile unsigned MR0;
  volatile unsigned MR1;
  volatile unsigned MR2;
  volatile unsigned MR3;
  volatile unsigned CCR;
  volatile unsigned CR0;
  volatile unsigned PADDING0[3];
  volatile unsigned EMR;
  volatile unsigned PADDING1[12];
  volatile unsigned CTCR;
  volatile unsigned PWMC;
} TMR16B1;
