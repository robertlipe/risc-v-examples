This is approximately the simplest code I could think of that demonstrates
booting a RISC-V core, configuring it to handle interrupts and exceptions,
and starting a repeating timer just to demonstrates how it all works. It's a
goal to do it with as little assembly as possible. At this writing, it's about
forty commmented lines of .S and no inline asms hidden in the C.

It works in both 32 and 64-bit versions under QEMU, the excellent CPU emulator.
The whole pile comes in around 250 lines of code and mostly borrowed from my
other projects.

This is the "hello world" of RISC-V interrupts.

Usage:
$ make run

Then, from another shell start riscv64-unknown-elf-gdb in that directory so
you pick up the .gdbrc that's there. It will connect to the running instance and provide you with some creature comforts. The riscv64 gdb will work on both 32
and 64 bit executables.

riscv-encoding.h came from someplace on github wihout a copyright. Since it all
statement of facts and not expression, I doubt it's copyrightable anyway. Everything
else is mine.


--
Robert Lipe