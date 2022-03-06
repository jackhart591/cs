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

.data

operand1   WORD    46
operand2   WORD    -20
dest       DWORD   0

.code
main PROC

	push   operand1
	push   operand2
	push   OFFSET dest
	call   compute
	;; currently dest holds a value of +26
	mov    eax, dest
	call   WriteInt   ; should display +26

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

decryption:
	jmp		LeaveFunc

encryption:
	jmp		LeaveFunc

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
