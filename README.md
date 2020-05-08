# ProjectDelta

This is a 32-bit custom OS project built from scratch using C and assembly language.

# Dependencies
Running this code requires the following:

    * GCC Cross Compiler - Instructions for this can be found on the [OS Dev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler). The target platform is i686-elf.
    * NASM - Assembly language used for the bootloader.
    * QEMU - Virtual machine software used to boot the OS.

# Running
To run the OS, open a terminal and enter:

```
    git clone https://github.com/CianOSullivan/ProjectDelta
```

Then:

```
    cd ProjectDelta
    make
    ./ynos
```

And the OS should be running in a QEMU window!
