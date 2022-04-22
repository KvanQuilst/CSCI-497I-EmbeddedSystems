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

/* Ch 7, Table 56 (pg. 75) */
extern struct {
  volatile unsigned PIO2_6;
  volatile unsigned PADDING0;
  volatile unsigned PIO2_0;
  volatile unsigned RESET_PIO0_0;
  volatile unsigned PIO0_1;
  volatile unsigned PIO1_8;
  volatile unsigned PADDING1;
  volatile unsigned PIO0_2;
  volatile unsigned PIO2_7;
  volatile unsigned PIO2_8;
  volatile unsigned PIO2_1;
  volatile unsigned PIO0_3;
  volatile unsigned PIO0_4;
  volatile unsigned PIO0_5;

  struct {
    volatile unsigned FUNC  : 3;
    volatile unsigned MODE  : 2;
    volatile unsigned HYS   : 1;
    volatile unsigned       : 4;
    volatile unsigned OD    : 1;
    volatile unsigned       : 21;
  } PIO1_9;

  volatile unsigned PIO3_4;
  volatile unsigned PIO2_4;
  volatile unsigned PIO2_5;
  volatile unsigned PIO3_5;
  volatile unsigned PIO0_6;
  volatile unsigned PIO0_7;
  volatile unsigned PIO2_9;
  volatile unsigned PIO2_10;
  volatile unsigned PIO2_2;
  volatile unsigned PIO0_8;
  volatile unsigned PIO0_9;
  volatile unsigned SWCLK_PIO0_10;
  volatile unsigned PIO1_10;
  volatile unsigned PIO2_11;

  /* Table 85, (pg. 94) */
  struct {
    volatile unsigned FUNC    : 3;
    volatile unsigned MODE    : 2;
    volatile unsigned HYS     : 1;
    volatile unsigned         : 1;
    volatile unsigned ADMODE  : 1;
    volatile unsigned         : 2;
    volatile unsigned OD      : 1;
    volatile unsigned         : 21;
  } R_PIO0_11;

  volatile unsigned R_PIO1_0;
  volatile unsigned R_PIO1_1;
  volatile unsigned R_PIO1_2;
  volatile unsigned PIO3_0;
  volatile unsigned PIO3_1;
  volatile unsigned PIO2_3;
  volatile unsigned SWDIO_PIO1_3;
  volatile unsigned PIO1_4;
  volatile unsigned PIO1_11;
  volatile unsigned PIO3_2;
  volatile unsigned PIO1_5;
  volatile unsigned PIO1_6;
  volatile unsigned PIO1_7;
  volatile unsigned PIO3_3;
  volatile unsigned SCK_LOC;
  volatile unsigned DSR_LOC;
  volatile unsigned DCD_LOC;
  volatile unsigned RI_LOC;
} IOCON;

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
struct tmr16 {

  /* Table 282 (pg. 338) */
  struct {
    volatile unsigned MR0 : 1;
    volatile unsigned MR1 : 1;
    volatile unsigned MR2 : 1;
    volatile unsigned MR3 : 1;
    volatile unsigned CR0 : 1;
    volatile unsigned     : 27;
  } IR;

  /* Table 283 (pg. 338) */
  struct {
    volatile unsigned CE  : 1;
    volatile unsigned CR  : 1;
    volatile unsigned     : 30;
  } TCR;

  volatile unsigned TC;

  /* Table 285 (pg. 339) */
  struct {
    volatile unsigned PR  : 16;
    volatile unsigned     : 16;
  } PR;

  volatile unsigned PC;

  /* Table 287 (pg. 340) */
  struct {
    volatile unsigned MR0I  : 1;
    volatile unsigned MR0R  : 1;
    volatile unsigned MR0S  : 1;
    volatile unsigned MR1I  : 1;
    volatile unsigned MR1R  : 1;
    volatile unsigned MR1S  : 1;
    volatile unsigned MR2I  : 1;
    volatile unsigned MR2R  : 1;
    volatile unsigned MR2S  : 1;
    volatile unsigned MR3I  : 1;
    volatile unsigned MR3R  : 1;
    volatile unsigned MR3S  : 1;
    volatile unsigned       : 20;
  } MCR;

  /* Table 288 (pg. 341) */
  struct {
    volatile unsigned MATCH : 16;
    volatile unsigned       : 16;
  } MR0;

  /* Table 288 (pg. 341) */
  struct {
    volatile unsigned MATCH : 16;
    volatile unsigned       : 16;
  } MR1;

  volatile unsigned MR2;
  volatile unsigned MR3;
  volatile unsigned CCR;

  volatile unsigned CR0;

  volatile unsigned PADDING0[3];
  volatile unsigned EMR;
  volatile unsigned PADDING1[12];
  volatile unsigned CTCR;

  /* Table 294 (pg. 344) */
  struct {
    volatile unsigned PWMEN0  : 1;
    volatile unsigned PWMEN1  : 1;
    volatile unsigned PWMEN2  : 1;
    volatile unsigned PWMEN3  : 1;
    volatile unsigned         : 28;
  } PWMC;
};

extern struct tmr16 TMR16B1;

/* Ch 25, Table 363 (pg. 410) */
extern struct {

  /* Table 364 (pg. 411) */
  /*struct {
    volatile unsigned SEL     : 8;
    volatile unsigned CLKDIV  : 8;
    volatile unsigned BURST   : 1;
    volatile unsigned CLKS    : 3;
    volatile unsigned         : 4;
    volatile unsigned START   : 3;
    volatile unsigned EDGE    : 1;
    volatile unsigned         : 4;
  } CR;*/
  volatile unsigned CR;

  volatile unsigned GDR; 
  volatile unsigned PADDING0;

  /* Table 366 (pg. 413) */
  struct {
    volatile unsigned ADINTEN   : 8;
    volatile unsigned ADGINTEN  : 1;
    volatile unsigned           : 23;
  } INTEN;

  /* Table 367 (pg. 413) */
  struct {
    volatile unsigned         : 6;
    volatile unsigned V_VREF  : 10;
    volatile unsigned         : 14;
    volatile unsigned OVERRUN : 1;
    volatile unsigned DONE    : 1;
  } DR0;
  
  volatile unsigned DR1; 
  volatile unsigned DR2; 
  volatile unsigned DR3; 
  volatile unsigned DR4; 
  volatile unsigned DR5; 
  volatile unsigned DR6; 
  volatile unsigned DR7; 
  volatile unsigned STAT; 
} ADC;

/* Ch 28, Table 443 (pg. 508) */
extern struct {
  volatile unsigned SETENA;
} ISER;
