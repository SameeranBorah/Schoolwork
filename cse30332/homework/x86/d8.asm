;John Lake
;x86 Daily 8

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
	cld		; clear direction flag for lodsb, end of prelude

	mov si, thestring	; point the register SI to the string that
					; we want to print
	call print	; the call instruction causes the CPU to execute
			; instructions at the given label until
			; the ret instruction is hit
			; call puts the current instruction pointer on
			; the stack before it goes to the label
			; ret restores the instruction pointer by
			; reading it from the stack

	jmp $	; loop until the power goes out


; start of procedure print
print:
	mov ah, 0Eh 	;Set up teletype mode
.loop:			;Loop so that you can print each char
	lodsb         	;Load whatever is in si to al
	cmp al, 0h	;Check if there is a null char, and quit if there is. 
	je .exit
	int 10h		;Issue an interrupt so that you can display the character. 
	jmp .loop	;Loop through each character in the word
.exit:			;When you're done with the loop, go here so you can return to where the IP was before print.
	ret
; end of procedure print

;; END OF PROCEDURE AREA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; START OF DATA AREA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

thestring db 'John Lake', 0

;; END OF DATA AREA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

times 510-($-$$) db 0	; fill remainder of sector with zeros
dw 0xAA55		; BIOS looks for AA55 at the end of the sector

