MEMORY {
  flash (rx) : org = 0x00000000, len = 32k
  sram (rwx) : org = 0x10000000, len = 4k
}

ENTRY(vector);

SECTIONS {
  
  .text : {
    . = 0x00000000;
    *(vector);
    . = ALIGN(4);
    *(.text);
    . = ALIGN(4);
  } > flash

  .rodata : {
    *(.rodata);
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
}


PROVIDE(__INITIAL_SP = ORIGIN(sram) + LENGTH(sram));
PROVIDE(__VECTOR_CHECKSUM = 0
                          - __INITIAL_SP
                          - (__reset + 1)
                          - (NMI + 1)
                          - (Hardfault + 1));
PROVIDE(SYSABHCLKCTRL = 0x40048080);

PROVIDE(GPIO0 = 0x50000000);
PROVIDE(GPIO1 = 0x50010000);
