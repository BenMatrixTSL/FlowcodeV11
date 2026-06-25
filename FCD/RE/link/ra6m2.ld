/* CRC: E8D8BA6B01C86C3AC01705C895CD4B8E143B46B2337721088F71DB8F0B027625A65F0DF805534A5A360B650001EC7F5CA54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15FA96C1F486979985610A7D468A8B65F8DFFE2206409BBF73CDC238E9FB47028EFC921B5FB0E2BA3F172D5AC4F271A6600D5B95C4273E96B2B2724DC9BB937394CB728E224ED01CAC3F6621F1E72156331526368DDF0BF7029758EFE42C9857D725878B46801FA838A2043822D91DABFCE8BE0EA32704ACB96FF949B8D8BFAD15599C160227117CAC */
/* REVISION: 1.0 */
/* GUID: D3E4F5A6-B7C8-9012-3456-789012345678 */
/* DATE: 25\06\2026 */
/* DIR: FCD\RE\link\ra6m2.ld */
/* RA6M2: 1MB Flash at 0x00000000, 128KB RAM at 0x20000000 */

_Min_Heap_Size  = 0x800;
_Min_Stack_Size = 0x1000;

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
