	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.globl	_err_ret                ## -- Begin function err_ret
	.p2align	4, 0x90
_err_ret:                               ## @err_ret
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$416, %rsp              ## imm = 0x1A0
	testb	%al, %al
	movaps	%xmm7, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -336(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -352(%rbp)       ## 16-byte Spill
	movq	%rdi, -360(%rbp)        ## 8-byte Spill
	movq	%r9, -368(%rbp)         ## 8-byte Spill
	movq	%r8, -376(%rbp)         ## 8-byte Spill
	movq	%rcx, -384(%rbp)        ## 8-byte Spill
	movq	%rdx, -392(%rbp)        ## 8-byte Spill
	movq	%rsi, -400(%rbp)        ## 8-byte Spill
	je	LBB0_4
## %bb.3:
	movaps	-352(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -176(%rbp)
	movaps	-336(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -160(%rbp)
	movaps	-320(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -144(%rbp)
	movaps	-304(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -128(%rbp)
	movaps	-288(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -112(%rbp)
	movaps	-272(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -96(%rbp)
	movaps	-256(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -80(%rbp)
	movaps	-240(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -64(%rbp)
LBB0_4:
	movq	-368(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -184(%rbp)
	movq	-376(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -192(%rbp)
	movq	-384(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -200(%rbp)
	movq	-392(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -208(%rbp)
	movq	-400(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -216(%rbp)
	movq	-360(%rbp), %r8         ## 8-byte Reload
	leaq	-32(%rbp), %r9
	movq	___stack_chk_guard@GOTPCREL(%rip), %r10
	movq	(%r10), %r10
	movq	%r10, -8(%rbp)
	movq	%r8, -40(%rbp)
	leaq	-224(%rbp), %r8
	movq	%r8, 16(%r9)
	leaq	16(%rbp), %r8
	movq	%r8, 8(%r9)
	movl	$48, 4(%r9)
	movl	$8, (%r9)
	callq	___error
	movl	$1, %edi
	leaq	-32(%rbp), %rcx
	movl	(%rax), %esi
	movq	-40(%rbp), %rdx
	callq	_err_doit
	leaq	-32(%rbp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movq	%rax, -408(%rbp)        ## 8-byte Spill
	jne	LBB0_2
## %bb.1:
	addq	$416, %rsp              ## imm = 0x1A0
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function err_doit
_err_doit:                              ## @err_doit
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$4224, %rsp             ## imm = 0x1080
	movl	$4096, %eax             ## imm = 0x1000
	movl	%eax, %r8d
	xorl	%eax, %eax
	leaq	-4112(%rbp), %r9
	movq	___stack_chk_guard@GOTPCREL(%rip), %r10
	movq	(%r10), %r10
	movq	%r10, -8(%rbp)
	movl	%edi, -4116(%rbp)
	movl	%esi, -4120(%rbp)
	movq	%rdx, -4128(%rbp)
	movq	%rcx, -4136(%rbp)
	movq	-4128(%rbp), %rcx
	movq	-4136(%rbp), %rdx
	movq	%r9, %rdi
	movq	%r8, %rsi
	movq	%rdx, -4144(%rbp)       ## 8-byte Spill
	movl	%eax, %edx
	movq	%rcx, -4152(%rbp)       ## 8-byte Spill
	movq	%r8, %rcx
	movq	-4152(%rbp), %r8        ## 8-byte Reload
	movq	-4144(%rbp), %r9        ## 8-byte Reload
	callq	___vsnprintf_chk
	cmpl	$0, -4116(%rbp)
	movl	%eax, -4156(%rbp)       ## 4-byte Spill
	je	LBB1_2
## %bb.1:
	movl	$4096, %eax             ## imm = 0x1000
	movl	%eax, %ecx
	leaq	-4112(%rbp), %rdx
	movq	%rdx, %rdi
	movq	%rcx, -4168(%rbp)       ## 8-byte Spill
	movq	%rdx, -4176(%rbp)       ## 8-byte Spill
	callq	_strlen
	movq	-4176(%rbp), %rcx       ## 8-byte Reload
	addq	%rax, %rcx
	movq	-4176(%rbp), %rdi       ## 8-byte Reload
	movq	%rcx, -4184(%rbp)       ## 8-byte Spill
	callq	_strlen
	movq	-4168(%rbp), %rcx       ## 8-byte Reload
	subq	%rax, %rcx
	movl	-4120(%rbp), %edi
	movq	%rcx, -4192(%rbp)       ## 8-byte Spill
	callq	_strerror
	xorl	%edx, %edx
	movq	$-1, %rcx
	leaq	L_.str.1(%rip), %r8
	movq	-4184(%rbp), %rdi       ## 8-byte Reload
	movq	-4192(%rbp), %rsi       ## 8-byte Reload
	movq	%rax, %r9
	movb	$0, %al
	callq	___snprintf_chk
	movl	%eax, -4196(%rbp)       ## 4-byte Spill
LBB1_2:
	leaq	L_.str.2(%rip), %rsi
	movl	$4096, %eax             ## imm = 0x1000
	movl	%eax, %edx
	leaq	-4112(%rbp), %rdi
	callq	___strcat_chk
	movq	___stdoutp@GOTPCREL(%rip), %rdx
	movq	(%rdx), %rdi
	movq	%rax, -4208(%rbp)       ## 8-byte Spill
	callq	_fflush
	movq	___stderrp@GOTPCREL(%rip), %rdx
	leaq	-4112(%rbp), %rdi
	movq	(%rdx), %rsi
	movl	%eax, -4212(%rbp)       ## 4-byte Spill
	callq	_fputs
	xorl	%ecx, %ecx
	movl	%ecx, %edi
	movl	%eax, -4216(%rbp)       ## 4-byte Spill
	callq	_fflush
	movq	___stack_chk_guard@GOTPCREL(%rip), %rdx
	movq	(%rdx), %rdx
	movq	-8(%rbp), %rsi
	cmpq	%rsi, %rdx
	movl	%eax, -4220(%rbp)       ## 4-byte Spill
	jne	LBB1_4
## %bb.3:
	addq	$4224, %rsp             ## imm = 0x1080
	popq	%rbp
	retq
LBB1_4:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_err_sys                ## -- Begin function err_sys
	.p2align	4, 0x90
_err_sys:                               ## @err_sys
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$400, %rsp              ## imm = 0x190
	testb	%al, %al
	movaps	%xmm7, -224(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -336(%rbp)       ## 16-byte Spill
	movq	%rdi, -344(%rbp)        ## 8-byte Spill
	movq	%r9, -352(%rbp)         ## 8-byte Spill
	movq	%r8, -360(%rbp)         ## 8-byte Spill
	movq	%rcx, -368(%rbp)        ## 8-byte Spill
	movq	%rdx, -376(%rbp)        ## 8-byte Spill
	movq	%rsi, -384(%rbp)        ## 8-byte Spill
	je	LBB2_2
## %bb.1:
	movaps	-336(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -160(%rbp)
	movaps	-320(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -144(%rbp)
	movaps	-304(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -128(%rbp)
	movaps	-288(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -112(%rbp)
	movaps	-272(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -96(%rbp)
	movaps	-256(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -80(%rbp)
	movaps	-240(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -64(%rbp)
	movaps	-224(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -48(%rbp)
LBB2_2:
	movq	-352(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -168(%rbp)
	movq	-360(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -176(%rbp)
	movq	-368(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -184(%rbp)
	movq	-376(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -192(%rbp)
	movq	-384(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -200(%rbp)
	movq	-344(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -8(%rbp)
	leaq	-208(%rbp), %r8
	movq	%r8, -16(%rbp)
	leaq	16(%rbp), %r8
	movq	%r8, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	callq	___error
	movl	(%rax), %esi
	movq	-8(%rbp), %rdx
	movl	$1, %r9d
	leaq	-32(%rbp), %rcx
	movl	%r9d, %edi
	movl	%r9d, -388(%rbp)        ## 4-byte Spill
	callq	_err_doit
	movl	-388(%rbp), %edi        ## 4-byte Reload
	callq	_exit
	.cfi_endproc
                                        ## -- End function
	.globl	_err_exit               ## -- Begin function err_exit
	.p2align	4, 0x90
_err_exit:                              ## @err_exit
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$416, %rsp              ## imm = 0x1A0
	testb	%al, %al
	movaps	%xmm7, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -336(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -352(%rbp)       ## 16-byte Spill
	movl	%edi, -356(%rbp)        ## 4-byte Spill
	movq	%r9, -368(%rbp)         ## 8-byte Spill
	movq	%r8, -376(%rbp)         ## 8-byte Spill
	movq	%rcx, -384(%rbp)        ## 8-byte Spill
	movq	%rdx, -392(%rbp)        ## 8-byte Spill
	movq	%rsi, -400(%rbp)        ## 8-byte Spill
	je	LBB3_2
## %bb.1:
	movaps	-352(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -176(%rbp)
	movaps	-336(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -160(%rbp)
	movaps	-320(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -144(%rbp)
	movaps	-304(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -128(%rbp)
	movaps	-288(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -112(%rbp)
	movaps	-272(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -96(%rbp)
	movaps	-256(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -80(%rbp)
	movaps	-240(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -64(%rbp)
LBB3_2:
	movq	-368(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -184(%rbp)
	movq	-376(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -192(%rbp)
	movq	-384(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -200(%rbp)
	movq	-392(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -208(%rbp)
	movq	-400(%rbp), %rdi        ## 8-byte Reload
	movl	-356(%rbp), %r8d        ## 4-byte Reload
	movl	%r8d, -4(%rbp)
	movq	%rdi, -16(%rbp)
	leaq	-224(%rbp), %rdi
	movq	%rdi, -32(%rbp)
	leaq	16(%rbp), %rdi
	movq	%rdi, -40(%rbp)
	movl	$48, -44(%rbp)
	movl	$16, -48(%rbp)
	movl	-4(%rbp), %esi
	movq	-16(%rbp), %rdx
	movl	$1, %r8d
	leaq	-48(%rbp), %rcx
	movl	%r8d, %edi
	movl	%r8d, -404(%rbp)        ## 4-byte Spill
	callq	_err_doit
	movl	-404(%rbp), %edi        ## 4-byte Reload
	callq	_exit
	.cfi_endproc
                                        ## -- End function
	.globl	_err_dump               ## -- Begin function err_dump
	.p2align	4, 0x90
_err_dump:                              ## @err_dump
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$384, %rsp              ## imm = 0x180
	testb	%al, %al
	movaps	%xmm7, -224(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -336(%rbp)       ## 16-byte Spill
	movq	%rdi, -344(%rbp)        ## 8-byte Spill
	movq	%r9, -352(%rbp)         ## 8-byte Spill
	movq	%r8, -360(%rbp)         ## 8-byte Spill
	movq	%rcx, -368(%rbp)        ## 8-byte Spill
	movq	%rdx, -376(%rbp)        ## 8-byte Spill
	movq	%rsi, -384(%rbp)        ## 8-byte Spill
	je	LBB4_2
## %bb.1:
	movaps	-336(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -160(%rbp)
	movaps	-320(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -144(%rbp)
	movaps	-304(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -128(%rbp)
	movaps	-288(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -112(%rbp)
	movaps	-272(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -96(%rbp)
	movaps	-256(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -80(%rbp)
	movaps	-240(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -64(%rbp)
	movaps	-224(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -48(%rbp)
LBB4_2:
	movq	-352(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -168(%rbp)
	movq	-360(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -176(%rbp)
	movq	-368(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -184(%rbp)
	movq	-376(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -192(%rbp)
	movq	-384(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -200(%rbp)
	movq	-344(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -8(%rbp)
	leaq	-208(%rbp), %r8
	movq	%r8, -16(%rbp)
	leaq	16(%rbp), %r8
	movq	%r8, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	callq	___error
	movl	(%rax), %esi
	movq	-8(%rbp), %rdx
	movl	$1, %edi
	leaq	-32(%rbp), %rcx
	callq	_err_doit
	callq	_abort
	.cfi_endproc
                                        ## -- End function
	.globl	_err_msg                ## -- Begin function err_msg
	.p2align	4, 0x90
_err_msg:                               ## @err_msg
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$416, %rsp              ## imm = 0x1A0
	testb	%al, %al
	movaps	%xmm7, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -336(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -352(%rbp)       ## 16-byte Spill
	movq	%rdi, -360(%rbp)        ## 8-byte Spill
	movq	%r9, -368(%rbp)         ## 8-byte Spill
	movq	%r8, -376(%rbp)         ## 8-byte Spill
	movq	%rcx, -384(%rbp)        ## 8-byte Spill
	movq	%rdx, -392(%rbp)        ## 8-byte Spill
	movq	%rsi, -400(%rbp)        ## 8-byte Spill
	je	LBB5_4
## %bb.3:
	movaps	-352(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -176(%rbp)
	movaps	-336(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -160(%rbp)
	movaps	-320(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -144(%rbp)
	movaps	-304(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -128(%rbp)
	movaps	-288(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -112(%rbp)
	movaps	-272(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -96(%rbp)
	movaps	-256(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -80(%rbp)
	movaps	-240(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -64(%rbp)
LBB5_4:
	movq	-368(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -184(%rbp)
	movq	-376(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -192(%rbp)
	movq	-384(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -200(%rbp)
	movq	-392(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -208(%rbp)
	movq	-400(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -216(%rbp)
	movq	-360(%rbp), %r8         ## 8-byte Reload
	xorl	%r9d, %r9d
	leaq	-32(%rbp), %r10
	movq	___stack_chk_guard@GOTPCREL(%rip), %r11
	movq	(%r11), %r11
	movq	%r11, -8(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r10, %r8
	leaq	-224(%rbp), %r11
	movq	%r11, 16(%r8)
	leaq	16(%rbp), %r11
	movq	%r11, 8(%r8)
	movl	$48, 4(%r8)
	movl	$8, (%r8)
	movq	-40(%rbp), %rdx
	movl	%r9d, %edi
	movl	%r9d, %esi
	movq	%r10, %rcx
	callq	_err_doit
	leaq	-32(%rbp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movq	%rax, -408(%rbp)        ## 8-byte Spill
	jne	LBB5_2
## %bb.1:
	addq	$416, %rsp              ## imm = 0x1A0
	popq	%rbp
	retq
LBB5_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_err_quit               ## -- Begin function err_quit
	.p2align	4, 0x90
_err_quit:                              ## @err_quit
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$384, %rsp              ## imm = 0x180
	testb	%al, %al
	movaps	%xmm7, -224(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -336(%rbp)       ## 16-byte Spill
	movq	%rdi, -344(%rbp)        ## 8-byte Spill
	movq	%r9, -352(%rbp)         ## 8-byte Spill
	movq	%r8, -360(%rbp)         ## 8-byte Spill
	movq	%rcx, -368(%rbp)        ## 8-byte Spill
	movq	%rdx, -376(%rbp)        ## 8-byte Spill
	movq	%rsi, -384(%rbp)        ## 8-byte Spill
	je	LBB6_2
## %bb.1:
	movaps	-336(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -160(%rbp)
	movaps	-320(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -144(%rbp)
	movaps	-304(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -128(%rbp)
	movaps	-288(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -112(%rbp)
	movaps	-272(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -96(%rbp)
	movaps	-256(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -80(%rbp)
	movaps	-240(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -64(%rbp)
	movaps	-224(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -48(%rbp)
LBB6_2:
	movq	-352(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -168(%rbp)
	movq	-360(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -176(%rbp)
	movq	-368(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -184(%rbp)
	movq	-376(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -192(%rbp)
	movq	-384(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -200(%rbp)
	movq	-344(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -8(%rbp)
	leaq	-208(%rbp), %r8
	movq	%r8, -16(%rbp)
	leaq	16(%rbp), %r8
	movq	%r8, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	movq	-8(%rbp), %rdx
	xorl	%r9d, %r9d
	leaq	-32(%rbp), %rcx
	movl	%r9d, %edi
	movl	%r9d, %esi
	callq	_err_doit
	movl	$1, %edi
	callq	_exit
	.cfi_endproc
                                        ## -- End function
	.globl	_alarm_handler          ## -- Begin function alarm_handler
	.p2align	4, 0x90
_alarm_handler:                         ## @alarm_handler
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	$0, _flag(%rip)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$14, %edi
	leaq	_alarm_handler(%rip), %rsi
	movl	$0, -4(%rbp)
	callq	_signal
	movl	$5, %edi
	movq	%rax, -16(%rbp)         ## 8-byte Spill
	callq	_alarm
	movl	$1, _flag(%rip)
	movl	%eax, -20(%rbp)         ## 4-byte Spill
LBB8_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	_flag(%rip), %eax
	cmpl	$0, %eax
	je	LBB8_3
## %bb.2:                               ##   in Loop: Header=BB8_1 Depth=1
	movq	_count(%rip), %rax
	addq	$1, %rax
	movq	%rax, _count(%rip)
	jmp	LBB8_1
LBB8_3:
	leaq	L_.str(%rip), %rdi
	movq	_count(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_count                  ## @count
.zerofill __DATA,__common,_count,8,3
	.section	__DATA,__data
	.p2align	2               ## @flag
_flag:
	.long	1                       ## 0x1

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%lld\n"

L_.str.1:                               ## @.str.1
	.asciz	": %s"

L_.str.2:                               ## @.str.2
	.asciz	" "


.subsections_via_symbols
