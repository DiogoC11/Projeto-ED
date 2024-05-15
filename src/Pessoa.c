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

void *PesquisarPesssoaPorNome(Lista_Chaves_P *L, char *nome) {
    if(!L ) return NULL;
    NO_CHAVE_P *N = L->Inicio;
    ElementoP *E = N->DADOS->Inicio;

    for (int i = 0; i < L->num_chaves; i++) {
        for(int j = 0; j < L->Inicio[i].DADOS->num_Pessoas; j++){
            if(strcmp(E->pessoa->NOME,nome) == 0){
                return E->pessoa;
            }
            E = E->proximo;
        }
        N = N->Prox;
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
        perror("Erro ao alocar memória para o array de elementos");
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

// Função para criar um novo nó de chave
NO_CHAVE_P *criarNoChave(char chave) {
    NO_CHAVE_P *novoNoChave = (NO_CHAVE_P *)malloc(sizeof(NO_CHAVE_P));
    if (novoNoChave != NULL) {
        novoNoChave->Key = chave;
        novoNoChave->DADOS = criarListaP();
        novoNoChave->Prox = NULL;
    }
    return novoNoChave;
}

// Função para inserir uma pessoa na tabela de hashing
void inserirPessoaHash(NO_CHAVE_P **tabela, char *chave, PESSOA *pessoa) {
    int indice = chave[0] - 'A'; // Supondo que as chaves sejam letras maiúsculas de A a Z
    NO_CHAVE_P *atual = tabela[indice];
    if (atual == NULL) {
        tabela[indice] = criarNoChave(*chave);
        atual = tabela[indice];
    } else {
        while (atual->Prox != NULL) {
            atual = atual->Prox;
        }
        atual->Prox = criarNoChave(*chave);
        atual = atual->Prox;
    }
    AdicionarPessoa(atual->DADOS, pessoa);
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














// Função para ler o arquivo de freguesias e armazenar os dados em uma matriz de Freguesia
int lerFreguesias(const char* nome_arquivo, Freguesia **freguesias) {
    FILE *arquivo;
    char linha[150]; // Tamanho máximo da linha do arquivo
    int num_freguesias = 0;

    arquivo = fopen("./data/recursos/freguesias.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Alocar memória inicial para as freguesias
    *freguesias = malloc(sizeof(Freguesia));
    if (*freguesias == NULL) {
        perror("Erro ao alocar memória para as freguesias");
        exit(EXIT_FAILURE);
    }

    // Ler cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Realocar memória para armazenar mais uma freguesia
        *freguesias = realloc(*freguesias, (num_freguesias + 1) * sizeof(Freguesia));
        if (*freguesias == NULL) {
            perror("Erro ao realocar memória para as freguesias");
            exit(EXIT_FAILURE);
        }

        // Separar o código e o nome da freguesia
        char *token = strtok(linha, "\t");
        strcpy((*freguesias)[num_freguesias].codigo, token);
        token = strtok(NULL, "\t");
        strcpy((*freguesias)[num_freguesias].nome, token);

        num_freguesias++;
    }

    fclose(arquivo);
    return num_freguesias;
}

/*int lerRequisitantes(const char* nome_arquivo, Requisitante **requisitantes) {
    FILE *arquivo;
    char linha[200]; // Tamanho máximo da linha do arquivo
    int num_requisitantes = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Alocar memória inicial para os requisitantes
    *requisitantes = malloc(sizeof(Requisitante));
    if (*requisitantes == NULL) {
        perror("Erro ao alocar memória para os requisitantes");
        exit(EXIT_FAILURE);
    }

    // Ler cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Realocar memória para armazenar mais um requisitante
        *requisitantes = realloc(*requisitantes, (num_requisitantes + 1) * sizeof(Requisitante));
        if (*requisitantes == NULL) {
            perror("Erro ao realocar memória para os requisitantes");
            exit(EXIT_FAILURE);
        }

        // Separar os dados do requisitante
        char *token = strtok(linha, "\t");
        strcpy((*requisitantes)[num_requisitantes].codigo, token);

        token = strtok(NULL, "\t");
        strcpy((*requisitantes)[num_requisitantes].nome, token);

        token = strtok(NULL, "\t");
        strcpy((*requisitantes)[num_requisitantes].data_nascimento, token);

        token = strtok(NULL, "\t");
        (*requisitantes)[num_requisitantes].numero_requisicoes = atoi(token);

        num_requisitantes++;
    }

    fclose(arquivo);
    return num_requisitantes;
}
*/
int lerDistritos(const char* nome_arquivo, Distrito **distritos) {
    FILE *arquivo;
    char linha[100]; // Tamanho máximo da linha do arquivo
    int num_distritos = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Alocar memória inicial para os distritos
    *distritos = malloc(sizeof(Distrito));
    if (*distritos == NULL) {
        perror("Erro ao alocar memória para os distritos");
        exit(EXIT_FAILURE);
    }

    // Ler cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Realocar memória para armazenar mais um distrito
        *distritos = realloc(*distritos, (num_distritos + 1) * sizeof(Distrito));
        if (*distritos == NULL) {
            perror("Erro ao realocar memória para os distritos");
            exit(EXIT_FAILURE);
        }

        // Separar os dados do distrito
        char *token = strtok(linha, "\t");
        strcpy((*distritos)[num_distritos].codigo, token);

        token = strtok(NULL, "\n");
        strcpy((*distritos)[num_distritos].nome, token);

        num_distritos++;
    }

    fclose(arquivo);
    return num_distritos;
}

int lerConselhos(const char* nome_arquivo, Conselho **conselhos) {
    FILE *arquivo;
    char linha[100]; // Tamanho máximo da linha do arquivo
    int num_conselhos = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Alocar memória inicial para os conselhos
    *conselhos = malloc(sizeof(Conselho));
    if (*conselhos == NULL) {
        perror("Erro ao alocar memória para os conselhos");
        exit(EXIT_FAILURE);
    }

    // Ler cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Realocar memória para armazenar mais um conselho
        *conselhos = realloc(*conselhos, (num_conselhos + 1) * sizeof(Conselho));
        if (*conselhos == NULL) {
            perror("Erro ao realocar memória para os conselhos");
            exit(EXIT_FAILURE);
        }

        // Separar os dados do conselho
        char *token = strtok(linha, "\t");
        strcpy((*conselhos)[num_conselhos].codigo, token);

        token = strtok(NULL, "\n");
        strcpy((*conselhos)[num_conselhos].nome, token);

        num_conselhos++;
    }

    fclose(arquivo);
    return num_conselhos;
}
