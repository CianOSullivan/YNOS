print_string:
    pusha                       ; Push all registers to stack
    mov al, [bx]                ; Set al to memory contents of bx
    cmp al, 0                   ; If null terminator reached
    je stop                     ; Stop printing
    mov ah, 0xe                 ; BIOS teletype output
    int 0x10                    ; Interrupt - Print character in al
    add bx, 1                   ; Iterate through characters
    call print_string           ; Print character at next position

print_hex:
    ;; make hex temp = dw
    mov bx, HEX_TEMP
    call print_string

stop:
    popa                        ; Pop all registers from stack
    ret                         ; Return to call point

HEX_TEMP:
    db "0x0000", 0
