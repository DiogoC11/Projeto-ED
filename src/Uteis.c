
#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"

/*int Aleatorio(int min, int max){
    return min + rand() % (max - min + 1);
}

int Factorial(int N){
    if (N == 0) return 1;
    return N * Factorial(N-1);
}*/

int LerInteiro(char *txt){
    int x;
    printf("%s : ", txt);
    do {
        scanf("%d", &x);
        if (isdigit(x) == 1) {
            printf("\nErro: Deve inserir um inteiro\n");
        }
    }while (isdigit(x) == 1);
    return x;
}
