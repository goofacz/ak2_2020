all: inline_asm asm

asm: inline_asm.c
	gcc -g -O0 -m32 inline_asm.c -S

inline_asm: inline_asm.c
	gcc -g -O0 -m32 inline_asm.c -o inline_asm
