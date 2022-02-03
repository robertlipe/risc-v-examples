// Platform-specific code. Could be used to shim printing to a UART or
// semihosting or something.
// This is for QEMU -machine virt -bios none -nographic

#include "riscv_encoding.h"

#define VIRT_UART 0x10000000

void putc(char c) {
    *(volatile char*) VIRT_UART = c;
}

void puts(char* message) {
  while (*message) {
    putc(*message++);
  }
}

// Called before main() to get the environment set up and sane.

void _premain() {
  extern void panic(const char* msg) __attribute__((noreturn));
  static int premain_called;
  if (premain_called++) {
    panic("PANIC: _premain called multiple times");
  }

  // We have to zero our globals that aren't initialized.
  extern char _sbss; // provided by linker script.
  extern char _ebss;
  our_memset(&_sbss, 0, &_ebss - &_sbss);

  puts("Arming Interrupts.");

  // Where does the processor go on a trap? *mtvec.
  extern void trap(void);
  write_csr(mtvec, trap);

  write_csr(mie, 1 << IRQ_M_TIMER); // Enable timer for INTR specifically.
  write_csr(mstatus, MSTATUS_MIE); // Enable global interrupts.

  // In this case, it's badly name. It's "arm timer" the first time.
  extern void rearm_timer();
  rearm_timer();
}
