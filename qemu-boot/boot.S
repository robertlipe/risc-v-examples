
#include "riscv_encoding.h"

.data
idle_counter:
.word 0

.text
.global _start
_start:
  // Disable interrupts until they are needed.
  csrc CSR_MSTATUS, MSTATUS_MIE
  // Load the initial stack pointer value.
  la   sp, _sp

  li   a0, 0
  li   a1, 0
  jal main

# We've exited from main. Just loop.
# WFI is a "hint" opcode. If implemented, we wait for an.
# interrupt. if not, it is a NOP.
.globl dead
dead:
  li t1, 1
  la t0, idle_counter
  # add t0, (t0), t1
  sw t0, (t0)
  wfi
  j dead
