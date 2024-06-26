#ifndef EXEM_PROJETO_UTEIS_H
#define EXEM_PROJETO_UTEIS_H

int Aleatorio();
int LerInteiro(char *txt);
void limparBuffer();
void lerString(char *str, int tamanho);
void removeSpaces(char* input);
void EscreverLogs(const char *mensagem);
int validarData(int dia, int mes, int ano);
int contem_numero(char *array);
void rtrim(char *str);
int isStringEmptyOrSpaces(const char *str);
char *trim(char *str);
#endif //EXEM_PROJETO_UTEIS_H
