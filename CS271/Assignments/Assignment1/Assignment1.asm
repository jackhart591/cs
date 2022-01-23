TITLE Assignment1     (Assignment1.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified:
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: 1
	Due Date: 1/16/22
	Description: This program reads two numbers from the user, and outputs the 
			   sum, difference, quotient, and remainder.
&

INCLUDE Irvine32.inc

ASCII_ADJUST = 48

.data

	title_str	BYTE		"Calculator Program, By Jackson Hart", 13, 0
	ec_str	BYTE		"**EC: This program verifies the second number is less than the first AND squares both numbers.", 0
	intro_str	BYTE		"Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder.", 0
	num1_str	BYTE		"Please enter your first number: ", 0
	num2_str	BYTE		"Please enter your second number: ", 0
	big_str	BYTE		"Your second number can't be bigger than your first...", 0
	add_str	BYTE		" + ", 0
	sub_str	BYTE		" - ", 0
	prod_str	BYTE		" * ", 0
	div_str	BYTE		" / ", 0
	rem_str	BYTE		" remainder ", 0
	sqr_str	BYTE		"^2", 0
	equal_str	BYTE		" = ", 0
	farewell	BYTE		"Bye-Bye!", 0

	num1		DWORD	?
	num2		DWORD	?

	sum		DWORD	?
	diff		DWORD	?
	product	DWORD	?
	quotient	DWORD	?
	remainder	DWORD	?
	sqr_1	DWORD	?
	sqr_2	DWORD	?

	temp		DWORD	?

.code
main PROC

; Write title of program to user
	mov	edx,	OFFSET title_str
	call	WriteString
	call	Crlf

; Output introduction
	mov	edx, OFFSET ec_str
	call	WriteString
	call	Crlf

	mov	edx, OFFSET intro_str
	call	WriteString
	call	Crlf

; Ask for the first number
	mov	edx, OFFSET num1_str
	call	WriteString
	call ReadInt
	mov	num1, eax

; Ask for the second number
SECOND:
	mov	edx, OFFSET num2_str
	call	WriteString
	call ReadInt
	mov	num2, eax

; Error check second number
	cmp	num1, eax
	jae	NEXT
	mov	edx, OFFSET big_str
	call	WriteString
	call	Crlf
	jmp SECOND

; Calculate
NEXT:
	add	eax, num1
	mov	sum, eax	; num1 + num2
	
	mov	eax, num1
	sub	eax, num2	; num1 - num2
	mov	diff, eax

	mov	eax, num1
	mul	num2		; num1 * num2
	mov	product, eax

	mov	edx, 0
	mov	eax, num1
	div	num2		; num1 / num2
	mov	quotient, eax
	mov	remainder, edx

	mov	eax, num1
	mul	num1		; num1^2
	mov	sqr_1, eax

	mov	eax, num2
	mul	num2		; num2^2
	mov	sqr_2, eax

; Display Values

	; Sum
	mov	edx, OFFSET add_str
	mov	eax, num1
	call WriteInt				
	call WriteString			; Num1 + ...

	mov	eax, num2
	mov	edx, OFFSET equal_str	; ...Num2 = ...
	call	WriteInt
	call	WriteString

	mov	eax, sum
	call	WriteInt				; ...Sum
	call Crlf

	; Difference
	mov	eax, num1
	mov	edx, OFFSET sub_str
	call	WriteInt
	call	WriteString			; Num1 - ...

	mov	eax, num2
	mov	edx, OFFSET equal_str
	call	WriteInt
	call	WriteString			; ...Num2 = ...

	mov	eax, diff
	call	WriteInt				; ...Diff
	call	Crlf

	; Product
	mov	eax, num1
	mov	edx, OFFSET prod_str
	call	WriteInt
	call	WriteString			; Num 1 * ...

	mov	eax, num2
	mov	edx, OFFSET equal_str
	call	WriteInt
	call	WriteString			; ...Num2 = ...

	mov	eax, product
	call	WriteInt
	call	Crlf

	; Quotient / Remainder
	mov	eax, num1
	mov	edx, OFFSET div_str
	call	WriteInt
	call	WriteString			; Num1 / ...

	mov	eax, num2
	mov	edx,	OFFSET equal_str
	call	WriteInt
	call	WriteString			; Num2 = ...

	mov	eax, quotient
	mov	edx, OFFSET rem_str
	call	WriteInt
	call	WriteString			; Quotient remainder ...

	mov	eax, remainder
	call	WriteInt				; remainder
	call	Crlf

	; Num1^2
	mov	eax, num1
	mov	edx, OFFSET sqr_str
	call	WriteInt
	call	WriteString			; Num1^2...

	mov	edx, OFFSET equal_str
	mov	eax, sqr_1
	call	WriteString
	call	WriteInt				; ... = sqr_1
	call	Crlf

	; Num2^2
	mov	eax, num2
	mov	edx, OFFSET sqr_str
	call	WriteInt
	call	WriteString			; Num2^2...

	mov	edx, OFFSET equal_str
	mov	eax, sqr_2
	call	WriteString
	call	WriteInt				; ... = sqr_2
	call	Crlf

	mov	edx,	OFFSET farewell
	call	WriteString

	exit	; exit to operating system
main ENDP

END main
