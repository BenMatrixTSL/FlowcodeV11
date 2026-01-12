/* CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE63A7B1B482DE23EA0098F24A8EA4F2D01B476235DC84385ECD78EEA432C1CB15DDCA398A47C6AE994ABC7D8F6F499E8CED9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF569FD7407517200A8B735BD2D0C6400AD6FE27C28E827345A75C8DB6A44A27DCDE7573567D709CED87F1D650A18D26EDCEFFB6524A8C1E80B7236C36EA72C099EBC9221C7AEE8DB846E54CA6CC2E08B2DBEAB9478B11D6A579758EFE42C9857D7634165C2A8716C46A1F4D7AB7D080D287726C07C89336E017E0891B16C3AB1D1B75B7955E2A3F925 */
/* REVISION: 1.0 */
/* GUID: 4A5BF831-EB45-4D78-87A1-9E74D02AEC6B */
/* DATE: 08\08\2022 */
/* DIR: FCD\ARM\link\stm32f_ccm16.ld */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;;      /* required amount of heap  */
_Min_Stack_Size = 0x400;; /* required amount of stack */

MEMORY
{
FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = _ROMSIZE
RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = _RAMSIZE
CCMRAM (rw)     : ORIGIN = 0x10000000, LENGTH = 16K
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
