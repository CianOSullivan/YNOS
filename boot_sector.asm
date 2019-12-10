    [org 0x7c00]                ; Load the code into memory at 0x7c00

    mov bx, welcome             ; Set bx to welcome string
    call print_string           ; Print welcome
    ;; mov dx, 0x1fb6
    ;; call print_hex
    mov bx, goodbye             ; Set bx to goodbye string
    call print_string           ; Print goodbye
    jmp $                       ; Jump to current address - forever

    %include "print.asm"

welcome:
    db "Welcome to YNOS!", 0

goodbye:
    db "Goodbye!", 0

    times 510-($-$$) db 0       ; Pad boot sector with 0s
    dw 0xaa55                   ; Magic number
