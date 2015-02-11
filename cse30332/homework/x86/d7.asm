BITS 16

start:
                        ; this is the prelude, where we set up the data
                        ; and stack segments
        cli             ; turn off interrupts while setting up DS and SS
        mov ax, 07C0h   ; recall that 07C0h is where the bootloader starts
                        ; so, that is the start of the data segment (DS)
        mov ds, ax      ; move AX into DS because we can't set DS directly
                        ; that's all we need to do for the data segment...
                        ; ...now we need to set up the stack
                        ; to do that, we move forward by 512 bytes (the
                        ; size of this bootloader) to get a starting point
                        ; for the stack.
                        ; to do that, we want the stack segment (SS register)
                        ; to point to the end of the bootloader, which is
                        ; the data segment start (07C0h) plus the size of the
                        ; the bootloader.
                        ; but, segments are addressed in multiples of 16
                        ; (called "paragraphs"), so we actually add 512/16=
        add ax, 0020h   ; 32, which is 0020 in hex
        mov ss, ax      ; set the stack segment to 07E0h (07C0h + 0020h)
        mov sp, 1000h   ; set the stack pointer to 4096 bytes (1000h)
                        ; remember that this will grow *down*, towards SS
        sti             ; turn the interrupts back on
	
	;Set graphics mode:
	mov ah, 0h
	mov al, 13h
	int 10h

	;J:
	mov ah, 0Eh
	mov al, 4Ah
	mov bh, 0h
	mov bl, 01h
	int 10h

	;F:
	mov ah, 0Eh
	mov al, 46h
	mov bh, 0h
	mov bl, 0Ch
	int 10h

	;L:
	mov ah, 0Eh
	mov al, 4Ch
	mov bh, 0h
	mov bl, 04h
	int 10h

	jmp $

	times 510-($-$$) db 0
	dw 0xAA55	; BIOS looks for AA55 at the end of the sector
