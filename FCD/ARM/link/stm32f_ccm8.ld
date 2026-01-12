/* CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE63A7B1B482DE23EA0098F24A8EA4F2D01B2D66C113A9B27923B44598A78BC517E4A75D7D23FE11B0A74E4F4569EB07AB699A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF57F0394C7453393C1C88838BD6758F31AFB0DF8EFA89034C20EEE0D08A4EFB60DAB22C3E4A5924AA3085E9DA405E880F5B85C606AF541BCB8CF690E3D1811C44A233346122AF8FF21D8805925F0481CF14765A18146B2F0509758EFE42C9857D734F699332B399EE706B8F2BDDCE52FF19E8A106B732F051B3D4904234D2DB8FF0968D0215FCB1380 */
/* REVISION: 1.0 */
/* GUID: 89FE0FCA-FE0E-4A9C-8407-274619455B05 */
/* DATE: 08\08\2022 */
/* DIR: FCD\ARM\link\stm32f_ccm8.ld */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;;      /* required amount of heap  */
_Min_Stack_Size = 0x400;; /* required amount of stack */

MEMORY
{
FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = _ROMSIZE
RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = _RAMSIZE
CCMRAM (rw)     : ORIGIN = 0x10000000, LENGTH = 8K
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
