section .text
	global	main
main:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 112
	mov		rdx, 2
	mov		[rbp-8], rdx
	mov		rdx, [rbp-16]
	mov		[rbp-8], rdx
	mov		rdx, [rbp-32]
	mov		rcx, 2
	imul	rdx, rcx
	mov		[rbp-32], rdx
.L5:
	mov		rdx, [rbp-40]
	mov		rcx, 3
	cmp		rdx, rcx
	jge		.L105
	mov		rdx, [rbp-40]
	mov		rcx, 1
	add		rdx, rcx
	mov		[rbp-40], rdx
	jmp		.L5
.L105:
.L7:
	mov		rdx, [rbp-40]
	mov		rcx, 3
	cmp		rdx, rcx
	jge		.L107
	mov		rdx, [rbp-40]
	mov		rcx, 1
	add		rdx, rcx
	mov		[rbp-32], rdx
.L107:
	add		rsp, 112
	pop		rbp
	mov		rax, 1
	xor		rbx, rbx
	int		0x80

	extern	printf
	extern	scanf

section .data
	formString db "%s", 10, 0
	formInt db "%d", 10, 0
	formInInt db "%d", 0
	bufInInt dq 0
