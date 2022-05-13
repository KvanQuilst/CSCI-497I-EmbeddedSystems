MEMORY {
  flash (rx) : org = 0x00000000, len = 32k
  sram (rwx) : org = 0x10000000, len = 4k
}

ENTRY(vector);

SECTIONS {
  
  .text : {
    . = 0x00000000;
    *(.vector);
    . = ALIGN(4);
    *(.text);
    . = ALIGN(4);
  } > flash

  .init_array : {
    *(.init_array);
  } > flash

  .rodata : {
    *(.rodata);
    . = ALIGN(4);
    __THREADS = .;
    *(.threads);
    LONG(0);
    . = ALIGN(4);
  } > flash

  .data : {
    . = 0x00000000;
    *(.data);
    . = ALIGN(4);
  } > sram AT > flash

  .bss : {
    *(.bss);
    . = ALIGN(4);
  } > sram

	__DATA_LMA = LOADADDR(.data);
	__DATA_VMA = ADDR(.data);
	__DATA_END = ADDR(.data) + SIZEOF(.data);
	__BSS_VMA = ADDR(.bss);
	__BSS_END = ADDR(.bss) + SIZEOF(.bss);
  __INIT_ARRAY_VMA = LOADADDR(.init_array);
  __INIT_ARRAY_END = ADDR(.init_array) + SIZEOF(.init_array);
}

PROVIDE(__INITIAL_SP = ORIGIN(sram) + LENGTH(sram));
PROVIDE(__VECTOR_CHECKSUM = 0 - __INITIAL_SP - (__reset + 1) - (__irq + 1)
                          - (Hardfault + 1));

PROVIDE(SYSCON = 0x40048000);
PROVIDE(IOCON = 0x40044000);

PROVIDE(GPIO0 = 0x50000000);
PROVIDE(GPIO1 = 0x50010000);

PROVIDE(TMR16B1 = 0x40010000);
PROVIDE(ADC = 0x4001C000);
PROVIDE(ISER = 0xE000E100);
