/* CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE63A7B1B482DE23EA0098F24A8EA4F2D01B5B6FC3E7DD275CC616D1B51CF1FE6E81A75D7D23FE11B0A74E4F4569EB07AB699A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5B24443CE13D8EFE72295B53495526E293203C4EE1F743DEF5B7626695DC8A05CEFA9CD1B5F8182BAFBED2D077438039473E554543ED8408813223D85D279668AA48EEE7F28E4CD4CF696F5715619E0BF7919932010DB1DE09758EFE42C9857D707DCBA0363080D56721A6400DE3551922595AC8E51F0176376D3E34736BD7539F516F4BDFF4A1CBE */
/* REVISION: 1.0 */
/* GUID: B367FC67-C71A-42A0-8593-FBA41307402A */
/* DATE: 08\08\2022 */
/* DIR: FCD\ARM\link\stm32f_ccm4.ld */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;;      /* required amount of heap  */
_Min_Stack_Size = 0x400;; /* required amount of stack */

MEMORY
{
FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = _ROMSIZE
RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = _RAMSIZE
CCMRAM (rw)     : ORIGIN = 0x10000000, LENGTH = 4K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

ENTRY(Reset_Handler)

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  _sidata = LOADADDR(.data);

  .data : 
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .;
  } >RAM AT> FLASH

  _siccmram = LOADADDR(.ccmram);
  
  .ccmram :
  {
    . = ALIGN(4);
    _sccmram = .;       /* create a global symbol at ccmram start */
    *(.ccmram)
    *(.ccmram*)
    
    . = ALIGN(4);
    _eccmram = .;       /* create a global symbol at ccmram end */
  } >CCMRAM AT> FLASH

  . = ALIGN(4);
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM
  
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
