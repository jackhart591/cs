TITLE Assignment1     (Assignment1.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified:
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: 1
	Due Date: 1/16/22
	Description: 
&

INCLUDE Irvine32.inc

ASCII_ADJUST = 48

.data

	title_str	BYTE		"Calculator Program, By Jackson Hart", 13, 0
	num1_str	BYTE		"Please enter your first number: ", 0
	num2_str	BYTE		"Please enter your second number: ", 0
	sum_str	BYTE		"Sum = ", 0
	diff_str	BYTE		"Difference = ", 0
	quot_str	BYTE		"Quotient = ", 0
	rem_str	BYTE		"Remainder = ", 0

	num1		DWORD	?
	num2		DWORD	?

	sum		DWORD	?
	diff		DWORD	?
	quotient	DWORD	?
	remainder	DWORD	?

	temp		DWORD	?

.code
main PROC

; Write title of program to user
	mov	edx,	OFFSET title_str
	call	WriteString
	call	Crlf

; Ask for the first number
	mov	edx, OFFSET num1_str
	call	WriteString
	call ReadInt
	mov	num1, eax

; Ask for the second number
	mov	edx, OFFSET num2_str
	call	WriteString
	call ReadInt
	mov	num2, eax

; Calculate
	add	eax, num1
	mov	sum, eax	; num1 + num2
	
	mov	eax, num1
	sub	eax, num2	; num1 - num2
	mov	diff, eax

	mov	edx, 0
	mov	eax, num1
	div	num2		; num1 / num2
	mov	quotient, eax
	mov	remainder, edx

; Display Values
	; Need to read this part somewhere


	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
