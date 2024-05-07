#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Pessoa.h"

/** \brief Permite Alocar e inicializar uma estrutura Pessoa
 *
 * \param _id int
 * \param _nome char*
 * \param _categoria char*
 * \return PESSOA*
 *
 */


PESSOA *CriarPessoa(char *_nome, char *dataNascimento)
{
    PESSOA *P = (PESSOA *)malloc(sizeof(PESSOA));
    P->NOME = (char *)malloc((strlen(_nome) + 1)*sizeof(char));
    strcpy(P->NOME, _nome);
    P->dataNascimento = (char *)malloc((strlen(dataNascimento) + 1)*sizeof(char));
    strcpy(P->dataNascimento, dataNascimento);
    P->ID = GerarID();
    return P;
}

PESSOA *PedirDadosPessoa(){
    int _id,dia[3],mes[3],ano[5];
    char nome[50],dataNascimento[9];
    printf("\nAdicionar Pessoa:\n");
    printf("\nNome: ");
    scanf("%s",nome);
    printf("\nData de nascimento: \n");
    printf("\nDia: ");
    scanf("%d",dia);
    printf("\nMês: ");
    scanf("%d",mes);
    printf("\nAno: ");
    scanf("%d",ano);
    sprintf(dataNascimento, "%02d-%02d-%02d", dia, mes, ano);
    return CriarPessoa(nome,dataNascimento);
}
ListaPessoa *criarListaP(){
    ListaPessoa *L = (ListaPessoa *) malloc(sizeof (ListaPessoa));
    if (!L) return NULL;
    L->num_Pessoas = 0;
    L->Inicio = NULL;
    return L;
}

ElementoP *criar_elementoP(PESSOA *L){
    ElementoP *e = (ElementoP * ) malloc(sizeof (ElementoP));
    if(!e) return NULL;
    e->pessoa = L;
    e->proximo = NULL;
    return e;
}

void *AdicionarPessoa(ListaPessoa *L,ElementoP *E){
    if(!L) return NULL;
    if(!E) return NULL;
    if(L->num_Pessoas == 0){
        L->Inicio = E;
    }else {
        ElementoP *ultimo = L->Inicio;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = E;
    }
    L->num_Pessoas ++;
    printf("\nPessoa adicionada a lista.\n");
}

void MostrarPessoa(PESSOA *P)
{
    printf("\tPESSOA: ID: %d [%s] [%s]\n", P->ID, P->NOME, P->dataNascimento);
}
void DestruirPessoa(PESSOA *P)
{
    free (P->NOME);
    free (P->dataNascimento);
    free (P);
}

int GerarID() {
    static int baseID = 100000000;  // Começa com um número de 9 dígitos.
    int sum = 0, id = baseID;
    int tempID = id;

    while (tempID > 0) {
        sum += tempID % 10;
        tempID /= 10;
    }

    // Calcula o dígito de controle necessário para fazer a soma um múltiplo de 10.
    int lastDigit = 10 - (sum % 10);
    if (lastDigit == 10) lastDigit = 0;

    id += lastDigit;  // Adiciona o dígito de controle ao final do ID.
    baseID++;  // Incrementa a base para o próximo ID.
     */
    int numero_aleatorio;
    srand(time(NULL));
    numero_aleatorio = rand() % 900000000 + 100000000;
    for (int i = 0; i < L->num_Pessoas; i++) {
        if ( E->pessoa->ID == numero_aleatorio) {
            printf("Problema com funcao GerarID");
            return 0; // Número encontrado na lista
        }
    }


    return id;
}
