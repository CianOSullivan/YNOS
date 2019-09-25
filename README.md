# ProjectDelta

Cian's custom OS project

# Boot Sector
To assemble boot sector into machine code:  
   `$ nasm boot_sector.asm -f bin -o boot_sector.bin`

To run os:  
   `$ qemu-system-x86_64 boot_sector.bin`