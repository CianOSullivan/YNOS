print:
    pusha
    mov al, [bx]    ; Move memory contents at bx to al
    cmp al, 0
    je stop
    mov ah, 0xe                    
    int 0x10
    add bx, 1
    call print

stop:
    popa
    ret