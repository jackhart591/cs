TITLE Assignment 3     (assignment3.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified: 1/31/22
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: 3
	Due Date: 1/30/22
	Description: Asks the user to enter negative integers above -100, and then once they enter a positive integer, 
	displays the number of valid integers, the sum of those integers, and the average. 

	**PLEASE USE ONE OF MY GRACE DAYS FOR THIS ASSIGNMENT**
&

INCLUDE Irvine32.inc

MAX_INPUT = 127
LOWER_LIMIT = -100

.data
finit

intro_str			BYTE		"Welcome to Integer Accumulator by Jackson Hart", 0
name_str			BYTE		"What's your name? ", 0
welcome_str		BYTE		"Welcome, ", 0
num_instruct_str	BYTE		"Please enter numbers in [-100, -1]", 0
exit_prompt_str	BYTE		"Enter a non-negative number when you are finished to see results", 0
num_prompt_str		BYTE		"Enter a number: ", 0
goodbyte_str		BYTE		"Goodbye, ", 0
exclam_str		BYTE		"!", 0
special_str		BYTE		"You didn't enter anything dummy!", 0
extra_cred_str		BYTE		"**EC: Prints average as a decimal**", 0

num_1_str			BYTE		"You entered ", 0
num_2_str			BYTE		" usable numbers", 0
sum_str			BYTE		"The sum of those numbers is ", 0
avg_str			BYTE		"The average of those numbers is ", 0
dot_str			BYTE		".", 0


user_name			BYTE		MAX_INPUT+1 DUP(?)
in_arr			DWORD	MAX_INPUT DUP(0)
num_int			DWORD	0
num_ave			REAL8	0.0
int_ave			DWORD	?
int_int			DWORD	?
int_real			DWORD	?
num_sum			DWORD	0
multiplier		DWORD	1000
neg_one			DWORD	-1


.code
main PROC

; Display program title
	mov		edx, OFFSET intro_str
	call		WriteString
	call		Crlf
	mov		edx, OFFSET extra_cred_str
	call		WriteString
	call		Crlf

; Prompt user for name
	mov		edx, OFFSET name_str
	call		WriteString
	mov		edx, OFFSET user_name
	mov		ecx, MAX_INPUT
	call		ReadString

; Welcome user
	mov		edx, OFFSET welcome_str
	call		WriteString
	mov		edx, OFFSET user_name
	call		WriteString
	call		Crlf
	call		Crlf

; Display instructions
	mov		edx, OFFSET num_instruct_str
	call		WriteString
	call		Crlf
	mov		edx, OFFSET exit_prompt_str
	call		WriteString
	call		Crlf

; Get integers from user
	mov			edx, OFFSET num_prompt_str
Top:
	call		WriteString
	call		ReadInt
	cmp		eax, LOWER_LIMIT
	jl		Top						; If not valid
	cmp		eax, 0
	jge		Average					; If positive
	push		eax						; Pushes valid ints onto stack
	inc		num_int					; Keeps track of number of valid ints
	jmp		Top

; Get average
Average:
	mov		ecx, num_int
	mov		ebx, 0
	mov		eax, num_int
	cmp		ecx, 0
	jne		Loopie					; If there's more than zero valid ints
	mov		edx, OFFSET special_str		; If not, stop the program
	call		WriteString
	call		Crlf
	jmp		Goodbyte
Loopie:
	pop		eax						; Pops stack to sum ints
	add		ebx, eax
	loop		Loopie

; Parse decimal into printable integers
	mov		num_sum, ebx
	fild		num_sum
	fwait
	fidiv	num_int					; Perform FPU division
	fimul	multiplier				; Multiply by 1000 to get percision I want
	fistp	int_ave					; Truncate and store into this var

	mov		eax, int_ave
	cdq
	idiv		multiplier				; Divide by 1000 to get the left side of decimal
	mov		int_int, eax
	imul		multiplier
	mov		ebx, int_ave
	sub		ebx, eax					; Subtract by the part I took out
	neg		ebx						; Negate it so printing right side of decimal is easier
	mov		int_real, ebx

; Display values to user
	
	mov		edx, OFFSET num_1_str		; Display number of nums entered
	mov		eax, num_int
	call		WriteString
	call		WriteInt
	mov		edx, OFFSET num_2_str
	call		WriteString
	call		Crlf

	mov		edx, OFFSET sum_str			; Write the sum
	mov		eax, num_sum
	call		WriteString
	call		WriteInt
	call		Crlf

	mov		edx, OFFSET avg_str			; Write the average
	call		WriteString
	mov		eax, int_int
	call		WriteInt
	mov		edx, OFFSET dot_str
	call		WriteString
	mov		eax, int_real
	call		WriteDec
	call		Crlf

; Say Goodbyte
Goodbyte:
	mov		edx, OFFSET goodbyte_str
	call		WriteString
	mov		edx, OFFSET user_name
	call		WriteString
	mov		edx, OFFSET exclam_str
	call		WriteString

	exit	; exit to operating system
main ENDP
END main
