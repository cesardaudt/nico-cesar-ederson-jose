# as output.s -o output.o
# ld -dynamic-linker /lib/ld-linux.so.2 -o output -lc output.o
# ./output


.section .data					# MEM
	filo:	.space 12			# allocates space for STACK based on TAC
	temp:	.space 12			# allocates space for HEAP based on TAC.

	intf:	.string "%d\n"			# integer format for printing.
	
		.equ LINUX_SYSCALL , 0x80	# alias for invoking a system call through INT.

#------------------------------------------------------------------------------

.section .text					# CODE
	.extern printf
	.global _start				# enables linker (ld) to see it.
	.align 4				# ensures word (4 bytes, 32 bits) align of instructions.
	
	_start:	MOVL  $filo , %ECX		# register %ECX gets SP reference.
		MOVL  $temp , %EDX		# register %EDX gets Rx reference.

	_000:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL $2 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_001:	LEAL 4(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $4 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_002:	LEAL 8(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $2 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_003:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  (%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_004:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  4(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_005:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  8(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_006:	MOVL  (%ECX) , %EAX
		ADDL  4(%ECX) , %EAX
		MOVL  %EAX ,(%EDX)

	_007:	MOVL  (%EDX) , %EAX
		SUBL  8(%ECX) , %EAX
		MOVL  %EAX ,4(%EDX)

	_008:	MOVL   4(%EDX) , %EAX
		MOVL   (%ECX) , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 8(%EDX)

	_009:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL 8(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_010:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  (%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_011:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  4(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_012:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  8(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_exit:
		PUSH stdout
		CALL fflush			# call fflush(stdout)
		MOVL $1 , %EAX 
		MOVL $0 , %EBX 
		INT $LINUX_SYSCALL		# abruptly terminate (exit() crashes, hehe)
.end
