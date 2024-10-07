	.file	"pointer_arrow.c"
	.text
	.p2align 4
	.globl	chase
	.type	chase, @function
chase:
.LFB0:
	.cfi_startproc
	endbr64
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L4
	.p2align 4,,10
	.p2align 3
.L3:
	addq	8(%rdi), %rax
	movq	(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.L3
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	ret
	.cfi_endproc
.LFE0:
	.size	chase, .-chase
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
