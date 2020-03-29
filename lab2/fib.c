#include <stdio.h>

extern int fib(int);

int main(void)
{
    int input;
    printf("Podaj liczbe: ");
    scanf("%d", &input);
    printf("Wynik: %d\n", fib(input));
}
