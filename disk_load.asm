    ;; Load DH sectors to ES:BX from drive DL

disk_load:
    push dx                     ; Store DX on stack so we can laterrecall how many sectors were
                                ; requested to be read, even if it is altered
    mov ah, 0x2
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13

    jc disk_error               ; Jump if carry bit set

    pop dx
    cmp dh, al
    jne disk_error
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print
    jmp $


DISK_ERROR_MSG  db "Disk read error!", 0
