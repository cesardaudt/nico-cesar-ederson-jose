# as output.s -o output.o
# ld -dynamic-linker /lib/ld-linux.so.2 -o output -lc output.o
# ./output


.section .data					# MEM
	filo:	.space 44			# allocates space for STACK based on TAC
	temp:	.space 136			# allocates space for HEAP based on TAC.

	intf:	.string "%d\n"			# integer format for printing.
	
		.equ LINUX_SYSCALL , 0x80	# alias for invoking a system call through INT.

#------------------------------------------------------------------------------

.section .text					# CODE
	.extern printf
	.global _start				# enables linker (ld) to see it.
	.align 4				# ensures word (4 bytes, 32 bits) align of instructions.
	
	_start:	MOVL  $filo , %ECX		# register %ECX gets SP reference.
		MOVL  $temp , %EDX		# register %EDX gets Rx reference.

	_000:	LEAL 24(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $46 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_001:	LEAL 12(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $34 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_002:	LEAL 8(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $90 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_003:	LEAL 16(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $10 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_004:	LEAL 4(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $124 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_005:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL $137 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_006:	LEAL 16(%ECX) , %EAX
		PUSHL  %EAX
		MOVL $25 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_007:	MOVL  24(%ECX) , %EAX
		ADDL  (%ECX) , %EAX
		MOVL  %EAX ,(%EDX)

	_008:	MOVL  (%EDX) , %EAX
		ADDL  (%ECX) , %EAX
		MOVL  %EAX ,4(%EDX)

	_009:	MOVL  4(%EDX) , %EAX
		ADDL  24(%ECX) , %EAX
		MOVL  %EAX ,8(%EDX)

	_010:	MOVL  $40 , %EAX
		IMULL $10 , %EAX
		MOVL  %EAX ,12(%EDX)

	_011:	MOVL   12(%EDX) , %EAX
		MOVL   $20 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 16(%EDX)

	_012:	MOVL  8(%EDX) , %EAX
		ADDL  16(%EDX) , %EAX
		MOVL  %EAX ,20(%EDX)

	_013:	MOVL   $8 , %EAX
		MOVL   $3 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 24(%EDX)

	_014:	MOVL  20(%EDX) , %EAX
		ADDL  24(%EDX) , %EAX
		MOVL  %EAX ,28(%EDX)

	_015:	MOVL  28(%EDX) , %EAX
		ADDL  $2 , %EAX
		MOVL  %EAX ,32(%EDX)

	_016:	LEAL 24(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 32(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_017:	MOVL   (%ECX) , %EAX
		MOVL   $3 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 36(%EDX)

	_018:	MOVL   36(%EDX) , %EAX
		MOVL   $2 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 40(%EDX)

	_019:	MOVL   40(%EDX) , %EAX
		MOVL   $1 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 44(%EDX)

	_020:	MOVL   44(%EDX) , %EAX
		MOVL   $5 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 48(%EDX)

	_021:	MOVL   48(%EDX) , %EAX
		MOVL   $5 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 52(%EDX)

	_022:	MOVL  52(%EDX) , %EAX
		IMULL $9 , %EAX
		MOVL  %EAX ,56(%EDX)

	_023:	MOVL  56(%EDX) , %EAX
		IMULL $0 , %EAX
		MOVL  %EAX ,60(%EDX)

	_024:	MOVL  60(%EDX) , %EAX
		IMULL $1 , %EAX
		MOVL  %EAX ,64(%EDX)

	_025:	MOVL  64(%EDX) , %EAX
		IMULL $3 , %EAX
		MOVL  %EAX ,68(%EDX)

	_026:	MOVL  8(%ECX) , %EAX
		SUBL  68(%EDX) , %EAX
		MOVL  %EAX ,72(%EDX)

	_027:	LEAL 8(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 72(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_028:	MOVL  16(%ECX) , %EAX
		IMULL 16(%ECX) , %EAX
		MOVL  %EAX ,76(%EDX)

	_029:	MOVL  76(%EDX) , %EAX
		ADDL  24(%ECX) , %EAX
		MOVL  %EAX ,80(%EDX)

	_030:	MOVL  80(%EDX) , %EAX
		ADDL  32(%ECX) , %EAX
		MOVL  %EAX ,84(%EDX)

	_031:	MOVL  84(%EDX) , %EAX
		ADDL  16(%ECX) , %EAX
		MOVL  %EAX ,88(%EDX)

	_032:	MOVL  88(%EDX) , %EAX
		ADDL  12(%ECX) , %EAX
		MOVL  %EAX ,92(%EDX)

	_033:	LEAL 16(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 92(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_034:	MOVL   16(%ECX) , %EAX
		MOVL   $0 , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 96(%EDX)

	_035:	MOVL  96(%EDX) , %EAX
		IMULL 8(%ECX) , %EAX
		MOVL  %EAX ,100(%EDX)

	_036:	MOVL   100(%EDX) , %EAX
		MOVL   4(%ECX) , %EBX
		PUSHL %EDX
		XORL   %EDX , %EDX
		IDIVL  %EBX
		MOVL   %EDX, %EBX
		POPL   %EDX
		MOVL   %EAX , 104(%EDX)

	_037:	MOVL  104(%EDX) , %EAX
		IMULL 4(%ECX) , %EAX
		MOVL  %EAX ,108(%EDX)

	_038:	MOVL  108(%EDX) , %EAX
		IMULL 12(%ECX) , %EAX
		MOVL  %EAX ,112(%EDX)

	_039:	LEAL 32(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 112(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_040:	MOVL  (%ECX) , %EAX
		IMULL $2 , %EAX
		MOVL  %EAX ,116(%EDX)

	_041:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL 116(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_042:	MOVL  16(%ECX) , %EAX
		ADDL  $1 , %EAX
		MOVL  %EAX ,120(%EDX)

	_043:	LEAL 16(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 120(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_044:	MOVL  (%ECX) , %EAX
		IMULL $2 , %EAX
		MOVL  %EAX ,124(%EDX)

	_045:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL 124(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_046:	MOVL  16(%ECX) , %EAX
		ADDL  $1 , %EAX
		MOVL  %EAX ,128(%EDX)

	_047:	LEAL 16(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 128(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_048:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL $1 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_049:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL $2 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_050:	LEAL (%ECX) , %EAX
		PUSHL  %EAX
		MOVL $4 , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_051:	LEAL 132(%EDX) , %EAX
		PUSHL  %EAX
		MOVL 24(%ECX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_052:	LEAL 24(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 8(%ECX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_053:	LEAL 8(%ECX) , %EAX
		PUSHL  %EAX
		MOVL 132(%EDX) , %EBX
		POPL %EAX
		MOVL %EBX , (%EAX)

	_054:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  16(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_055:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  (%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_056:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  24(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_057:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  8(%ECX)
		PUSHL  $intf
		CALL printf
		POPL  %EAX
		POPL  %EAX
		POPL  %EDX
		POPL  %ECX

	_058:	PUSHL  %ECX
		PUSHL  %EDX
		PUSHL  4(%ECX)
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
