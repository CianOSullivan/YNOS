[org 0x7c00]                   ; Load the code into memory at 0x7c00
    mov bp, 0x9000
    mov sp, bp
    mov bx, MSG_REAL_MODE
    call print

    call switch_to_pm
    
    jmp $                           ; Jump to current address forever - shouldn't execute


%include "print_string.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_pm.asm"


[bits 32]

BEGIN_PM:    ; This is where we arrive after switching to and initialising protected mode.

    mov ebx , MSG_PROT_MODE
    call print_string_pm; Use our 32 - bit print routine.
                                
    jmp $ ; Hang.



; Global variables
MSG_REAL_MODE db "Started in 16bit Real Mode ", 0
MSG_PROT_MODE db "Successfully landed in 32bit Protected Mode " , 0
    
times 510-($-$$) db 0
dw 0xaa55
 
