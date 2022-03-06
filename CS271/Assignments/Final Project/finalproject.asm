TITLE Final Project     (finalproject.asm)

COMMENT &
	Author: Jackson Hart
	Last Modified:
	OSU email address: hartjack@oregonstate.edu
	Course number/section: 31528
	Assignment Number: FINAL
	Due Date: 3/15/2022
	Description: 
&

INCLUDE Irvine32.inc

PARAM_A			EQU		[ebp+8]
PARAM_B			EQU		[ebp+12]
PARAM_BH		EQU		[ebp+14]
PARAM_C			EQU		[ebp+16]

LETTER_OFFSET	EQU		97
NUM_LETTERS		EQU		26

.data

myKey      BYTE   "efbcdghijklmnopqrstuvwxyza"
message    BYTE   "the contents of this message will be a mystery.",0
dest       DWORD   -1

.code
main PROC

	push   OFFSET myKey
	push   OFFSET message
	push   OFFSET dest
	call   compute
	;; message now contains the encrypted string
	mov    edx, OFFSET message
	call   WriteString

	exit	; exit to operating system
main ENDP

compute PROC
	ENTER	0, 0
	PUSHAD

	mov		eax, DWORD PTR PARAM_A			; PARAM_A = destination
	mov		ebx, 0
	cmp		[eax], ebx
	je		decoy
	dec		ebx
	cmp		[eax], ebx
	je		encryption
	dec		ebx
	cmp		[eax], ebx
	je		decryption
	dec		ebx
	cmp		[eax], ebx
	je		generation


generation:
	
	jmp		LeaveFunc


; PARAM_A <- Offset of Destination
; PARAM_B <- Offset of Message
; PARAM_C <- Offset of Key
decryption:
   	mov		esi, DWORD PTR PARAM_B			; ESI <- Offset of message

Top_B:
	mov		edi, DWORD PTR PARAM_C			; EDI <- Offset of key
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

	jmp		LeaveFunc


; PARAM_A <- Offset of Destination
; PARAM_B <- Offset of Message
; PARAM_C <- Offset of Key
encryption:
	mov		edi, DWORD PTR PARAM_B			; EDI <- Offset of message
	mov		esi, DWORD PTR PARAM_C			; ESI <- Offset of key

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

	jmp		LeaveFunc


; PARAM_A <- Offset of dest
; PARAM_BH <- Operand 1
; PARAM_B <- Operand 2
decoy:
	mov		ax, WORD PTR PARAM_BH			; AX <- Operand 1
	mov		bx, WORD PTR PARAM_B			; BX <- Operand 2
	movsx	eax, ax
	movsx	ebx, bx
	mov		esi, DWORD PTR PARAM_A			; EDX <- Offset of destination

	add		eax, ebx
	mov		[esi], eax
	jmp		LeaveFunc

LeaveFunc:
	POPAD
	LEAVE
	ret
compute ENDP

END main
