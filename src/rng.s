	.text
	.file	"rng.cpp"
	.globl	_ZN4SRNG7squaresEmm     # -- Begin function _ZN4SRNG7squaresEmm
	.p2align	4, 0x90
	.type	_ZN4SRNG7squaresEmm,@function
_ZN4SRNG7squaresEmm:                    # @_ZN4SRNG7squaresEmm
	.cfi_startproc
# %bb.0:
	imulq	%rsi, %rdi
	addq	%rdi, %rsi
	movq	%rdi, %rax
	imulq	%rdi, %rax
	addq	%rdi, %rax
	rorxq	$32, %rax, %rax
	imulq	%rax, %rax
	addq	%rsi, %rax
	rorxq	$32, %rax, %rax
	imulq	%rax, %rax
	addq	%rdi, %rax
	shrq	$32, %rax
	retq
.Lfunc_end0:
	.size	_ZN4SRNG7squaresEmm, .Lfunc_end0-_ZN4SRNG7squaresEmm
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 10.0.0 (/var/tmp/portage/sys-devel/clang-10.0.0.9999/work/x/y/clang)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
