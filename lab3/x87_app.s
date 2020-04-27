.data
    # Nowe dyrektywy .float i .double służą do umieszczania liczb
    # zmiennoprzecinkowych pojedynczej i podwójnej precyzji. Narzędzie "as"
    # dokona niezbędnej konwersji z tzw. zapisu zrozumiałego dla człowieka na
    # binarny format IEEE 754, zrozumiały dla procesora.
    arg_f: .float  3.141592
    arg_d: .double 3.141592

    fmt_i: .asciz "\nIteracja: %d\n"
    fmt_f: .asciz "Liczba float:  %.6f\n"
    fmt_d: .asciz "Liczba double: %.6f\n"

.global main
.text

main:
    finit               # Inicjalizacja koprocesora x87
    xorl %ebx, %ebx     # Zerujemy rejestr EBX, który będzie licznikiem pętli

# Pętla, która 25 razy pomnoży liczbę float i double przez wartość licznika
# pętli, a następnie wyświetli je na standardowym wyjściu. Po kilku iteracjach
# uwidoczni się błąd zaokrąglania wynikający z różnej precyzji typów float oraz
# double.

iter:
    # Wyświetl komunikat z numerem obecnej iteracji
    pushl %ebx
    pushl $fmt_i
    call printf
    addl $8, %esp

    # Pomnóż liczbę double "arg_d" przez wartość rejestru EBX. W tym celu
    # odkładamy obie liczby na stosie koprocesora x87 i wykonujemy mnożenie.
    # Wynik działania wyświetlamy za pomocą printf().

    # *** SEKCJA 1 ***

    # Nie można bezpośrednio załadować liczb całkowitych z rejestrów EAX, EBX,
    # etc. do rejestrów x87. x87 pozwala ładować liczby całkowite z pamięci.
    # W tym celu robimy pewien trik. Odkładamy liczbę w rejestrze EBX na stos,
    # a następnie ładujemy ją do rejestrów x87 spod adresu w rejestrze ESP,
    # który wskazuje na szczyt stosu.

    # W składni GNU Assembler dla x86 rejestru x87 nazywają się st(0), st(1),
    # st(3) itd. aż do st(7). Odwołujemy się do korzystając ze znaku '%', tak
    # jak widzicie poniżej.

    fldl arg_d          # Załaduj na szczyt stosu rejestrów x87 liczbę spod
                        # adresu arg_d
    pushl %ebx          # Ładujemy liczbę całkowitą do rejestrów x87, w sposób
                        # opisany powyżej
    fildl (%esp)
    addl $4, %esp
    fmul %st(1), %st(0) # Wykonujemy mnożenie liczb zmiennoprzecinkowych w
                        #rejestrach ST0 i ST1, a wynik zapisujemy do ST0

    # Liczby zmiennoprzecinkowe przekazujemy do funkcji printf() tak jak
    # wszystkie inne argumenty - tj. przez stos. W tym celu rezerwujemy na
    # stosie odpowiednią ilość miejsca (8 bajtów dla double i 4 bajty dla
    # float), a następnie kopiujemy zawartość
    
    subl $8, %esp   # Rezerwujemy miejsce na stosie - 8 bajtów, bo wyświetlamy 
                    # liczbę double.
    fstpl (%esp)    # Ładujemy liczbę ze szczytu stosu rejestrów x87 (rejestr ST0)
    pushl $fmt_d    # Odkładamy na stos adres formatu dla printf()
    call printf     # Wykonujemy printf()
    addl $12, %esp  # Sprzątamy po sobie - cofamy stos o 12 bajtów (wskaźnik 
                    # na format 4 bajty + liczba double 8 bajtów)

    # *** SEKCJA 2 ***

    # Wykonujemy działanie analogiczne do tego opisanego powyżej, ale na
    # liczbach typu float (mniejszej precyzji). Porównaj uważnie kod w
    # sekcjach 1 i 2.

    flds arg_f      # Instrukcja flds ładuje liczbę typu float z pamięci na
                    # szczyt stosu rejestrów x86
    pushl %ebx
    fildl (%esp)
    addl $4, %esp
    fmulp           # Działa podobnie jak fmul + zdejmuje rekjestr ze szczytu
                    # stosu. Innymi słowy robi:
                    #   1. ST1 = ST0 + ST1
                    #   2. Zdejmuje ST0 ze stosu (ST staje się nowym ST0, czyli 
                    #                             szczytem stosu)

    subl $8, %esp
    fstpl (%esp)
    pushl $fmt_f
    call printf
    addl $12, %esp

    # Warunek pętli
    incl %ebx
    cmp $25, %ebx
    jle iter

    # Koniec programu
    movl $1, %eax
    movl $0, %ebx
    int $0x80
