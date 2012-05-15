# as output.s -o output.o
# ld -dynamic-linker /lib/ld-linux.so.2 -o output -lc output.o
# ./output


.section .data					# MEM
	filo:	.space 12			# allocates space for STACK based on TAC
	temp:	.space 4			# allocates space for HEAP based on TAC.

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
		MOVL $7 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_001:	LEAL 4(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $87 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_002:	LEAL 8(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $90 , %EBX
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

	_004:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL $5 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_005:	LEAL (%EDX) , %EAX
		PUSHL  %EAX
		MOVL (%ECX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_006:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL 4(%ECX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_007:	LEAL 4(%ECX) , %EAX
		PUSHL  %EAX
		MOVL (%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_008:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  4(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_009:	PUSHL  %ECX
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
