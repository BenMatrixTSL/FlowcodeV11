/* CRC: 0000000000000000000000000000000000000000000000000000000000000000 */
/* REVISION: 1.0 */
/* GUID: C2D3E4F5-A6B7-8901-2345-678901234567 */
/* DATE: 22\06\2026 */
/* DIR: FCD\RE\link\ra6m1.ld */
/* RA6M1: 256KB Flash at 0x00000000, 32KB RAM at 0x20000000 */

_Min_Heap_Size  = 0x400;
_Min_Stack_Size = 0x800;

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = _ROMSIZE
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = _RAMSIZE
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
