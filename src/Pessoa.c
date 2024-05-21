#include "Pessoa.h"

// Função para criar uma pessoa
PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, int dia, int mes, int ano) {
    PESSOA *P = (PESSOA *)malloc(sizeof(PESSOA));
    P->PrimeiroNome = (char *)malloc((strlen(primeiroNome) + 1) * sizeof(char));
    strcpy(P->PrimeiroNome, primeiroNome);
    P->UltimoNome = (char *)malloc((strlen(ultimoNome) + 1) * sizeof(char));
    strcpy(P->UltimoNome, ultimoNome);
    P->NOME = (char *)malloc((strlen(primeiroNome) + strlen(ultimoNome) + 2) * sizeof(char)); // +2 para espaço e '\0'
    strcpy(P->NOME, primeiroNome);
    strcat(P->NOME, " ");
    strcat(P->NOME, ultimoNome);
    P->dataNascimento = (DATANASC *)malloc(sizeof(DATANASC));
    P->dataNascimento->dia = dia;
    P->dataNascimento->mes = mes;
    P->dataNascimento->ano = ano;
    P->numero_requisicoes = 0;
    P->freguesia = NULL; // Inicializando como NULL, pode ser definido depois
    return P;
}

// Função para pedir dados de uma pessoa
PESSOA *PedirDadosPessoa() {
    int dia, mes, ano;
    char primeiroNome[30], ultimoNome[30];
    printf("\nAdicionar Pessoa:\n");
    printf("Primeiro Nome: ");
    scanf("%s", primeiroNome);
    printf("Ultimo Nome: ");
    scanf("%s", ultimoNome);
    printf("Data de nascimento:\n");
    printf("Dia: ");
    scanf("%d", &dia);
    printf("Mês: ");
    scanf("%d", &mes);
    printf("Ano: ");
    scanf("%d", &ano);
    return CriarPessoa(primeiroNome, ultimoNome, dia, mes, ano);
}

// Função para criar uma lista de pessoas
ListaPessoa *criarListaP() {
    ListaPessoa *L = (ListaPessoa *)malloc(sizeof(ListaPessoa));
    if (!L) return NULL;
    L->num_Pessoas = 0;
    L->Inicio = NULL;
    return L;
}

// Função para criar um elemento de pessoa
ElementoP *criarElementoP(PESSOA *P) {
    ElementoP *e = (ElementoP *)malloc(sizeof(ElementoP));
    if (!e) return NULL;
    e->pessoa = P;
    e->proximo = NULL;
    return e;
}

// Função para criar um nó de chave
NO_CHAVE_P *criarNoChave(char chave) {
    NO_CHAVE_P *novoNoChave = (NO_CHAVE_P *)malloc(sizeof(NO_CHAVE_P));
    if (novoNoChave != NULL) {
        novoNoChave->Key = chave;
        novoNoChave->DADOS = criarListaP();
        novoNoChave->Prox = NULL;
    }
    return novoNoChave;
}

// Função para criar uma lista de chaves
Lista_Chaves_P *criarListaChave() {
    Lista_Chaves_P *novaLista = (Lista_Chaves_P *)malloc(sizeof(Lista_Chaves_P));
    if (novaLista != NULL) {
        novaLista->Inicio = NULL;
        novaLista->num_chaves = 0;
    }
    return novaLista;
}

// Função para adicionar uma pessoa à lista de chaves
void *AdicionarPessoa(Lista_Chaves_P *C, ElementoP *E) {
    if (!C || !E) return NULL;
    int a = 0;
    NO_CHAVE_P *N = C->Inicio;
    for (int i = 0; i < C->num_chaves; i++) {
        if (N->Key == E->pessoa->PrimeiroNome[0]) {
            if (N->DADOS->Inicio == NULL) {
                N->DADOS->Inicio = E;
            } else {
                ElementoP *ultimo = N->DADOS->Inicio;
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = E;
            }
            a = 1;
            N->DADOS->num_Pessoas++;
            break;
        }
        N = N->Prox;
    }
    if (!a) {
        char key = E->pessoa->PrimeiroNome[0];
        NO_CHAVE_P *novoNo = criarNoChave(key);
        novoNo->Prox = C->Inicio;
        C->Inicio = novoNo;
        novoNo->DADOS->Inicio = E;
        novoNo->DADOS->num_Pessoas++;
        C->num_chaves++;
    }
    printf("\nPessoa adicionada a lista.\n");
    return NULL;
}

// Função para pesquisar uma pessoa pelo nome
void *PesquisarPesssoaPorNome(Lista_Chaves_P *L, char *nome) {
    if (!L) return NULL;
    NO_CHAVE_P *N = L->Inicio;
    while (N != NULL) {
        ElementoP *E = N->DADOS->Inicio;
        while (E != NULL) {
            if (strcmp(E->pessoa->NOME, nome) == 0) {
                return E->pessoa;
            }
            E = E->proximo;
        }
        N = N->Prox;
    }
    return NULL;
}

// Função para comparar nomes
int compararPrimeiroNome(const void *a, const void *b) {
    PESSOA *pessoaA = *(PESSOA **)a;
    PESSOA *pessoaB = *(PESSOA **)b;
    return strcmp(pessoaA->PrimeiroNome, pessoaB->PrimeiroNome);
}

