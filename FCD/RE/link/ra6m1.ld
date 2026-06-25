/* CRC: E8D8BA6B01C86C3AC01705C895CD4B8E143B46B2337721088F71DB8F0B0276255E75C93662E0FBB3DE30F07728859BDDA54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E155518EE67E1650E82C2555A0130C929C536DA43A440E873F7CD621D15B65E627117B57D45A259743659F6477ED97A70598A351BCB2BAA7FF08E88DE8813F4F18DACAFAB88B6F1AF5843DF262F1C9598076877F6D0E9D2E5A89758EFE42C9857D72294DA512CBFD56E74C314A081FC23B0577A6CBDF56DA445FC0E9FB60DFEAB887A64FF5F89231504 */
/* REVISION: 1.0 */
/* GUID: C2D3E4F5-A6B7-8901-2345-678901234567 */
/* DATE: 25\06\2026 */
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
