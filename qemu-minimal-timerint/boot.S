# Simple startup for RISC-V

#include "riscv_encoding.h"

.data
dead_counter: .word 0 # How long have we been dead?
past_main_text:

.text
.global _start
_start:
  // Disable interrupts until they are safe to handle.
  csrc CSR_MSTATUS, MSTATUS_MIE

  // Load the initial stack and general pointer values defined in *.ld.
  la   sp, _sp
  la   gp, _gp

  li   a0, 0
  li   a1, 0
  li   a2, 0
  call _premain # falls though
  call main # falls though to a tragic end.

# We've exited from main. Crash.
# WFI is a "hint" opcode. If implemented, we wait for an
# interrupt. if not, it is a NOP.
  la a0, past_main
  call panic

.globl dead
dead:
  li t1, 1
  la t0, dead_counter
  lw t1,(t0)
still_dead:
  addi t1, t1, 1
  sw t1, 0(t0)
  wfi
  j still_dead

