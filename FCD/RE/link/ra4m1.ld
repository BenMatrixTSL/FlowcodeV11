/* CRC: E8D8BA6B01C86C3AC01705C895CD4B8E7DB21B6A5C0446411EF7D3B5F1CF2E3E5E75C93662E0FBB3DE30F07728859BDDA54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15138B192425D50851BBE6DAAC22F97A982D17269267E900F5023FF945ADD6006401AFE7EF52291F2176251151352E0094DA2CAA03D3B9D9207744801899080DD78E431E7446B56F8ED501D6877C495332720A2CBED9E00DE99758EFE42C9857D74B4933E3EF4A6950253983A2DACDE6120EE4E76152752223674573756A3EC60527D03AB401F1B0EB */
/* REVISION: 1.0 */
/* GUID: D2E3F4A5-B6C7-8901-5678-012345678901 */
/* DATE: 25\06\2026 */
/* DIR: FCD\RE\link\ra4m1.ld */

/*
 * Renesas RA4M1 Linker Script (bare-metal, J-Link / SWD programming)
 * Flash: 256KB at 0x00000000
 * RAM:    32KB at 0x20000000
 *
 * _ROMSIZE and _RAMSIZE are passed from the compiler batch as linker --defsym.
 * This matches the stm32f.ld pattern used by STARM.
 */

_Min_Heap_Size  = 0x200;
_Min_Stack_Size = 0x400;

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = _ROMSIZE
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = _RAMSIZE
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
    KEEP(*(.init))
    KEEP(*(.fini))
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

  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE(end = .);
    PROVIDE(_end = .);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM

  /DISCARD/ :
  {
    libc.a(*)
    libm.a(*)
    libgcc.a(*)
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
