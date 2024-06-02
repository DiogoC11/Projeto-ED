
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include "ctype.h"

int Aleatorio(){
    return rand() % 10;
}

int Factorial(int N){
    if (N == 0) return 1;
    return N * Factorial(N-1);
}

int LerInteiro(char *txt){
    int x;
    printf("%s : ", txt);
    scanf("%ld", &x);
    return x;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *str, int tamanho) {
    if (fgets(str, tamanho, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len-1] == '\n') {
            str[len-1] = '\0';
        }
    }
}


