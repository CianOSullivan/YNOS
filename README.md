# ProjectDelta

Cian's custom OS project

# Boot Sector
To assemble boot sector into machine code:  
   `$ nasm boot_sector.asm -f bin -o boot_sector.bin`

To run os:  
   `$ qemu-system-x86_64 -drive format=raw,file=boot_sector.bin`


Finished base implementation of 3.5.1 so start reading from 3.6
You got this, 3.6 is a new section, looks manageable and interestings.