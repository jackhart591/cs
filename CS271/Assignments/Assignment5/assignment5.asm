TITLE Assignment 5     (assignment5.asm)

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

RAND_LOW	EQU		100
RAND_HI		EQU		999
USER_LOW	EQU		15
USER_HI		EQU		200

PARAM_A		EQU		[ebp+8]

.data

	title_str		BYTE		"Sorting Random Integers", 0
	author_str		BYTE		"By Jackson Hart", 0
	intro_str		BYTE		"This program generates random numbers in the range [100 ... 999],", 10, \
								"displays the original list, sorts the list, and calculates the median value.", 10, \
								"Finally, it displays the list sorted in descending order.", 0
	number_prompt	BYTE		"How many numbers should be generated? [15 ... 200]: ", 0
	invalid_str		BYTE		"Invalid input, try again!", 0

	num_ints		DWORD		?

.code
main PROC

	call	Intro
	push	num_ints
	call	GetData
	pop		num_ints

	exit	; exit to operating system
main ENDP

COMMENT &
	Description: Displays program intro
	Recieves: none
	Returns: none
	Pre-conditions: none
	Post-Conditions: none
	Registers Changed: none
&
Intro PROC
	push	edx

	mov		edx, OFFSET title_str
	call	WriteString
	call	Crlf

	mov		edx, OFFSET author_str
	call	WriteString
	call	Crlf

	mov		edx, OFFSET intro_str
	call	WriteString
	call	Crlf

	pop		edx
	ret
Intro ENDP

GetData PROC
	push	ebp
	mov		ebp, esp
	push	edx
	push	eax

Top_A:
	mov		edx, OFFSET number_prompt
	call	WriteString
	call	ReadDec

	cmp		eax, USER_LOW
	jl		NotValid
	cmp		eax, USER_HI
	jg		NotValid
	jmp		ValidInput

NotValid:
	mov		edx, OFFSET invalid_str
	call	WriteString
	call	Crlf
	jmp		Top_A

ValidInput:
	mov		PARAM_A, eax
	
	pop		eax
	pop		edx
	pop		ebp
	ret
GetData ENDP

FillArray PROC

	ret
FillArray ENDP

ExchangeElems PROC

	ret
ExchangeElems ENDP

SortList PROC

	ret
SortList ENDP

DisplayMedium PROC

	ret
DisplayMedium ENDP

DisplayList PROC

	ret
DisplayList ENDP


END main
