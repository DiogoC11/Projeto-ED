
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ctype.h"
#include <time.h>//necessário p/ função time()

int Aleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int Factorial(int N)
{
    if (N == 0) return 1;
    return N * Factorial(N-1);
}

int LerInteiro(char *txt)
{
    int x;
    printf("%s : ", txt);
    do {
        scanf("%d", &x);
        if (isdigit(x) == 0) {
            printf("\nErro: Deve inserir um inteiro\n");
        }
    }while (isdigit(x) == 0);
    return x;
}
