    [org 0x7c00]                   ; Load the code into memory at 0x7c00

    ;; mov al, 'H'                 ; Assign H to lower part of ax
    ;; int 0x10                    ; Interrupt with code 0x10
    ;; mov al, 'E'                 ; Assign H to lower part of ax
    ;; int 0x10
    ;; mov al, 'L'
    ;; int 0x10
    ;; int 0x10
    ;; mov al, 'O'                 ; Assign H to lower part of ax
    ;; int 0x10                    ;

    mov bx, welcome
    call print
    mov bx, goodbye
    call print
    jmp $                       ; Jump to current address - forever

print:
    pusha
    mov al, [bx]
    cmp al, 0
    je stop
    mov ah, 0xe                    
    int 0x10
    add bx, 1
    call print

stop:
    popa
    ret

welcome:
    db "Welcome to YNOS!", 0

goodbye:
    db "Goodbye!", 0


    times 510-($-$$) db 0

    dw 0xaa55
