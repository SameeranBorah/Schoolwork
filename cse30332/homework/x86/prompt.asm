;John Lake
;x86 Daily 9

BITS 16
%define BUFLOC 2fh

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
	mov si, promptString
	call print
	mov di, BUFLOC       ;Set the di location to the buffer location
.loop:		
	mov ah, 0 
	int 16h  	;Get keyboard input
	stosb		;Store whatever is in AL in DI

	cmp al, 13 	;If there is a carriage return, go to newline
	je .newline

	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h		
	jmp .loop	;Loop back and let the user type again

.newline:		
			;Here, we will check if bufloc is equal to e, c, h, and o

	mov ah, 0Eh     ;Set mode to teletype
	mov al, 0Dh	;Print a carriage return and a newline:
	int 10h
	mov al, 0Ah
	int 10h
;	mov di, 0h	
;	mov si, BUFLOC  ;Move the words at BUFLOC into si
;	call print
;	mov di, BUFLOC

	mov si, promptString
	call print
	jmp .loop	;Go back to the loop


print:
	mov ah, 0Eh 	;Set up teletype mode
.loop:			;Loop so that you can print each char
	lodsb		;Get value from SI and put it in AL
	cmp al, 0h	;Check if there is a null char, and quit if there is. 
	je .exit
	int 10h		;Issue an interrupt so that you can display the character. 
	jmp .loop	;Loop through each character in the word
.exit:			;When you're done with the loop, go here so you can return to where the IP was before print.
	ret

	

promptString db '--$ '


times 510-($-$$) db 0	; fill remainder of sector with zeros
dw 0xAA55		; BIOS looks for AA55 at the end of the sector
