/* CRC: E8D8BA6B01C86C3AC01705C895CD4B8E7DB21B6A5C0446411EF7D3B5F1CF2E3EA4410C8AD5ACFB354B46E1BE780F5386A82A31B710B61CEB8677019667BFA6E1A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E1543C55CA5A67D640542D4F7C55DEA7C9A267A91D80697BDF9D7888C7D0D684FA9D97FB9F873E53FB5C8314C8128507569CF8CAB5E50367192753BD7527F51BE9289C3EA3649420342FA7545FFF73C0DCB708EECE5E88D5A149758EFE42C9857D719D704268F40A1E3EB8B9E812E37DF7E098B6C11C2E5B98E11F33536FF4271682E83591212429612 */
/* REVISION: 1.0 */
/* GUID: E3F4A5B6-C7D8-9012-6789-123456789012 */
/* DATE: 25\06\2026 */
/* DIR: FCD\RE\link\ra4m1_boot.ld */

/*
 * Renesas RA4M1 Linker Script (Arduino Uno R4 bootloader offset)
 * App starts at 0x00008000 (after 32KB bootloader area).
 * Flash: 256KB total, app uses 224KB from offset 0x8000
 * RAM:    32KB at 0x20000000
 *
 * Program using DFU (bossac/dfu-util) over USB from bootloader.
 */

_Min_Heap_Size  = 0x200;
_Min_Stack_Size = 0x400;

/* Bootloader occupies 0x00000000-0x00007FFF (32KB) */
_BOOT_SIZE = 0x8000;

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x00008000, LENGTH = _ROMSIZE - _BOOT_SIZE
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
