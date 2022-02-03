// A timer demonstration for the simplest RISC-V hardware timer.
// It would be perfectly valid to split this file into a -32 and -64 bit
// version, but for education's sake, it's helpful to see the two in
// forced proximity.

#include <assert.h>

// 02000000 CLINT
// 0c000000 PLIC

#define CLINT 0x02000000
#define RISCV_MTIMECMP_ADDR (0x2000000 + 0x4000) // Both are 64-bi registers.
#define RISCV_MTIME_ADDR    (0x2000000 + 0xBFF8)

#if ( __riscv_xlen == 64)
  typedef unsigned long uint64_t;
  typedef long uint32_t;
#else
  typedef unsigned long long uint64_t;
  typedef long uint32_t;
#endif

inline uint64_t get_mtime() {
#if ( __riscv_xlen == 64)
    // On a 64-bit arch, reading a 64-bit register is easy.
    return *(volatile uint64_t *)(RISCV_MTIME_ADDR);
#else
    volatile uint32_t* mtimel = (volatile uint32_t*)(RISCV_MTIME_ADDR);
    volatile uint32_t* mtimeh = (volatile uint32_t*)(RISCV_MTIME_ADDR+4);

    uint32_t mtime_hi;
    uint32_t mtime_lo;
    do {
      mtime_hi = *mtimeh;
      mtime_lo = *mtimel;
        // Poll mtimeh to ensure it's consistent after reading mtimel
        // The frequency of mtimeh wrapping over is low, so this
        // loops rarely.
    } while (mtime_hi != *mtimeh);

    return (uint64_t) ((((uint64_t) mtime_hi)<<32) | mtime_lo);
#endif
}

inline void set_mtimecmp(uint64_t i) {
#if ( __riscv_xlen == 64)
  *(uint64_t *) (RISCV_MTIMECMP_ADDR) = i;
#else
 // Store a dummy high byte to prevent clock from running backward during
 // this non-atomic write.
 *(volatile int *)(RISCV_MTIMECMP_ADDR+4) = 0xffffffff;
 *(volatile int *)(RISCV_MTIMECMP_ADDR) = i & 0xffffffff;
 *(volatile int *)(RISCV_MTIMECMP_ADDR+4) = i >> 32;
#endif
}

void rearm_timer() {
  set_mtimecmp(get_mtime() + 0x1000*5000);
}
