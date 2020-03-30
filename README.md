# ProjectDelta

Cian's custom OS project

# Boot Sector
To assemble boot sector into machine code:
   `$ nasm boot_sector.asm -f bin -o boot_sector.bin`

To run os:
   `$ qemu-system-x86_64 -drive format=raw,file=boot_sector.bin,index=0,if=floppy`

# Resources
Good example of how to build a terminal in the kernel: https://wiki.osdev.org/Bare_Bones#Implementing_the_Kernel  
A more fleshed out kernel: https://wiki.osdev.org/Meaty_Skeleton#Architecture_Directories  
Good resource for interrupt handling: https://littleosbook.github.io/  

