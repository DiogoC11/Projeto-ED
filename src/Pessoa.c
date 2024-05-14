#include <stdio.h>
#include <stdlib.h>
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
    printf("\nM�s: ");
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

void *AdicionarPessoa(Lista_Chaves_P *C,ElementoP *E){
    if(!C) return NULL;
    if(!E) return NULL;
    int a = 0;
    NO_CHAVE_P *N = C->Inicio;
    for(int i = 0; i < C->num_chaves; i++){
        if(N->Key == E->pessoa->PrimeiroNome[0]){
            if(C->Inicio->DADOS->Inicio==0) {
                C->Inicio->DADOS->Inicio = E;
            }else{
                ElementoP *ultimo = C->Inicio->DADOS->Inicio;
                while (ultimo->proximo != NULL){
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = E;
            }
            a=1;
            C->Inicio->DADOS->num_Pessoas ++;
        }
        N = N->Prox;
    }
    if(!a){
        char key = E->pessoa->PrimeiroNome[0];
        criarNoChave(key);
        C->num_chaves ++;
        C->Inicio->DADOS->Inicio = E;
        C->Inicio->DADOS->num_Pessoas ++;
    }
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

int compararUltimoNome(const void *a, const void *b) {
    PESSOA *pessoaA = (*(ElementoP **)a)->pessoa;
    PESSOA *pessoaB = (*(ElementoP **)b)->pessoa;
    return strcmp(pessoaA->UltimoNome, pessoaB->UltimoNome);
}

int compararPrimeiroNome(const void *a, const void *b) {
    PESSOA *pessoaA = (*(ElementoP **)a)->pessoa;
    PESSOA *pessoaB = (*(ElementoP **)b)->pessoa;
    return strcmp(pessoaA->PrimeiroNome, pessoaB->PrimeiroNome);
}

void *OrganizarPorNome(ListaPessoa *L, int op){
    ElementoP **arrayElementos = malloc(L->num_Pessoas * sizeof(ElementoP *));
    if (arrayElementos == NULL) {
        perror("Erro ao alocar mem�ria para o array de elementos");
        exit(EXIT_FAILURE);
    }
    if(op == 1){
        qsort(arrayElementos, L->num_Pessoas, sizeof(ElementoP *), compararUltimoNome);
    }else if(op==2){
        qsort(arrayElementos, L->num_Pessoas, sizeof(ElementoP *), compararPrimeiroNome);
    }else if(op == 3){
        //funcao de comparar id de freguesias
    }
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

// Fun��o para criar um novo n� de chave
NO_CHAVE_P *criarNoChave(char chave) {
    NO_CHAVE_P *novoNoChave = (NO_CHAVE_P *)malloc(sizeof(NO_CHAVE_P));
    if (novoNoChave != NULL) {
        novoNoChave->Key = chave;
        novoNoChave->DADOS = criarListaP();
        novoNoChave->Prox = NULL;
    }
    return novoNoChave;
}

// Fun��o para inserir uma pessoa na tabela de hashing
void inserirPessoaHash(NO_CHAVE_P **tabela, char *chave, PESSOA *pessoa) {
    int indice = chave[0] - 'A'; // Supondo que as chaves sejam letras mai�sculas de A a Z
    NO_CHAVE_P *atual = tabela[indice];
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
    AdicionarPessoa(atual->DADOS, pessoa);
}

// Fun��o percorrer as pessoas a busca se o id � identifco ao parametro
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

    // L� cada linha do arquivo at� encontrar o fim do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, "\t"); // Divide a linha em tokens usando o caractere de tabula��o como delimitador
        if (token != NULL) {
            // O primeiro token � o ID requisitante
            if (strcmp(token, idRequisitante) == 0) {
                fclose(arquivo); // Fecha o arquivo
                return 1; // Retorna verdadeiro se o ID requisitante for encontrado
            }
        }
    }

    fclose(arquivo); // Fecha o arquivo
    return 0; // Retorna falso se o ID requisitante n�o for encontrado
}
