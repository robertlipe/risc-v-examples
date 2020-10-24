
include common.mk

# required For the memory layout of Qemu's 'virt'.
CFLAGS += -mcmodel=medany

bootimage: boot.o main.o Makefile
	$(LD) $(LDFLAGS) -T kernel.ld -o bootimage boot.o main.o
	$(OBJDUMP) --disassemble bootimage > bootimage.dis
	$(NM) bootimage -sg > bootimage.sym

run:
	@echo "In another terminal, run gdb."
	@echo "To regain control here, <ctrl>A, then <c> to quit."
	qemu-system-riscv64 -machine virt -bios none \
	-kernel bootimage -m 3G -nographic \
	-drive file=/tmp/fs.img,if=none,format=raw,id=x0 \
	-device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 \
	-S -gdb tcp::25505



clean:
	rm -f bootimage *.o *.dis *.sym

-include *.d
