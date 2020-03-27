[org 0x7c00]                   ; Load the code into memory at 0x7c00

    ;mov bx, welcome             
    ;call print

    ;mov dx, 0x6869             Set the value we want to print to dx
    ;call print_hex              Print the hex value
    ;mov bx, goodbye
	;call print
    mov [BOOT_DRIVE], dl
    mov bp, 0x8000
    mov sp, bp

    mov bx, 0x9000
    mov dh, 5
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov dx, [0x9000 + 512]
    call print_hex
    
    mov dx, [0x9000]
    call print_hex
    
    jmp $                           ; Jump to current address - forever


%include "print_string.asm"
%include "print_hex.asm"
%include "disk_load.asm"

BOOT_DRIVE:  db 0

    ;; welcome:db "Welcome to YNOS!", 0

    ;; goodbye:db "Goodbye!", 0call print
    
    times 510-($-$$) db 0
    dw 0xaa55
    
    times 256 dw 0xdada
    times 256 dw 0xface    
