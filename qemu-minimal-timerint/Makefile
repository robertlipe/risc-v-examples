
all: bootimage

BITS=64  # Valid Values are 32 or 64

include common.mk
include *.d

# mcmodel required For the memory layout of Qemu's 'virt'.
CFLAGS += -O3 -g3 -mcmodel=medany -nostdlib -ffreestanding
# If you value performance of every opcode or need opcodes to look source
# instead of honking on the stack pointer ($sp), uncomment
# CFLAGS += -fomit-frame-pointer

# CFLAGS+=-march=rv32i -mabi=ilp32 -mcmodel=medany
# ASFLAGS+=-march=rv32i -mabi=ilp32 -mcmodel=medany
# LDFLAGS+=-march=rv32i -mabi=ilp32 -mcmodel=medany

OBJS += boot.o timer.o trap.o main.o platform.o debug_print.o

bootimage: Makefile $(OBJS)
	$(LD) $(LDFLAGS) -T kernel.ld -o bootimage $(OBJS)
	$(OBJDUMP) --disassemble bootimage > bootimage.dis
	$(NM) bootimage -sg > bootimage.sym

run: bootimage
	@echo "In another terminal, run gdb."
	@echo "To regain control here, <ctrl>A, then <c> to quit."
	$(QEMU) -machine virt -bios none \
	-kernel bootimage -m 3G -nographic \
	-S -gdb tcp::25505

clean:
	rm -f bootimage *.o *.dis *.sym *.d

-include *.d
