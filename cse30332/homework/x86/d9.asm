;John Lake
;x86 Daily 9

BITS 16

start:
	; here's our prelude of setting up the data and stack sections
        cli
        mov ax, 07C0h
        mov ds, ax
        add ax, 0020h
        mov ss, ax
        mov sp, 1000h
        sti
	;End of prelude

	call prompt	
	jmp $	; loop until the power goes out

prompt:
.loop:		
	mov ah, 0 
	int 16h  	;Get keyboard input
	cmp al, 13 	;If there is a carriage return, go to newline
	je .newline
	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h		
	jmp .loop	;Loop back and let the user type again
.newline:		
	mov ah, 0Eh     ;Set mode to teletype
	mov al, 0Dh	;Print a carriage return and a newline:
	int 10h
	mov al, 0Ah
	int 10h
	jmp .loop	;Go back to the loop
	




times 510-($-$$) db 0	; fill remainder of sector with zeros
dw 0xAA55		; BIOS looks for AA55 at the end of the sector

