TITLE Final Project     (finalproject.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified: 3/15/2022
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: FINAL
	Due Date: 3/15/2022
	Description: Computes some operands using different
				 "algorithms", operands include strings and
				 ints
&

INCLUDE Irvine32.inc

PARAM_A			EQU		[ebp+8]
PARAM_B			EQU		[ebp+12]
PARAM_BH		EQU		[ebp+14]
PARAM_C			EQU		[ebp+16]

LETTER_OFFSET	EQU		97
NUM_LETTERS		EQU		26

.code

; EC: Hello Sadie Thomas!! (If you're not Sadie, hello TA!)

;	Description: Determines which "computation algorithm" the program should run
;				 based on the contents of the destination variable.
;	Recieves: two numbers or one or two strings and an integer
;	Returns: none
;	Pre-conditions: none
;	Post-Conditions: either integers will be added, messages translated, or keys
;					 generated
;	Registers Changed: none
compute PROC
	ENTER	0, 0
	PUSHAD

	mov		eax, DWORD PTR PARAM_A			; PARAM_A = destination
	mov		ebx, 0
	cmp		[eax], ebx						; [EAX] = 0
	je		decoy_lbl
	dec		ebx
	cmp		[eax], ebx						; [EAX] = -1
	je		encryption_lbl
	dec		ebx
	cmp		[eax], ebx						; [EAX] = -2
	je		decryption_lbl
	dec		ebx
	cmp		[eax], ebx						; [EAX] = -3
	je		generation_lbl
	jmp		Leave_lbl						; Else, jump to leave

generation_lbl:
	push	DWORD PTR PARAM_B
	call	generation
	jmp		Leave_lbl


decryption_lbl:
   	push	DWORD PTR PARAM_C
	push	DWORD PTR PARAM_B
	call	decryption
	jmp		Leave_lbl


encryption_lbl:
	push	DWORD PTR PARAM_C
	push	DWORD PTR PARAM_B
	call	encryption
	jmp		Leave_lbl

decoy_lbl:
	push	WORD PTR PARAM_BH
	push	WORD PTR PARAM_B
	push	DWORD PTR PARAM_A
	call	decoy

Leave_lbl:
	POPAD
	LEAVE
	ret
compute ENDP

;	Description: Generates a key that contains randomly positioned
;				 letters of the alphabet only once
;	Recieves: memory location to place the key into
;	Returns: none
;	Pre-conditions: none
;	Post-Conditions: key variable will be filled with a key
;	Registers Changed: none
generation PROC
	ENTER	0, 0
	push	eax
	push	ebx
	push	ecx
	push	edi

	call	Randomize

	mov		edi, DWORD PTR PARAM_A			; EDI <- memory loc of key
	mov		ecx, NUM_LETTERS

Top_C:
	cld
	mov		eax, NUM_LETTERS				; RandomRange[0, 26)
	call	RandomRange
	add		eax, LETTER_OFFSET
	push	edi
	push	ecx
	mov		ebx, NUM_LETTERS
	sub		ebx, ecx
	mov		ecx, ebx					
	inc		ecx								; ECX <- Number of iterations
	std
	repne	scasb							; Loop backwards through everything so far
	jz		Intermission					; If we found something, get a different value
	pop		ecx								; Reset ECX
	pop		edi								; Reset EDI
	cld
	stosb
	loop	Top_C
	jmp		leave_lbl

Intermission:
	pop		ecx								; Reset ECX
	pop		edi								; Reset EDI
	jmp		Top_C

leave_lbl:
	pop		edi
	pop		ecx
	pop		ebx
	pop		eax
	LEAVE
	ret		4
generation ENDP

;	Description: Decrypts a message using the given key
;	Recieves: a message string and a key string
;	Returns: decrypted message
;	Pre-conditions: key must be filled with all 24 letters of the alphabet once
;	Post-Conditions: message will be updated with new decrypted message
;	Registers Changed: none
decryption PROC
	ENTER	0, 0
	push	eax
	push	ebx
	push	ecx
	push	esi
	push	edi

	mov		esi, DWORD PTR PARAM_A			; ESI <- Offset of message

Top_B:
	mov		edi, DWORD PTR PARAM_B			; EDI <- Offset of key
	mov		ecx, NUM_LETTERS				; Holds iterator

	; Check to see if this character is a letter
	mov		al, BYTE PTR [esi]
	cmp		al, 97
	jl		Invalid_B
	cmp		al, 122
	jg		Invalid_B

	; Find position in key
	cld
	mov		al, BYTE PTR [esi]
	repne	scasb
	mov		eax, NUM_LETTERS
	sub		eax, ecx						; EAX <- Index of letter in alphabet
	add		eax, LETTER_OFFSET
	dec		eax
	mov		BYTE PTR [esi], al

Invalid_B:
	inc		esi
	mov		bl, BYTE PTR [esi]
	cmp		bl, 0
	jne		Top_B

	pop		edi
	pop		esi
	pop		ecx
	pop		ebx
	pop		eax
	LEAVE
	ret		8
decryption ENDP

;	Description: Encrypts a message using the given key
;	Recieves: a message string and a key string
;	Returns: encrypted message
;	Pre-conditions: key must be filled with all 24 letters of the alphabet once
;	Post-Conditions: message will be updated with new encrypted message
;	Registers Changed: none
encryption PROC
	ENTER	0, 0
	push	eax
	push	ebx
	push	esi
	push	edi

	mov		edi, DWORD PTR PARAM_A			; EDI <- Offset of message
	mov		esi, DWORD PTR PARAM_B			; ESI <- Offset of key

Top:
	; Check to see if this character is a letter
	mov		eax, 0
	mov		ebx, 0
	mov		al, BYTE PTR [edi]
	cmp		al, 97
	jl		Invalid_A
	cmp		al, 122
	jg		Invalid_A

	sub		al, LETTER_OFFSET				; Get index of letter in key
	mov		bl, BYTE PTR [esi + eax]		; Store new letter into ebx 
	mov		BYTE PTR [edi], bl				; move key + index into pos of edi

Invalid_A:
	inc		edi								; iterate to next pos in array
	mov		bl, BYTE PTR [edi]
	cmp		bl, 0							; Is this the end of the string?
	jne		Top

	pop		edi
	pop		esi
	pop		ebx
	pop		eax
	LEAVE
	ret		8
encryption ENDP

;	Description: Adds two word integers
;	Recieves: an memory loc to put the sum in, and 2 integer operands
;	Returns: the sum of the two integers
;	Pre-conditions: none
;	Post-Conditions: destination will contain sum
;	Registers Changed: none
decoy PROC
	ENTER	0, 0
	push	eax
	push	ebx
	push	esi

	mov		ax, WORD PTR PARAM_BH			; AX <- Operand 1
	mov		bx, WORD PTR PARAM_B			; BX <- Operand 2
	movsx	eax, ax
	movsx	ebx, bx
	mov		esi, DWORD PTR PARAM_A			; EDI <- Offset of destination

	add		eax, ebx
	mov		[esi], eax

	pop		esi
	pop		ebx
	pop		eax
	LEAVE
	ret		8
decoy	ENDP

END main