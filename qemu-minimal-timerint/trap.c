
#include "riscv_encoding.h"

void trap (void) __attribute__ ((interrupt ("machine")));
#pragma GCC optimize ("align-functions=4")

extern rearm_timer(void);

long interrupt_count;

// if the reason for the panic() is a blown stack pointer, this panic
// -- indeed, any written in C -- is going to have a baad time. This also
// means that $a0 is clobbered (by msg) and the system may otherwise be
// perturbed.
void panic(const char* msg) {
  puts(msg);
  putc('\n');
}

static interrupt(int intr) {
  switch(intr) {
    case IRQ_M_TIMER: // Machine Mode Timer
      rearm_timer();
      interrupt_count++;
      puts(" T");
      break;
    default:
      panic("Unexpected synchronous exception.");
  }
}

static exception(int cause) {
  // Handle types as listed in DECLARE_CAUSE.
  panic("Unexpected exception");
}

void trap(void) {
  long cause = read_csr(mcause);
  // MSTATUS_SD is always the top bit in the (32/64 bit) word. _SD is set
  // via preprocessing voodoo in riscv_encoding.h.
  if (cause & MSTATUS_SD) {
    interrupt(cause & 0xff);
  } else {
    exception(cause & 0xffff);
  }
}

const char past_main[] = "PANIC: fell off the end of main()";