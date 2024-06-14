
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <time.h>
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
void removeSpaces(char* input){
    int count = 0;
    int i;
    for (i = 0; input[i]; i++) {
        if (input[i] != ' ') {
            input[count++] = input[i];
        }
    }
    input[count] = '\0';
}

void EscreverLogs(const char *mensagem) {
    FILE *logFile = fopen("../data/log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "%s\n", mensagem);
        fclose(logFile);
    } else {
        printf("Erro ao abrir o arquivo de logs.\n");
    }
}

int validarData(int dia, int mes, int ano) {
    time_t t = time(NULL);
    struct tm hoje = *localtime(&t);

    if (ano < 1000 || ano > 2024) {
        return 0;
    }
    if (mes < 1 || mes > 12 ){

        return 0;
    }
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }

    if (dia < 1 || dia > diasNoMes[mes - 1]) {
        return 0;
    }
    if( ano == hoje.tm_year + 1900 && mes > hoje.tm_mon + 1){
        return 0;
    }else if (ano == hoje.tm_year + 1900 && dia > hoje.tm_mday && mes == hoje.tm_mon + 1){
        return 0;
    }
    return 1;
}
