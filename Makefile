# Automatically generate lists of sources using wildcards
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# Default make target
all: os-image

# This is the actual disk image that the computer loads,
# which is the combination of our compiled bootsector and kernel
os-image: boot/boot_sector.bin kernel.bin
			cat $^ > os-image

# This builds the binary of our kernel from two object files:
# - the kernel_entry, which jumps to kmain() in our kernel
# - the compiled C kernel
kernel.bin : boot/kernel_entry.o ${OBJ}
			ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to an object file
# For simplicity, C files depend on all header files
%.o: %.c ${HEADERS}
			gcc -ffreestanding -c $< -o $@

# Assemble the kernel_entry .
%.o: %.asm
			nasm $< -f elf64 -o $@

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
%.bin: %.asm
			nasm $< -f bin -I 'boot/' -o $@

# Clear away all generated files
clean:
			rm -fr *.bin *.dis *.o os-image
			rm -fr kernel/*.o boot/*.bin drivers/*.o

# Disassemble our kernel for debugging
kernel.dis: kernel.bin
			ndisasm -b 32 $< > $@
