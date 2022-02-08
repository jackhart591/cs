TITLE Assignment 4		(assignmen4.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified:
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: 4
	Due Date: 2/13/2022
	Description: 
&

INCLUDE Irvine32.inc

UPPER_LIMIT = 300

.data

intro_str_1		BYTE		"Welcome to the composite number spreadsheet", 10, "Programmed by Jackson Hart", 0
intro_str_2		BYTE		"This program is capable of generating a list of composite numbers.", 10, "Simply let me know how many you would like to see.", \
							10, "I will accept orders for up to 300 composites.", 0
prompt_str		BYTE		"How many composites do you want to view? [1 .. 300]:", 0

.code
main PROC

	call	intro

	exit								; exit to operating system
main ENDP

COMMENT &
	Description: Introduces user to program
	Recieves: intro_str_1, intro_str_2
	Returns: none
	Preconditions: none
	Registers Changed: EDX (pushed onto stack)
&
intro PROC
	push	edx							; Save EDX from being overwritten

	mov		edx, OFFSET intro_str_1
	call	WriteString
	call	Crlf
	mov		edx, OFFSET intro_str_2
	call	WriteString
	call	Crlf

	pop		edx							; Restore EDX
	ret
intro ENDP

COMMENT &
	Description: Gets the number of composites to view from the user
	Recieves: none
	Returns: none
	Preconditions: none
	Registers Changed: EAX and EDX (pushed onto stack)
&
getInput PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 4
	mov		DWORD PTR [ebp-4], ?		; Input integer
	push	edx							; Save EDX from being overwritten
	push	eax							; Save EAX from being overwritten

	mov		edx, OFFSET prompt_str
	call	WriteString
	call	ReadDec

	pop		eax
	pop		edx
	mov		esp, ebp
	pop		ebp
	ret
getInput ENDP

END main
