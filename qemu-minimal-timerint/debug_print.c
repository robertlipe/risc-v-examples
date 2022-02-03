// This is a super simple and small debug print. Its useful on embedded
// parts where kilobytes matter. This doesn't do floating point or offer
// much control over spacing. It's definitly NOT ISO C printf. If you need
// "real" printf, you need a full libc.

#include <stdarg.h>

static void puthex(unsigned char c) {
  static char hex[] = "0123456789abcdef";
  putc(hex[(c >> 4)]);
  putc(hex[c & 0xf]);
}

static puthexi(int i) {
    puthex(i >> 24);
    puthex(i >> 16);
    puthex(i >> 8);
    puthex(i);
}

#if 0
puthexl(long l) {
  puthexi(l >> 32);
  puthexi(l & 0xffffffff);
}
#endif

// TODO: decide if recursion is reasonable in our tiny interrupt stack.
putdec(int d) {
  if (d < 0) {
    putc('-');
      d = -d;
  }
  if (d >= 10) {
    print_i(d / 10);
  }
  putc(d % 10 + '0');
}
