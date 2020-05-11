#include <stdint.h>
#include <stdio.h>

uint32_t a = 25;
uint32_t g;

int main()
{
    uint32_t b = 5;
    uint32_t c;

    __asm__ (
        /* c = a * b */
        "movl %1, %%eax\n" 
        "mull %2\n"
        "movl %%eax, %0\n"
        : "=r"(c) /* Zmienna "c" ma byc przekazana przez rejestr (kompilator wybierze odpowiedni rejestr) */
        : "m"(a), /* Zmienna "a" będzie dostępna przez adres (kompilator zapweni odpowiedni tryb dostępu) */
          "r"(b) /* Zmienna "b" ma byc przekazana przez rejestr (kompilator wybierze odpowiedni rejestr) */
        : "%eax", /* Jawnie nadpisujemy wartosc rejestru EAX we wstawce, wiec informujemy o tym kompilator.
                   * GCC zadba o to, zeby zachowac wartość rejetry EAX przed wejście do wstawki i odtworzyc 
                   * ja po wyjsciu ze wstawki. Jak to zrobi? Np. odlozy wartosc rejestru EAX na stos.*/
          "%edx"  /* Nie zmieniamy wprost wartosci rejestru EDX, ale uzywamy instrukcji, ktora to robi
                   * niejawnie. Instrukcja "mull" zapisuje wynik mnozenia w parze rejestrow EDX:EAX! */
    );
    
    printf("Simple case:\n[a * b = c] :   %d * %d = %d\n", a, b, c);
    
    uint32_t d = 15;
    uint32_t e;

    __asm__ (
        /* e = c -d */
        "subl %%ecx, %%ebx\n" 
        "movl %%ebx, %%eax\n"
        : "=a"(e) /* Prosimy kompilator zeby dal na dostep do zmiennej "a" przez rejestr EAX */
        : "b"(c), "c"(d) /* Analigocznie prosimy GCC zeby umiescilo dla nasz zmienne "c" i "d" w rejestrach
                          * EBX i ECX*/
        : /* Nie modifikujemy zadnych rejestr, poza tymi wymienionymi na listach powyzej. */
    );
    
    printf("[c - d = e] : %d - %d = %d\n", c, d, e);
    
    uint32_t f = 20;

    __asm__ (
        /* g = e + f */
        "xorl %%ecx, %%ecx\n"
        "addl %1, %%ecx\n" 
        "addl %2, %%ecx\n" 
        "movl %%ecx, %0\n"
        : "=d"(g)
        : "r"(c), "r"(d)
        : "%ecx"
    );
    
    printf("[e + f = g] : %d + %d = %d\n", e, f, g);

    return 0;
}
