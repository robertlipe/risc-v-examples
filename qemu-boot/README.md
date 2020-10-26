This is a an example of how to get from boot to a reasonable C environment
in the Qemu "virt" system for RISC-V. Everything is in one directory, not
because that's a great way to organize a large product, but to simplify that
this is EVERYTHING going on.

This code isn't particularly interesting. There are a zillion "hello world"
examples around. This project demonstrates all the integration of all
the various fiddly startup files so you can write your own code in 
assembler or C and run it on the awesome QEMU virtual hardware. While RISC-V
hardware can be inexpensive, the convenience of debugging on a full
system from the comfort of your laptop, without cables, and a full screen
and even emulated disk and network is quite nice.

A full debug environment is provided. The program halts at startup so you
can single step from the beginning, without hardware probes. You can 
use https://en.wikibooks.org/wiki/QEMU/Monitor or normal GDB commands 
to see registers, set breakpoints, inspect local or global variables, etc.

robertlipe@Roberts-MacBook-Pro qemu-boot % make run
echo "In another terminal, run gdb."
In another terminal, run gdb.
echo "To regain control here, <ctrl>A, then <c> to quit."
To regain control here, <ctrl>A, then <c> to quit.
qemu-system-riscv64 -machine virt -bios none \
	-kernel bootimage -m 3G -nographic \
	-drive file=/tmp/fs.img,if=none,format=raw,id=x0 \
	-device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 \
	-S -gdb tcp::25505
Hello, world.

robertlipe@Roberts-MacBook-Pro qemu-boot % gdb
[ jabber ] 
Breakpoint 1 at 0x8000005e: file main.c, line 28.
Breakpoint 2 at 0x80000014
(gdb) c
Continuing.

Breakpoint 1, main (argc=0, argv=0x0, envp=0x1028) at main.c:28
28	int main(int argc, char* argv[], char* envp[]) {
(gdb) n
29	  our_memset(&_sbss, 0, &_ebss - &_sbss);
(gdb)
31	  console_puts("Hello, world.");
(gdb)
33	  return;
(gdb) c
Continuing.

Breakpoint 2, 0x0000000080000014 in dead ()
=> 0x0000000080000014 <dead+0>:	73 00 50 10	wfi



It's quite a bit different than the GD32V as we'll see soon.