int compararUltimoNome(const void *a, const void *b) {
    PESSOA *pessoaA = *(PESSOA **)a;
    PESSOA *pessoaB = *(PESSOA **)b;
    return strcmp(pessoaA->UltimoNome, pessoaB->UltimoNome);
}

// Função para organizar a lista de pessoas por nome
void *OrganizarPorNome(Lista_Chaves_P *L, int op) {
    if (!L) return NULL;
    // Coletando todas as pessoas em uma array
    int totalPessoas = 0;
    NO_CHAVE_P *N = L->Inicio;
    while (N != NULL) {
        totalPessoas += N->DADOS->num_Pessoas;
        N = N->Prox;
    }
    PESSOA **pessoasArray = (PESSOA **)malloc(totalPessoas * sizeof(PESSOA *));
    int index = 0;
    N = L->Inicio;
    while (N != NULL) {
        ElementoP *E = N->DADOS->Inicio;
        while (E != NULL) {
            pessoasArray[index++] = E->pessoa;
            E = E->proximo;
        }
        N = N->Prox;
    }
    // Ordenando a array
    if (op == 0) {
        qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararPrimeiroNome);
    } else {
        qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararUltimoNome);
    }
    // Imprimindo as pessoas ordenadas
    printf("Pessoas ordenadas:\n");
    for (int i = 0; i < totalPessoas; i++) {
        MostrarPessoa(pessoasArray[i]);
    }
    free(pessoasArray);
    return NULL;
}

// Função para listar pessoas
void *ListarPessoas(Lista_Chaves_P *L) {
    if (!L) return NULL;
    NO_CHAVE_P *N = L->Inicio;
    while (N != NULL) {
        ElementoP *E = N->DADOS->Inicio;
        while (E != NULL) {
            MostrarPessoa(E->pessoa);
            E = E->proximo;
        }
        N = N->Prox;
    }
    return NULL;
}

// Função para mostrar dados de uma pessoa
void MostrarPessoa(PESSOA *P) {
    if (!P) return;
    printf("\nNome: %s\n", P->NOME);
    printf("ID: %d\n", P->ID);
    printf("Data de Nascimento: %d/%d/%d\n", P->dataNascimento->dia, P->dataNascimento->mes, P->dataNascimento->ano);
    if (P->freguesia != NULL) {
        printf("Freguesia: %s\n", P->freguesia->nome);
    }
    printf("Número de Requisições: %d\n", P->numero_requisicoes);
}

// Função para buscar pessoa por ID
PESSOA *buscarPessoaPorID(Lista_Chaves_P *L, int id) {
    if (!L) return NULL;
    NO_CHAVE_P *N = L->Inicio;
    while (N != NULL) {
        ElementoP *E = N->DADOS->Inicio;
        while (E != NULL) {
            if (E->pessoa->ID == id) {
                return E->pessoa;
            }
            E = E->proximo;
        }
        N = N->Prox;
    }
    return NULL;
}

// Função para verificar ID no arquivo
int verificarIDArquivo(char *idRequisitante) {
    FILE *arquivo = fopen("Ids.txt", "r");
    if (!arquivo) return 0;
    char linha[20];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        if (strcmp(linha, idRequisitante) == 0) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

// Função para ler freguesias de um arquivo
int lerFreguesias(const char* nome_arquivo, Freguesia **freguesias) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) return -1;
    int num_freguesias;
    fscanf(file, "%d", &num_freguesias);
    *freguesias = (Freguesia *)malloc(num_freguesias * sizeof(Freguesia));
    for (int i = 0; i < num_freguesias; i++) {
        fscanf(file, "%s %s", (*freguesias)[i].codigo, (*freguesias)[i].nome);
    }
    fclose(file);
    return num_freguesias;
}

// Função para ler pessoas de um arquivo
/*
void lerArquivoPessoas(const char *nome_arquivo, ListaPessoa *listaPessoa) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) return;
    while (!feof(file)) {
        char primeiroNome[30], ultimoNome[30];
        int dia, mes, ano, ID;
        fscanf(file, "%d %s %s %d %d %d", &ID, primeiroNome, ultimoNome, &dia, &mes, &ano);
        PESSOA *pessoa = CriarPessoa(primeiroNome, ultimoNome, dia, mes, ano);
        pessoa->ID = ID;
        ElementoP *elemento = criarElementoP(pessoa);
        AdicionarPessoa(, elemento);
    }
    fclose(file);
}
 */

// Função para ler distritos de um arquivo
int lerDistritos(const char* nome_arquivo, Distrito **distritos) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) return -1;
    int num_distritos;
    fscanf(file, "%d", &num_distritos);
    *distritos = (Distrito *)malloc(num_distritos * sizeof(Distrito));
    for (int i = 0; i < num_distritos; i++) {
        fscanf(file, "%s %s", (*distritos)[i].codigo, (*distritos)[i].nome);
    }
    fclose(file);
    return num_distritos;
}

// Função para ler conselhos de um arquivo
int lerConselhos(const char* nome_arquivo, Conselho **conselhos) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) return -1;
    int num_conselhos;
    fscanf(file, "%d", &num_conselhos);
    *conselhos = (Conselho *)malloc(num_conselhos * sizeof(Conselho));
    for (int i = 0; i < num_conselhos; i++) {
        fscanf(file, "%s %s", (*conselhos)[i].codigo, (*conselhos)[i].nome);
    }
    fclose(file);
    return num_conselhos;
}
