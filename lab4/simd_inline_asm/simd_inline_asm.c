#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const uint16_t a[] = { 1, 2, 4, 8 };
static uint16_t b[4];
static const uint16_t c[] = { 10, 100, 1000, 10000 };
static uint16_t d[4];

int main()
{
    __asm__(
        "movq %2, %%mm0\n"
        "psllw $1, %%mm0\n"
        "movq %%mm0, %%mm1\n"
        "movq %3, %%mm2\n"
        "paddw %%mm2, %%mm1\n"
        "movq %%mm0, %0\n"
        "movq %%mm1, %1\n"
        : "=m"(b), "=m" (d)
        : "m" (a), "m" (c)
    );
    
    printf("a = [%d, %d, %d, %d]\n", a[0], a[1], a[2], a[3]);
    printf("c = [%d, %d, %d, %d]\n", c[0], c[1], c[2], c[3]);
    printf("b = a << 1 : [%d, %d, %d, %d]\n", b[0], b[1], b[2], b[3]);
    printf("d = b + c  : [%d, %d, %d, %d]\n", d[0], d[1], d[2], d[3]);
    return 0;
}
