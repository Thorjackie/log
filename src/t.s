	.arch armv8-a
	.file	"t.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB0:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	mov	w0, 4
	str	w0, [sp, 4]
	mov	w0, 5
	str	w0, [sp, 8]
	ldr	w1, [sp, 4]
	ldr	w0, [sp, 8]
	add	w0, w1, w0
	str	w0, [sp, 12]
	mov	w0, 0
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Alpine 10.3.1_git20211027) 10.3.1 20211027"
	.section	.note.GNU-stack,"",@progbits
