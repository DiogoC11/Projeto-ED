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


PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, int dia, int mes, int ano){
    PESSOA *P = (PESSOA *)malloc(sizeof(PESSOA));
    P->PrimeiroNome = (char *)malloc((strlen(primeiroNome) + 1)*sizeof(char));
    strcpy(P->NOME, primeiroNome);
    P->UltimoNome = (char *)malloc((strlen(ultimoNome) + 1)*sizeof(char));
    strcpy(P->UltimoNome,ultimoNome);
    P->NOME = (char *) malloc((strlen(primeiroNome)+ strlen(ultimoNome)+2)* sizeof(char));
    strcpy(P->NOME, primeiroNome);
    strcat(P->NOME, " ");
    strcat(P->NOME, ultimoNome);
    P->dataNascimento->dia = dia;
    P->dataNascimento->mes = mes;
    P->dataNascimento->ano = ano;

    return P;
}

PESSOA *PedirDadosPessoa(){
    int dia,mes,ano;
    char primeiroNome[30],ultimoNome[30];
    printf("\nAdicionar Pessoa:\n");
    printf("\nPrimeiro Nome: ");
    scanf("%s",primeiroNome);
    printf("\nUltimo Nome: ");
    scanf("%s",ultimoNome);
    printf("\nData de nascimento: \n");
    printf("\nDia: ");
    scanf("%d",dia);
    printf("\nMês: ");
    scanf("%d",mes);
    printf("\nAno: ");
    scanf("%d",ano);
    return CriarPessoa(primeiroNome,ultimoNome,dia,mes,ano);
}
ListaPessoa *criarListaP(){
    ListaPessoa *L = (ListaPessoa *) malloc(sizeof (ListaPessoa));
    if (!L) return NULL;
    L->num_Pessoas = 0;
    L->Inicio = NULL;
    return L;
}

ElementoP *criar_elementoP(PESSOA *P){
    ElementoP *e = (ElementoP * ) malloc(sizeof (ElementoP));
    if(!e) return NULL;
    e->pessoa = P;
    e->proximo = NULL;
    return e;
}

void *AdicionarPessoaInicio(ListaPessoa *L,ElementoP *E){
    if(!L) return NULL;
    if(!E) return NULL;
    if(L->num_Pessoas == 0){
        L->Inicio = E;
    }else{
        return NULL;
    }
    L->num_Pessoas ++;
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
    L->num_Pessoas++;
    printf("\nPessoa adicionada a lista.\n");
}

void *PesquisarPesssoaPorNome(ListaPessoa *L, char *nome) {
    if(!L ) return NULL;
    ElementoP *E = L->Inicio;
    for (int i = 0; i < L->num_Pessoas; i++) {
        if(strcmp(E->pessoa->NOME,nome) == 0){
            return E->pessoa;
        }
        E = E->proximo;
    }
    return NULL;
}

int compararPessoas(const void *a, const void *b) {
    PESSOA *pessoaA = (*(ElementoP **)a)->pessoa;
    PESSOA *pessoaB = (*(ElementoP **)b)->pessoa;
    return strcmp(pessoaA->UltimoNome, pessoaB->UltimoNome);
}

void *OrganizarPorApelido(ListaPessoa *L){
    ElementoP **arrayElementos = malloc(L->num_Pessoas * sizeof(ElementoP *));
    if (arrayElementos == NULL) {
        perror("Erro ao alocar memória para o array de elementos");
        exit(EXIT_FAILURE);
    }
    ElementoP *atual =  L->Inicio;

    qsort(arrayElementos, L->num_Pessoas, sizeof(ElementoP *), compararPessoas);
    for(int i = 0; i < L->num_Pessoas;i++){
        printf("Livro %d:\n", i+1);
        MostrarPessoa(arrayElementos[i]->pessoa);
    }
}

void *ListarPessoas(ListaPessoa *L){
    printf("\nLista de Livros:\n");
    ElementoP *E = L->Inicio;
    for (int i = 0; i < L->num_Pessoas; i++){
        printf("Livro %d:\n", i + 1);
        MostrarPessoa(E->pessoa);
        E = E->proximo;
    }
}

void MostrarPessoa(PESSOA *P)
{
    printf("\tPESSOA: ID: %d [%s] [%s]\n", P->ID, P->NOME, P->dataNascimento);
}

// Função para criar um novo nó de chave
NO_CHAVE *criarNoChave(char *chave) {
    NO_CHAVE *novoNoChave = (NO_CHAVE *)malloc(sizeof(NO_CHAVE));
    if (novoNoChave != NULL) {
        novoNoChave->KEY = chave;
        novoNoChave->DADOS = criarListaPessoa();
        novoNoChave->Prox = NULL;
    }
    return novoNoChave;
}

// Função para inserir uma pessoa na tabela de hashing
void inserirPessoaHash(NO_CHAVE **tabela, char *chave, PESSOA *pessoa) {
    int indice = chave[0] - 'A'; // Supondo que as chaves sejam letras maiúsculas de A a Z
    NO_CHAVE *atual = tabela[indice];
    if (atual == NULL) {
        tabela[indice] = criarNoChave(chave);
        atual = tabela[indice];
    } else {
        while (atual->Prox != NULL) {
            atual = atual->Prox;
        }
        atual->Prox = criarNoChave(chave);
        atual = atual->Prox;
    }
    inserirPessoa(atual->DADOS, pessoa);
}

// Função percorrer as pessoas a busca se o id é identifco ao parametro
PESSOA *buscarPessoaPorID(ptListaP lista, int id) {
    ptElementoP atual = lista->Inicio;
    while (atual != NULL) {
        if (atual->pessoa->ID == id) {
            return atual->pessoa;
        }
        atual = atual->proximo;
    }
    return NULL;
}

////------------- Percorrer

int verificarIDArquivo(char *idRequisitante) {
    FILE *arquivo = fopen("Requisitantes.txt", "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[100]; // Buffer para armazenar cada linha lida do arquivo

    // Lê cada linha do arquivo até encontrar o fim do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, "\t"); // Divide a linha em tokens usando o caractere de tabulação como delimitador
        if (token != NULL) {
            // O primeiro token é o ID requisitante
            if (strcmp(token, idRequisitante) == 0) {
                fclose(arquivo); // Fecha o arquivo
                return 1; // Retorna verdadeiro se o ID requisitante for encontrado
            }
        }
    }

    fclose(arquivo); // Fecha o arquivo
    return 0; // Retorna falso se o ID requisitante não for encontrado
}
