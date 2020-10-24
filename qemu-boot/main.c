extern char _sbss;
extern char _ebss;

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

// There is a full debug UART provided by the Qemu Virt VM. We use only
// the very simplest part of it and because it's fake, we don't have to
// even init baud rates and such. The TX register is conveniently at address
// 0 of the UART, so we can write to it and have it appear on the screen.
#define VIRT_UART 0x10000000
void console_puts(char* message) {
  while (*message) {
    *(volatile char*) VIRT_UART = *message++;
  }
}

int main(int argc, char* argv[], char* envp[]) {
  our_memset(&_sbss, 0, &_ebss - &_sbss);

  console_puts("Hello, world.");

  return;
}
