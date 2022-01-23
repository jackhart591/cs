TITLE Assignment 2     (Assignment2.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified:
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: 2
	Due Date: 1/23/22
	Description: 
&

INCLUDE Irvine32.inc

; maximum number of chars in an input string
MAX_INPUT_CHAR = 127

; Min/Max number of fibb nums
MIN_NUMS = 1
MAX_NUMS = 46

.data

intro		BYTE		"Fibonacci Numbers", 10, "Programmed by Jackson Hart", 0
name_prompt	BYTE		"What's your name? ", 0
welcome_str	BYTE		"Hello, ", 0
num_prompt	BYTE		"Enter the number of fibonacci numbers to be displayed.", 10, "Provide the number as an integer in the range [1 .. 46].", 10, \
					"How many fibonacci numbers do you want? ", 0
bad_in_str	BYTE		"That wasn't a valid number, please try again: ", 0
gbye_str		BYTE		"Goodbye, ", 0
space_str		BYTE		"     ", 0
line_str		BYTE		10, 0

user_name		BYTE		MAX_INPUT_CHAR+1	DUP(?) ; +1 for the null char
fib_nums		DWORD	?
fib_0		DWORD	1
fib_1		DWORD	1
num_per_line	DWORD	4

.code
main PROC

; Write the intro to the program
	mov		edx, OFFSET intro
	call		WriteString
	call		Crlf

; Ask for and store the user's name
	mov		edx, OFFSET name_prompt
	call		WriteString

	mov		edx, OFFSET user_name
	mov		ecx, MAX_INPUT_CHAR
	call		ReadString

; Welcome user and ask for num of fibonacci numbers
	mov		edx, OFFSET welcome_str
	call		WriteString
	mov		edx, OFFSET user_name
	call		WriteString
	call		Crlf
	mov		edx, OFFSET num_prompt
	call		WriteString
Top:
	call		ReadInt
	cmp		eax, MIN_NUMS	
	jl		NaughtyLabel		; Val < 1
	cmp		eax, MAX_NUMS
	jg		NaughtyLabel		; Val > 46
	jmp		GoodInput
NaughtyLabel:					; Bad input gets sent to the naughty label
	mov		edx, OFFSET bad_in_str
	call		WriteString
	jmp		Top

; Print fibonacci numbers
GoodInput:
	mov		fib_nums, eax
	mov		ecx, fib_nums
Fib_Loop:						; Beginning of loop
	cmp		ecx, fib_nums
	jne		Num_One
	mov		eax, fib_0
	call		WriteDec			; Base case 0
	mov		ebx, eax
	jmp		Loopie
Num_One:						; Base case 1
	mov		edx, fib_nums
	sub		edx, 1
	cmp		ecx, edx
	jne		Num_GOne
	mov		eax, fib_1
	call		WriteDec
	jmp		Loopie
Num_GOne:
	push		eax				; Push EAX to stack so we don't lose N-1
	add		eax, ebx			; Add to get N
	pop		ebx				; Pop N-1 in EBX
	call		WriteDec
Loopie:
	mov		edx, OFFSET space_str
	call		WriteString

	push		eax				; Store eax so we don't lose N-1
	mov		eax, fib_nums
	sub		eax, ecx			; Gets the total amount of loops run
	inc		eax				; Increments to account for 0 being the first loop
	mov		edx, 0
	div		num_per_line		; Divide by number of terms per line
	pop		eax				; Pop N-1 back into EAX
	cmp		edx, 0			; If the remainder is 0...
	jne		Loopie_Loopie
	mov		edx, OFFSET line_str
	call		WriteString		; ...Make a new line
Loopie_Loopie:
	loop		Fib_Loop

; Say goodbyte to the user
	call		Crlf
	mov		edx, OFFSET gbye_str
	call		WriteString
	mov		edx, OFFSET user_name
	call		WriteString
	

	exit	; exit to operating system
main ENDP

END main
