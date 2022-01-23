TITLE 1-18-22     (1-18-22.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified: 1/18/22
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Description: Gets two integers from the user and calculates the summation of the integers
			   from the first to the second
&

INCLUDE Irvine32.inc

.data

	prompt_1	BYTE		"Enter lower limit: ", 0
	prompt_2	BYTE		"Enter upper limit: ", 0
	low_limit	DWORD	?
	up_limit	DWORD	?

.code
main PROC

; Get numbers from user

	mov		edx, OFFSET prompt_1
	call		WriteString
	call		ReadInt
	mov		low_limit, eax

	mov		EDX, OFFSET prompt_2
	call		WriteString
	call		ReadInt
	mov		up_limit, eax

; Data validation: swap low_limit and up_limit if low > up

	cmp		low_limit, eax
	jle		inputOk
	mov		ebx, low_limit
	xchg		eax, ebx
	mov		low_limit, ebx
	mov		up_limit, eax

; Do calculation

inputOk:
	; Set up accumulator (eax)
	mov		eax, 0
	mov		ebx, low_limit

	; Set up the counter: up_limit - low_limit + 1 (ecx)
	mov		ecx, up_limit
	sub		ecx, low_limit
	inc		ecx

	; Loop body
top:
	add		eax, ebx
	inc		ebx
	loop		top

; Print the result
	call		WriteDec

	exit	; exit to operating system
main ENDP

END main
