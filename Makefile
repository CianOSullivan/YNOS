# Default make target
all: os-image

# This is the actual disk image that the computer loads,
# which is the combination of our compiled bootsector and kernel
os-image: boot_sector.bin kernel.bin
			cat $^ > os-image

# This builds the binary of our kernel from two object files:
# - the kernel_entry, which jumps to kmain() in our kernel
# - the compiled C kernel
kernel.bin : kernel_entry.o kernel.o
			ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

# Build the kernel object file
kernel.o : kernel.c
			gcc -ffreestanding -c $< -o $@

# Build our kernel entry object file
kernel_entry.o : kernel_entry.asm
			nasm $< -f elf64 -o $@

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
boot_sector.bin: boot_sector.asm
			nasm $< -f bin -o $@

# Clear away all generated files
clean:
			rm -fr *.bin *.dis *.o os-image

# Disassemble our kernel for debugging
kernel.dis: kernel.bin
			ndisasm -b 32 $< > $@
