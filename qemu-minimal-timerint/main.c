
#include "riscv_encoding.h"

// This isn't really simpler than doing it in the startup code. It's just
// an example/reminder that you have no libc and tending your startup really
// is your own responsibility.
// This is also so we have an "interesting" loop to look at in the generated
// assembly.
void* our_memset(void* start, int data, int len) {
  unsigned char* p = start;
  while(len--) {
    *p++ = (unsigned char)data;
  }
  return start;
}

static int foreground_count;

int main(int argc, char* argv[], char* envp[]) {
  while(1) {
    if ((foreground_count & 0xfffff) == 0) {
      putc('f');
    }
    foreground_count++;
  }

  return;
}
