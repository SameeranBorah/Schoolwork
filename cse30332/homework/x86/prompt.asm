;John Lake
;x86 Command Prompt
;For this assignment, I chose a nice prompt to make things interesting.

BITS 16
%define BUFLOC 201h

start:
	; here's our prelude of setting up the data and stack sections
        cli
        mov ax, 07C0h
        mov ds, ax
	mov es, ax
        add ax, 0020h
        mov ss, ax
        mov sp, 1000h
        sti
	;End of prelude

	call prompt		; Call prompt, the main function
	jmp $			; loop until the power goes out



;The actual function for the command prompt: 
prompt:
	mov si, promptString 
	call print		;print the first prompt
	mov di, BUFLOC       	;Set the di location to the buffer location
	jmp .loop
.loop:		
	call getChar	
	cmp al, 13 	;If there is a carriage return, go to newline
	je .newline
	call checkEcho
	
.endOfLoop:
	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h		
	jmp .loop	;Loop back and let the user type again
.newline:		
	mov ah, 0Eh     ;Set mode to teletype
	mov al, 0Dh	;Print a carriage return and a newline:
	int 10h
	mov al, 0Ah
	int 10h

	mov si, promptString ;Print the prompt
	call print
	jmp .loop



;Check and see if the echo command has been given
checkEcho: 
	cmp al, 65h 	;Check for "e"
	jne prompt.endOfLoop
	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h		

	call getChar  	;Check for "c"
	cmp al, 63h
	jne prompt.endOfLoop
	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h		

	call getChar 	;Check for "h"
	cmp al, 68h
	jne prompt.endOfLoop
	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h		

	call getChar	;Check for "o"
	cmp al, 6Fh
	jne prompt.endOfLoop
	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h		

	call getChar	;Check for a space afterwords
	cmp al, 20h
	jne prompt.endOfLoop
	mov ah, 0Eh     ;Otherwise, print the character to the user.
	int 10h	

	call echo
	jmp prompt.newline


;Simple function to read characters typed into AL
getChar:
	mov ah, 0 	;set video mode
	int 16h  	;Get keyboard input
	ret		





;Function for echo
echo:
	mov di, BUFLOC  ;Reset di to read everthing after "echo"
.loopEcho:
	call getChar	;continuously get characters and store them in di
	stosb
	cmp al, 13 	;If there is a carriage return, finish and print
	je .print
	
	mov ah, 0Eh     ;Otherwise, print the character to the user and loop
	int 10h	
	jmp .loopEcho
.print:
	mov ah, 0Eh     ;Set mode to teletype
	mov al, 0Dh	;Print a carriage return and a newline:
	int 10h
	mov al, 0Ah
	int 10h

	mov al, 0	;Append a null byte to the end of di
	stosb		
	mov si, BUFLOC  ;Move the words at BUFLOC into si
	call print
	jmp .done

.done:
	ret


;Print function to print words stored in si
print:
	mov ah, 0Eh 	;Set up teletype mode
.loop:			;Loop so that you can print each char
	lodsb		;Get value from SI and put it in AL
	cmp al, 0	;Check if there is a null char, and quit if there is. 
	je .exit
	int 10h		;Issue an interrupt so that you can display the character. 
	jmp .loop	;Loop through each character in the word
.exit:			;When you're done with the loop, go here so you can return to where the IP was before print.
	ret

	
;Prompt string
promptString db '[you@mini-os-]$ '


times 510-($-$$) db 0	; fill remainder of sector with zeros
dw 0xAA55		; BIOS looks for AA55 at the end of the sector

