/* CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE63A7B1B482DE23EA0098F24A8EA4F2D01BE1E91ECB9454A15707F0CF08D42C2ABD9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51AA8012C327A6060C08AA2F9AE4F66AD2CB227E1E5F83175C6F45D2E0405E2A20085A59A123E2B62D37518FFFCA206B3212F3B79A3ACCC968AAB4160451A0A6243D66071BC0823F9B714654FE8B8F5F63A7312EFF420337E9758EFE42C9857D79CA77944B8339745569A70D9E954A46F687D4568165AB1569931EA1D1140CCEE68CC0CC191075369 */
/* REVISION: 1.0 */
/* GUID: 46A7402C-1F71-4FBB-BCAE-F88F18675CA5 */
/* DATE: 08\08\2022 */
/* DIR: FCD\ARM\link\stm32f.ld */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;;      /* required amount of heap  */
_Min_Stack_Size = 0x400;; /* required amount of stack */

MEMORY
{
FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = _ROMSIZE
RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = _RAMSIZE
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
