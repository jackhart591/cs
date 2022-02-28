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

RAND_LOW		EQU		100
RAND_HI			EQU		999
USER_LOW		EQU		15
USER_HI			EQU		200

PARAM_A			EQU		[ebp+8]
PARAM_B			EQU		[ebp+12]
PARAM_C			EQU		[ebp+16]

LOCAL_A			EQU		[ebp-4]
LOCAL_B			EQU		[ebp-8]

SPACE_CHAR		EQU		20h
NUM_PER_LINE	EQU		10

.data

	intro_str		BYTE		"Sorting Random Integers", 10, 13, \
								"By Jackson Hart", 10, 13, \
								"This program generates random numbers in the range [100 ... 999],", 10, 13, \
								"displays the original list, sorts the list, and calculates the median value.", 10, 13, \
								"Finally, it displays the list sorted in descending order.", 0
	number_prompt	BYTE		"How many numbers should be generated? [15 ... 200]: ", 0
	invalid_str		BYTE		"Invalid input, try again!", 0

	num_ints		DWORD		0
	num_arr			DWORD		USER_HI DUP(?)

.code
main PROC
	
	push	OFFSET intro_str
	call	Intro

	push	OFFSET invalid_str
	push	OFFSET number_prompt
	push	OFFSET num_ints
	call	GetData

	mov		eax, num_ints
	push	num_ints
	push	OFFSET num_arr
	call	FillArray

	push	OFFSET num_arr
	push	num_ints
	call	DisplayList


 	exit										; exit to operating system
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
	push	ebp
	mov		ebp, esp
	push	edx

	mov		edx, PARAM_A
	call	WriteString
	call	Crlf

	pop		edx
	pop		ebp
	ret		4
Intro ENDP

GetData PROC
	push	ebp
	mov		ebp, esp
	push	eax
	push	edx
	push	esi

Top_A:
	mov		edx, PARAM_B
	call	WriteString
	call	ReadDec

	cmp		eax, USER_LOW
	jl		NotValid
	cmp		eax, USER_HI
	jg		NotValid
	jmp		ValidInput

NotValid:
	mov		edx, PARAM_C
	call	WriteString
	call	Crlf
	jmp		Top_A

ValidInput:
	mov		esi, PARAM_A
	mov		[esi], eax
	
	pop		esi
	pop		edx
	pop		eax
	pop		ebp
	ret		12
GetData ENDP

FillArray PROC
	push	ebp
	mov		ebp, esp
	push	eax
	push	ecx
	push	esi

	call	Randomize
	mov		ecx, PARAM_B
	mov		esi, PARAM_A
	
Loop_A:
	mov		eax, RAND_HI
	sub		eax, RAND_LOW
	call	RandomRange
	inc		eax
	add		eax, RAND_LOW
	mov		[esi], eax
	add		esi, 4
	loop	Loop_A

	pop		esi
	pop		ecx
	pop		eax
	pop		ebp
	ret		8
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
	push	ebp
	mov		ebp, esp
	sub		esp, 4							; Save space for local vars
	push	ecx
	push	esi
	push	eax
	push	ebx

	mov		ecx, PARAM_A					; ECX -> length of array
	mov		esi, PARAM_B					; ESI -> base pointer to array
	mov		DWORD PTR LOCAL_A, SPACE_CHAR
	mov		edx, ebp
	sub		edx, 4
	cld

Loop_B:
	LODSD
	call	WriteDec
	mov		eax, PARAM_A
	sub		eax, ecx
	inc		eax
	push	edx
	mov		edx, 0
	mov		ebx, NUM_PER_LINE
	div		ebx
	cmp		edx, 0
	pop		edx
	jne		Continue
	call	Crlf
	jmp		Loop_C
Continue:
 	call	WriteString
Loop_C:
	loop	Loop_B

	pop		ebx
	pop		eax
	pop		esi
	pop		ecx
	mov		esp, ebp
	pop		ebp
	ret		8
DisplayList ENDP


END main
