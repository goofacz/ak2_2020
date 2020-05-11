all: simd_inline_asm asm

asm: simd_inline_asm.c
	gcc -g -O0 -m32 simd_inline_asm.c -S

simd_inline_asm: simd_inline_asm.c
	gcc -g -O0 -m32 simd_inline_asm.c -o simd_inline_asm
