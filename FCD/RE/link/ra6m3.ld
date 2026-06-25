/* CRC: E8D8BA6B01C86C3AC01705C895CD4B8E143B46B2337721088F71DB8F0B027625DCF35EF5FAD318B984DDDD6E93D7D404A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15C49E8BAC40A4F9810AF0A187FA77CAE7A7F860E0EFABDF17EF7D2E5571C88DB5427A9C579B16E366E47EB66C432E16CCEFDF1ED7CF6211936051AE80582A001614C8922195D6C0C9D55EC15358C26E6FAE2053CD77566BF89758EFE42C9857D7AEE1AA73604F5055E1C81E5E3BB6EE2AC9DE72A096C8E0F7E4565E63FDA312627DD474674123A97D */
/* REVISION: 1.0 */
/* GUID: E4F5A6B7-C8D9-0123-4567-890123456789 */
/* DATE: 25\06\2026 */
/* DIR: FCD\RE\link\ra6m3.ld */
/* RA6M3: 2MB Flash at 0x00000000, 640KB RAM (0x1FFE0000 SRAM+TCM) */

_Min_Heap_Size  = 0x1000;
_Min_Stack_Size = 0x2000;

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = _ROMSIZE
  RAM   (xrw) : ORIGIN = 0x1FFE0000, LENGTH = _RAMSIZE
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

ENTRY(Reset_Handler)

SECTIONS
{
  .isr_vector : { . = ALIGN(4); KEEP(*(.isr_vector)) . = ALIGN(4); } >FLASH
  .text : { . = ALIGN(4); *(.text) *(.text*) KEEP(*(.init)) KEEP(*(.fini)) . = ALIGN(4); _etext = .; } >FLASH
  .rodata : { . = ALIGN(4); *(.rodata) *(.rodata*) . = ALIGN(4); } >FLASH
  _sidata = LOADADDR(.data);
  .data : { . = ALIGN(4); _sdata = .; *(.data) *(.data*) . = ALIGN(4); _edata = .; } >RAM AT> FLASH
  . = ALIGN(4);
  .bss : { _sbss = .; __bss_start__ = _sbss; *(.bss) *(.bss*) *(COMMON) . = ALIGN(4); _ebss = .; __bss_end__ = _ebss; } >RAM
  ._user_heap_stack : { . = ALIGN(4); PROVIDE(end = .); PROVIDE(_end = .); . = . + _Min_Heap_Size; . = . + _Min_Stack_Size; . = ALIGN(4); } >RAM
  /DISCARD/ : { libc.a(*) libm.a(*) libgcc.a(*) }
  .ARM.attributes 0 : { *(.ARM.attributes) }
}
