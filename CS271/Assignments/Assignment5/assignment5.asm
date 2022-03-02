TITLE Assignment 5     (assignment5.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified: 03/01/2022
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: 5
	Due Date: 02/27/2022
	Description: This program asks for a number of numbers to create, fills an array with random numbers with the given length,
				 sorts the array, gets the median, and displays the unsorted and sorted array as well as the median.
&

INCLUDE Irvine32.inc

RAND_LOW		EQU		100
RAND_HI			EQU		999
USER_LOW		EQU		15
USER_HI			EQU		200

PARAM_A			EQU		[ebp+8]
PARAM_B			EQU		[ebp+12]
PARAM_C			EQU		[ebp+16]
PARAM_D			EQU		[ebp+20]

LOCAL_A			EQU		[ebp-4]
LOCAL_B			EQU		[ebp-8]
LOCAL_C			EQU		[ebp-12]
LOCAL_D			EQU		[ebp-16]

SPACE_CHAR		EQU		20h
NUM_PER_LINE	EQU		10

.data

	intro_str		BYTE		"Sorting Random Integers", 10, 13, \
								"By Jackson Hart", 10, 13, \
								"EC: Hello James Taylor (if not, hello TA)!", 10, 13, \
								"This program generates random numbers in the range [100 ... 999],", 10, 13, \
								"displays the original list, sorts the list, and calculates the median value.", 10, 13, \
								"Finally, it displays the list sorted in descending order.", 0
	number_prompt	BYTE		"How many numbers should be generated? [15 ... 200]: ", 0
	invalid_str		BYTE		"Invalid input, try again!", 0
	median_str		BYTE		"The median is ", 0
	unsort_str		BYTE		"The unsorted list: ", 0
	sorted_str		BYTE		"The sorted list: ", 0
	goodbyte_str	BYTE		"Thanks for using my program!", 0

	num_ints		DWORD		0
	num_arr			DWORD		USER_HI DUP(?)

.code

COMMENT &
	Description: The driver for this program
	Recieves: none
	Returns: none
	Pre-conditions: none
	Post-Conditions: none
	Registers Changed: EDX
&
main PROC
	
	push	OFFSET intro_str
	call	Intro

	push	OFFSET invalid_str
	push	OFFSET number_prompt
	push	OFFSET num_ints
	call	GetData

	push	num_ints
	push	OFFSET num_arr
	call	FillArray

	call	Crlf
	mov		edx, OFFSET unsort_str
	call	WriteString
	call	Crlf
	push	OFFSET num_arr
	push	num_ints
	call	DisplayList
	call	Crlf

	push	num_ints
	push	OFFSET num_arr
	call	SortList

	mov		edx, OFFSET median_str
	call	WriteString
	push	num_ints
	push	OFFSET num_arr
	call	DisplayMedian
	call	Crlf
	call	Crlf

	mov		edx, OFFSET sorted_str
	call	WriteString
	call	Crlf
	push	OFFSET num_arr
	push	num_ints
	call	DisplayList
	call	Crlf

	mov		edx, OFFSET goodbyte_str
	call	WriteString
	call	Crlf


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

COMMENT &
	Description: Gets the number of numbers to fill the array with
	Recieves: offset of invalid str, offset of number prompt, offset of num_ints
	Returns: none
	Pre-conditions: none
	Post-Conditions: num_ints will be filled with the number of numbers to print
	Registers Changed: none
&
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
	jl		NotValid							; if input < lower lim
	cmp		eax, USER_HI
	jg		NotValid							; if input > upper lim
	jmp		ValidInput							; else...

NotValid:
	mov		edx, PARAM_C
	call	WriteString
	call	Crlf
	jmp		Top_A

ValidInput:
	mov		esi, PARAM_A
	mov		[esi], eax							; Move number to print into the address stored in ESI
	
	pop		esi
	pop		edx
	pop		eax
	pop		ebp
	ret		12
GetData ENDP

COMMENT &
	Description: Fills array with a specified number of numbers
	Recieves: number of integers to print, address of array to fill
	Returns: none
	Pre-conditions: none
	Post-Conditions: array will be filled with random numbers
	Registers Changed: none
&
FillArray PROC
	push	ebp
	mov		ebp, esp
	push	eax
	push	ecx
	push	esi

	call	Randomize
	mov		ecx, PARAM_B						; ECX <- Number of ints
	mov		esi, PARAM_A						; ESI <- Address of arr
	
Loop_A:
	mov		eax, RAND_HI
	sub		eax, RAND_LOW						; Upper lim - Lower lim
	call	RandomRange							; Random[0 .. Upper lim - Lower lim]
	add		eax, RAND_LOW						; Random[Lower lim .. Upper lim]
	mov		[esi], eax							; Address @ ESI <- Random[lower lim .. Upper lim]
	add		esi, 4								; Increment to next elem of arr
	loop	Loop_A

	pop		esi
	pop		ecx
	pop		eax
	pop		ebp
	ret		8
FillArray ENDP

COMMENT &
	Description: Exchanges two values at two given mem locations
	Recieves: offset of value 1, offset of value 2
	Returns: none
	Pre-conditions: none
	Post-Conditions: the two vals will be swapped
	Registers Changed: none
&

Exchange PROC
	push	ebp
	mov		ebp, esp
	push	eax
	push	ebx
	push	ecx
	push	edx

	mov		eax, DWORD PTR PARAM_A			; EAX <- val_1 address
	mov		ebx, DWORD PTR PARAM_B			; EBX <- val_2 address
	mov		ecx, [eax]
	mov		edx, [ebx]
	mov		[eax], edx
	mov		[ebx], ecx

	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
	pop		ebp
	ret		8
Exchange ENDP

COMMENT &
	Description: Sorts list
	Recieves: offset of array, num_ints
	Returns: none
	Pre-conditions: Array must be filled with values
	Post-Conditions: Array will be sorted
	Registers Changed: none
&
SortList PROC
	push	ebp
	mov		ebp, esp
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi
	push	edi

	mov		ecx, DWORD PTR PARAM_B
	dec		ecx
Loop_D:	
	mov		edi, DWORD PTR PARAM_B			; EDI <- index
	sub		edi, ecx						; i = k 
	dec		edi
	mov		eax, 4
	mov		edx, 0
	mul		edi
	mov		edi, eax						; EDI <- index offset
	push	ecx
	mov		ebx, [ebp+8]					; EBX <- arr[i]
	add		ebx, edi
	mov		eax, ebx
	mov		esi, ebx
	add		eax, 4
	mov		edx, 0
Loop_E:
 	inc		edx								; EDX is accumulator
	push	esi
	mov		esi, [eax]
	cmp		esi, [ebx]						; arr[j] <= arr[i]
	pop		esi
	jle		Not_A
	mov		ebx, eax						; else, swap
	mov		edi, edx
Not_A:
	add		eax, 4							; EAX <- arr[j+1]
	loop	Loop_E

	pop		ecx
	push	esi								; PARAM_B = current value of array we're looking at (arr[i])
	push	ebx								; PARAM_A = Highest value after arr[i]
	call	Exchange
	loop	Loop_D

	pop		edi
	pop		esi
	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
	pop		ebp
	ret		8
SortList ENDP

COMMENT &
	Description: Gets the middle val and if there isn't a middle val, finds the avg of the
				 two closest vals
	Recieves: offset of array, num_ints
	Returns: none
	Pre-conditions: Array must be filled with values
	Post-Conditions: Median will be printed
	Registers Changed: none
&
DisplayMedian PROC
	push	ebp
	mov		ebp, esp
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi

	mov		edx, 0
	mov		eax, DWORD PTR PARAM_B					; EAX <- Request
	mov		esi, DWORD PTR PARAM_A					; ESI <- OFFSET Arr
	mov		ecx, 2
	div		ecx
	cmp		edx, 0
	jne		Odd
	mov		ecx, 4
	mul		ecx
	add		eax, esi						; EAX <- Address of middle elem
	mov		ebx, [eax]
	mov		eax, ebx						; EAX <- Value of middle elem
	jmp		Ret_B
Odd:
	push	eax
	mov		edx, 0
	inc		eax
	mov		ecx, 4
	mul		ecx								; EAX <- Index offset
	add		eax, esi						; EAX <- Address of middle elem + 1
	mov		ebx, [eax]						; EBX <- Value of middle elem + 1
	pop		eax
	mov		ecx, 4
	mul		ecx
	add		eax, esi
	mov		ecx, [eax]
	mov		eax, ecx						; EAX <- Value of middle elem - 1
	add		eax, ebx
	mov		ecx, 2
	div		ecx								; EAX <- Gets average of these two values
Ret_B:
	call	WriteDec
	pop		esi
	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
	pop		ebp
	ret		8
DisplayMedian ENDP

COMMENT &
	Description: Prints out the a given list
	Recieves: number of elems in arr, address of array
	Returns: none
	Pre-conditions: array must be filled with n values
	Post-Conditions: Array will be printed out to user
	Registers Changed: none
&
DisplayList PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 4								; Save space for local vars
	push	ecx
	push	esi
	push	eax
	push	ebx

	mov		ecx, PARAM_A						; ECX <- length of array
	mov		esi, PARAM_B						; ESI <- base pointer to array
	mov		DWORD PTR LOCAL_A, SPACE_CHAR
	mov		edx, ebp
	sub		edx, 4
	cld

Loop_B:
	lodsd
	call	WriteDec
	mov		eax, PARAM_A
	sub		eax, ecx							; EAX <- number of times loop has run -1
	inc		eax									; EAX <- number of times loop has run
	push	edx
	mov		edx, 0
	mov		ebx, NUM_PER_LINE
	div		ebx
	cmp		edx, 0								; Is the current iteration of this loop a multiple of 10?
	pop		edx
	jne		Continue							; If not, continue
	call	Crlf								; Else, create a new line
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
