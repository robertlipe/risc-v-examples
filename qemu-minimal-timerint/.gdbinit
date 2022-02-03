# set arch riscv:rv32
# GDB civilities and quality-of-life
display/i $pc
# This can be a bit much if you're not debugging assembly.
# Our example has very little assemly, so it's not so useful.
# set disassemble-next-line on
# don't ask if I'm sure when I |q|.
define hook-quit
  set confirm off
end

# Reboot the image by resetting the program counter to start of execution.
define restart
  target extended-remote localhost:25505
  p $pc = &_start
end

file bootimage
b panic
target extended-remote localhost:25505
