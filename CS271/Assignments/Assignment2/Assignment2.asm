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

user_name		BYTE		MAX_INPUT_CHAR+1	DUP(?) ; +1 for the null char
fib_nums		DWORD	?
fib_0		BYTE		0
fib_1		BYTE		1

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
	jl		BadInput	; Val < 1
	cmp		eax, MAX_NUMS
	jg		BadInput	; Val > 46
	jmp		GoodInput
BadInput:
	mov		edx, OFFSET bad_in_str
	call		WriteString
	jmp		Top

; Print fibonacci numbers
GoodInput:
	mov		fib_nums, eax
	; neck
	

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
