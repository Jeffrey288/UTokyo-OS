	.file	"pointer.c"
	.text
	.p2align 4
	.globl	deref_int
	.type	deref_int, @function
deref_int:
.LFB0:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	deref_int, .-deref_int
	.p2align 4
	.globl	deref_long
	.type	deref_long, @function
deref_long:
.LFB1:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE1:
	.size	deref_long, .-deref_long
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
