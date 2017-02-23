[GLOBAL gdt_flush]    ; Allows the C code to call gdt_flush().

gdt_flush:
   mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
   mov ds, ax        ; Load all data segment selectors
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush2   ; 0x08 is the offset to our code segment: Far jump!
.flush2:
   ret