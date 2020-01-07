    [org 0x7c00]                   ; Load the code into memory at 0x7c00

    mov bx, welcome
    call print

    mov dx, 0x6869                  ; Set the value we want to print to dx
    call print_hex                  ; Print the hex value
    mov bx, goodbye
    call print
    jmp $                           ; Jump to current address - forever


    %include "print_string.asm"
    %include "print_hex.asm"

HEX_OUT: db '0x0000', 0

welcome:
    db "Welcome to YNOS!", 0

goodbye:
    db "Goodbye!", 0

    
    
    times 510-($-$$) db 0
    dw 0xaa55