.data
buffer: .asciz "Countdown: 0!\n"
buffer_len: .long 15

.text

.global _start

_start:
    pushw $10

loop:
    movl $0x04, %eax
    movl $0x01, %ebx
    movl $buffer, %ecx
    movl buffer_len, %edx
    int $0x80

    movl $buffer, %eax
    addl $11, %eax
    incl (%eax)

    popw %cx
    decw %cx
    pushw %cx

    cmpw $0, %cx
    jne loop

    movl $0x01, %eax
    xorl %ebx, %ebx
    int $0x80
