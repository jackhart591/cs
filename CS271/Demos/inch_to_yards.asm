TITLE inch_to_yards	(inch_to_yards.asm)

INCLUDE Irvine32.inc

YARD_TO_INCH_FACTOR = 13

.data

		intro	BYTE		"Hi there, this is Jack", 13, 10, "This program is going to convert aaa yard to inches", 0
		result_1	BYTE		"That's...", 0
		result_2	BYTE		" in inches", 0
		inches	DWORD	?
		good_bye	BYTE		"Good Bye", 0
		username	BYTE		33 DUP(0)		; string entered by the user, initialized to 33 0's

		prompt_1	BYTE		"What's your name? ", 0
		prompt_2	BYTE		"Enter yard(s): ", 0
		yards	DWORD	?

.code
main proc


; 1. Introduce the programmer
	mov		edx,		OFFSET intro ; Move the intro to edx for printing
	call		WriteString
	call		Crlf

; 2. Get the name from the user
	mov		edx,		OFFSET prompt_1
	call		WriteString

	mov		edx,		OFFSET username
	mov		ecx,		32
	call		ReadString	; Stores string in edx


; 3. Get the yards from the user
	mov		edx,		OFFSET prompt_2
	call		WriteString
	call		ReadInt		; user input will be stored in eax
	mov		yards, eax

; 4. Calculation
	mov		ebx, YARD_TO_INCH_FACTOR
	mul		ebx
	mov		inches, eax

; 5. Report the result
	mov		edx,		OFFSET intro
	call		WriteString
	mov		eax,		inches
	call		WriteDec	; Call WriteInt
	mov		edx,		OFFSET result_2
	call		WriteString
	call		Crlf

; 6. Farewell "Goodbye"
	mov		edx,		OFFSET good_bye
	call		WriteString

	mov		edx,		OFFSET username
	call		WriteString
	call		Crlf

	exit
main ENDP

; Just add and unadd files as you need them in the solution

end main
