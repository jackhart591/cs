TITLE Assignment 4		(assignmen4.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified:
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: 4
	Due Date: 2/13/2022
	Description: Asks the user how many composite numbers they want to print, and the program prints
			   that number of composites. 
&

INCLUDE Irvine32.inc

UPPER_LIMIT	EQU 300
LOCAL_A		EQU [ebp-4]
LOCAL_B		EQU [ebp-8]
PARAM_A		EQU [ebp+8]

.data

intro_str_1		BYTE		"Welcome to the composite number spreadsheet", 10, "Programmed by Jackson Hart", 0
intro_str_2		BYTE		"This program is capable of generating a list of composite numbers.", 10, "Simply let me know how many you would like to see.", \
						10, "I will accept orders for up to 300 composites.", 0
prompt_str		BYTE		"How many composites do you want to view? [1 .. 300]:", 0
bad_in_str		BYTE		"That was not within the specified range, try again!", 10, 0
goodbyte_str		BYTE		"Thanks for using my program!", 0
tab_char			BYTE		9, 0
endl_char			BYTE		10, 0
num_chars			DWORD	10

num_composites	DWORD		?

.code
main PROC

	call		intro
	call		getInput
	call		showComposites
	call		goodByte

	exit										; exit to operating system
main ENDP

COMMENT &
	Description: Introduces user to program
	Recieves: intro_str_1, intro_str_2
	Returns: none
	Pre-conditions: none
	Post-conditions: none
	Registers Changed: EDX (pushed onto stack)
&
intro PROC USES edx
	mov		edx, OFFSET intro_str_1
	call		WriteString
	call		Crlf
	mov		edx, OFFSET intro_str_2
	call		WriteString
	call		Crlf

	ret
intro ENDP

COMMENT &
	Description: Gets the number of composites to view from the user and calls validateInput
	Recieves: none
	Returns: none
	Pre-conditions: none
	Post-Conditions: num_composites will be updated with valid user input
	Registers Changed: EAX and EDX (pushed onto stack)
&
getInput PROC USES edx eax
	push		ebp

	mov		edx, OFFSET prompt_str
	call		WriteString
	call		ReadDec
	call		validateInput

	pop		ebp
	ret
getInput ENDP

COMMENT &
	Description: Validates that the value stored in EAX is between 1 and 300
	Recieves: none
	Returns: none
	Pre-conditions: user input is stored in EAX
	Post-Conditions: either will set num_composites or call getInput
	Registers Changed: none
&
validateInput PROC
	push		ebp
	mov		ebp, esp

	cmp		eax, 0
	jle		BadInput						; if input <= 0
	cmp		eax, UPPER_LIMIT
	jg		BadInput						; if input > 300
	jmp		GoodInput						; else...

BadInput:
	mov		edx, OFFSET bad_in_str
	call		WriteString
	call		getInput						; Get new input
	jmp		Return_A
GoodInput:
	mov		num_composites, eax				; Save the validated input

Return_A:
	pop		ebp
	ret
validateInput ENDP

COMMENT &
	Description: Displays composite numbers
	Recieves: none
	Returns: none
	Pre-conditions: num_composites is set
	Post-Conditions: composites will be displayed to the user
	Registers Changed: none
&
showComposites PROC USES ecx eax edx
	push		ebp
	mov		ebp, esp
	sub		esp, 8						; Free space for my local var
	mov		DWORD PTR LOCAL_A, 1			; Local variable for displaying composites (Starts at 1 because loop will inc to 2 which will not be recognized as comp)

	mov		ecx, num_composites
	mov		edx, OFFSET tab_char			; Load tab char into edx


Loopie_A:
	inc		DWORD PTR LOCAL_A
	push		DWORD PTR LOCAL_A				; Push argument
	call		checkComposite
	pop		DWORD PTR LOCAL_B				; Pop argument into LOCAL_B
	cmp		DWORD PTR LOCAL_B, 0			; Is the current integer a composite?
	je		NonPrime
	mov		eax, DWORD PTR LOCAL_B
	call		WriteDec						; Write composite
	call		WriteString					; Write spaces
	call		checkEndL						; Check if it's time for a new line
	loop		Loopie_A
	jmp		Return_C
NonPrime:
	jmp		Loopie_A

Return_C:
	mov		esp, ebp						; Remove locals from stack
	pop		ebp
	ret
showComposites ENDP

COMMENT &
	Description: Checks if it is time to insert and endl
	Recieves: none
	Returns: none
	Pre-conditions: ecx is currently being used for a counter and num_composites is set
	Post-Conditions: if num_composites - ecx is divisable by 10, a endl will be printed
	Registers Changed: none
&
checkEndL	PROC USES eax ebx edx
	push		ebp

	mov		ebx, num_composites
	mov		eax, ecx
	sub		ebx, eax						; num_composites - ecx = number the current composite is
	xchg		ebx, eax
	inc		eax							; So it starts at 1 and not 0
	mov		edx, 0
	div		num_chars
	cmp		edx, 0						; If the current composite's position is divisible by 10...
	jne		Return_D
	mov		edx, OFFSET endl_char			; Print a new line
	call		WriteString

Return_D:
	pop		ebp
	ret
checkEndL	ENDP

COMMENT &
	Description: Checks to see if a given number is a composite
	Recieves: number to check (LOCAL_A)
	Returns: 0 if not a composite, the inputted number if it is
	Pre-conditions: some number to check is pushed to the stack
	Post-Conditions: the number on the stack may be 0
	Registers Changed: none (pushed and popped so they do not get changed)
&
checkComposite PROC
	push		ebp
	mov		ebp, esp
	sub		esp, 4						; Free space for my local var
	push		eax
	push		ecx
	push		edx							; Save EAX, ECX, & EDX separately so I don't lose my parameter

	mov		DWORD PTR LOCAL_A, 1			; Make sure loop doesn't divide the number by 1
	mov		ecx, DWORD PTR PARAM_A
	sub		ecx, 2						; Make sure loop doesn't divide the number by itself

	cmp		ecx, 0
	jg		Loopie_B
	mov		DWORD PTR PARAM_A, 0
	jmp		Return_B

Loopie_B:
	inc		DWORD PTR LOCAL_A
	mov		eax, DWORD PTR PARAM_A
	mov		edx, 0
	div		DWORD PTR LOCAL_A
	cmp		edx, 0
	je		Return_B						; If we found a number this num is divisible by, return
	loop		Loopie_B

	mov		DWORD PTR PARAM_A, 0			; If we did not find a number, then return 0

Return_B:
	pop		edx
	pop		ecx
	pop		eax
	mov		esp, ebp
	pop		ebp
	ret
checkComposite ENDP

goodByte PROC USES edx
	push			ebp

	mov		edx, OFFSET goodbyte_str
	call		WriteString

	pop			ebp
	ret
goodByte ENDP

END main
