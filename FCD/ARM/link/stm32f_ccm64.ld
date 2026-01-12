/* CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE63A7B1B482DE23EA0098F24A8EA4F2D01B5DA2CB1AC3C76E0250026D86731C7044A9DD6E4E5997679117EA65F766A92ED79A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF54B1469A6525D4F35E0C677663F8E6440973EDA7C727C64D3277520FDA660134A07846AC4276DFDC8A6A97BF8134119C0BC0CCF31AE711E034E8550286488EE20A19209233F0DFEA5175348F583400EDC996E98D9D59BFDE49758EFE42C9857D73E330AA22325371A166FF7CDE1598561A8F2A9A2D939B7A2F0B9F6FEC6D77E3F44FB7D5555DAC58F */
/* REVISION: 1.0 */
/* GUID: E903ABB9-308A-4AC4-89FD-336C23445734 */
/* DATE: 08\08\2022 */
/* DIR: FCD\ARM\link\stm32f_ccm64.ld */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;;      /* required amount of heap  */
_Min_Stack_Size = 0x400;; /* required amount of stack */

MEMORY
{
FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = _ROMSIZE
RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = _RAMSIZE
CCMRAM (rw)     : ORIGIN = 0x10000000, LENGTH = 64K
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
