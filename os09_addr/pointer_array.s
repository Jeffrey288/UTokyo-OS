	.file	"pointer_array.c"
	.text
	.p2align 4
	.globl	idx_int
	.type	idx_int, @function
idx_int:
.LFB0:
	.cfi_startproc
	endbr64
	movl	(%rdi,%rsi,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	idx_int, .-idx_int
	.p2align 4
	.globl	idx_long
	.type	idx_long, @function
idx_long:
.LFB1:
	.cfi_startproc
	endbr64
	movq	(%rdi,%rsi,8), %rax
	ret
	.cfi_endproc
.LFE1:
	.size	idx_long, .-idx_long
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
