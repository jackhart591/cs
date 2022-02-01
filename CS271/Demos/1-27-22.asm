TITLE Jan 27 2022    (1-27-22.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified:
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number:
	Due Date:
	Description: 
&

INCLUDE Irvine32.inc

.data

intro_str		BYTE		"Enter a lower limit and and upper limit, and I'll show the summation of ints from lower to upper", 0
lower_str		BYTE		"Gimme lower: ", 0
upper_str		BYTE		"Gimme upper: ", 0
result_str	BYTE		"The summation from lower to upper is ", 0


lower_lim		DWORD	?
upper_lim		DWORD	?

.code
main PROC

	call intro
	call getData
	call calculate
	call showResults

	exit	; exit to operating system
main ENDP

COMMENT &
	Description: function desc
	Recieves: recieves which registers/vars to change
	Returns: returns what registers/vars that have been changed
	Preconditions: what needs to be true beforehand
	Registers Changed: self explanatory dumb dumb
&
intro PROC
	mov		edx, OFFSET intro_str
	call		WriteString
	call		Crlf
	ret
intro ENDP

getData PROC
	mov		edx, OFFSET lower_str
	call		WriteString
	call		ReadInt
	mov		lower_lim, eax
	mov		edx, OFFSET upper_str
	call		WriteString
	call		ReadInt
	mov		upper_lim, eax
	ret
getData ENDP

calculate PROC
	mov		ecx, upper_lim
	sub		ecx, lower_lim
	inc		ecx				; iterations: ecx = upper - lower + 1
	mov		eax, 0			; accumulator
Loopers:
	add		eax, lower_lim
	inc		lower_lim
	loop		Loopers
	ret
calculate ENDP

showResults PROC
	mov		edx, offset result_str
	call		WriteString
	call		WriteDec
	ret
showResults ENDP

END main
