OUTPUT_ARCH( "riscv" )
ENTRY( _start )

/* The 'virt' virtual machine is super simple. No ROM relocations or pain. */
MEMORY
{
  RAM   (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 1K;

  /* Group all the immutable (code, unchanged data) together */
  .text :
  {
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.srodata .srodata.*)
  } >RAM   

  . = ALIGN(4);

  .data :
  {
    PROVIDE(_sdata = .);
    PROVIDE(_gp = . + 0x800);
    *(.sdata .sdata.*) *(.data .data.*)
    PROVIDE(_edata = .);
  }

  /* Shove all the zero-initialized sections together. */
  .bss :
  {
    PROVIDE(_sbss = .);
    *(.sbss*)
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    PROVIDE(_ebss = .);
  } >RAM

  . = ALIGN(8);
  PROVIDE( _end = . );

  /* Stack, as in most every system, is at the top of RAM and grows down. */
  .stack ORIGIN(RAM) + LENGTH(RAM) - __stack_size :
  {
    PROVIDE( _heap_end = . );
    . = __stack_size;
    PROVIDE( _sp = . );
  } >RAM
}
