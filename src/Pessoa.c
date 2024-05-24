#include "Pessoa.h"

// Fun��o para criar uma pessoa
PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, int dia, int mes, int ano) {
    PESSOA *P = (PESSOA *)malloc(sizeof(PESSOA));
    P->PrimeiroNome = (char *)malloc((strlen(primeiroNome) + 1) * sizeof(char));
    strcpy(P->PrimeiroNome, primeiroNome);
    P->UltimoNome = (char *)malloc((strlen(ultimoNome) + 1) * sizeof(char));
    strcpy(P->UltimoNome, ultimoNome);
    P->NOME = (char *)malloc((strlen(primeiroNome) + strlen(ultimoNome) + 2) * sizeof(char)); // +2 para espa�o e '\0'
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

// Fun��o para pedir dados de uma pessoa
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
    printf("M�s: ");
    scanf("%d", &mes);
    printf("Ano: ");
    scanf("%d", &ano);
    return CriarPessoa(primeiroNome, ultimoNome, dia, mes, ano);
}

// Fun��o para criar uma lista de pessoas
ListaPessoa *criarListaP() {
    ListaPessoa *L = (ListaPessoa *)malloc(sizeof(ListaPessoa));
    if (!L) return NULL;
    L->num_Pessoas = 0;
    L->Inicio = NULL;
    return L;
}

// Fun��o para criar um elemento de pessoa
ElementoP *criarElementoP(PESSOA *P) {
    ElementoP *e = (ElementoP *)malloc(sizeof(ElementoP));
    if (!e) return NULL;
    e->pessoa = P;
    e->proximo = NULL;
    return e;
}

// Fun��o para criar um n� de chave
NO_CHAVE_P *criarNoChave(char chave) {
    NO_CHAVE_P *novoNoChave = (NO_CHAVE_P *)malloc(sizeof(NO_CHAVE_P));
    if (novoNoChave != NULL) {
        novoNoChave->Key = chave;
        novoNoChave->DADOS = criarListaP();
        novoNoChave->Prox = NULL;
    }
    return novoNoChave;
}

// Fun��o para criar uma lista de chaves
Lista_Chaves_P *criarListaChave() {
    Lista_Chaves_P *novaLista = (Lista_Chaves_P *)malloc(sizeof(Lista_Chaves_P));
    if (novaLista != NULL) {
        novaLista->Inicio = NULL;
        novaLista->num_chaves = 0;
    }
    return novaLista;
}

// Fun��o para adicionar uma pessoa � lista de chaves
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

// Fun��o para pesquisar uma pessoa pelo nome
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

// Fun��o para comparar nomes
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

// Fun��o para organizar a lista de pessoas por nome
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

// Fun��o para listar pessoas
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

// Fun��o para mostrar dados de uma pessoa
void MostrarPessoa(PESSOA *P) {
    if (!P) return;
    printf("\nNome: %s\n", P->NOME);
    printf("ID: %d\n", P->ID);
    printf("Data de Nascimento: %d/%d/%d\n", P->dataNascimento->dia, P->dataNascimento->mes, P->dataNascimento->ano);
    if (P->freguesia != NULL) {
        printf("Freguesia: %s\n", P->freguesia->nome);
    }
    printf("N�mero de Requisi��es: %d\n", P->numero_requisicoes);
}

// Fun��o para buscar pessoa por ID
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

// Fun��o para verificar ID no arquivo
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



Lista_F* LerTXT() {
    FILE *arquivo;
    char linha[100];
    Lista_F *lista = (Lista_F *)malloc(sizeof(Lista_F));
    if (lista == NULL) {
        printf("Erro ao alocar mem�ria para a lista de freguesias.\n");
        return NULL;
    }
    lista->num_Freguesias = 0;
    lista->Inicio = NULL;

    arquivo = fopen("../data/recursos/freguesias.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(lista);
        return NULL;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Extrair ID_DIST, ID_CONC e nome da linha
        int id_dist, id_conc;
        char ID[7]; // Aumente para 3 para permitir o caractere nulo
        char nome[50];
        if (sscanf(linha, "%2d%2d%2s %[^\n]", &id_dist, &id_conc, ID, nome) != 4) {
            printf("Erro ao ler os dados da linha.\n");
            fclose(arquivo);
            LibertarFreguesias(lista); // Supondo que isso libera a mem�ria da lista
            return NULL;
        }



        // Criar uma nova freguesia e alocar mem�ria
        Freguesia *nova_freg = (Freguesia *)malloc(sizeof(Freguesia));
        if (nova_freg == NULL) {
            printf("Erro ao alocar mem�ria para nova_freg.\n");
            fclose(arquivo);
            LibertarFreguesias(lista); // Supondo que isso libera a mem�ria da lista
            return NULL;
        }

        // Preencher os campos da freguesia
        sprintf(nova_freg->ID, "%s", ID); // Voc� pode copiar diretamente o ID
        nova_freg->ID_CONC = id_conc; // N�o precisa usar sprintf para inteiros
        nova_freg->ID_DIST = id_dist; // N�o precisa usar sprintf para inteiros
        strcpy(nova_freg->nome, nome); // Copia o nome da freguesia

        // Criar um novo elemento para a lista de freguesias e alocar mem�ria
        ElementoF *novo_elemento = (ElementoF *)malloc(sizeof(ElementoF));
        if (novo_elemento == NULL) {
            printf("Erro ao alocar mem�ria para novo_elemento.\n");
            fclose(arquivo);
            LibertarFreguesias(lista); // Supondo que isso libera a mem�ria da lista
            free(nova_freg);
            return NULL;
        }

        // Preencher o elemento com a nova freguesia
        novo_elemento->freguesia = nova_freg;
        novo_elemento->prox = lista->Inicio;
        lista->Inicio = novo_elemento;
        printf("Novo elemento: ID: %s, Nome: %s\n", novo_elemento->freguesia->ID, novo_elemento->freguesia->nome);
        lista->num_Freguesias++;
    }

    fclose(arquivo);
    return lista;
}


// Fun��o para liberar a mem�ria da lista de freguesias
void LibertarFreguesias(Lista_F *lista) {
    ElementoF *atual = lista->Inicio;
    while (atual != NULL) {
        ElementoF *temp = atual;
        atual = atual->prox;
        free(temp->freguesia);
        free(temp);
    }
    lista->Inicio = NULL;
    lista->num_Freguesias = 0;
}



// Fun��o para ler os concelhos a partir de um arquivo
Lista_C* LerTXTConc() {
    FILE *arquivo;
    char linha[100];
    Lista_C *lista = (Lista_C *)malloc(sizeof(Lista_C));
    if (lista == NULL) {
        printf("Erro ao alocar mem�ria para a lista de concelhos.\n");
        return NULL;
    }
    lista->num_Concelhos = 0;
    lista->Inicio = NULL;

    arquivo = fopen("../data/recursos/conselhos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(lista);
        return NULL;
    }

    printf("Arquivo aberto com sucesso.\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Extrair os IDs DIST e CONC da linha (uso de ASCII)
        int id_dist = (linha[0] - '0') * 10 + (linha[1] - '0');
        int id_conc = (linha[2] - '0') * 10 + (linha[3] - '0');

        // Encontrar o in�cio do nome do concelho (ap�s os 5 primeiros caracteres)
        char nome[50];
        strncpy(nome, linha + 5, sizeof(nome) - 1); // Copia o nome
        nome[sizeof(nome) - 1] = '\0'; // Adiciona o caractere nulo ao final

        // Remover o caractere de nova linha, se houver
        nome[strcspn(nome, "\n")] = 0;

        // Criar um novo concelho e alocar mem�ria
        Concelho *novo_conc = (Concelho *)malloc(sizeof(Concelho));
        if (novo_conc == NULL) {
            printf("Erro ao alocar mem�ria para novo_conc.\n");
            fclose(arquivo);
            LibertarConcelhos(lista);
            return NULL;
        }

        // Preencher os campos do concelho
        novo_conc->ID_DIST = id_dist;
        novo_conc->ID_CONC = id_conc;
        strncpy(novo_conc->nome, nome, sizeof(novo_conc->nome) - 1);
        novo_conc->nome[sizeof(novo_conc->nome) - 1] = '\0';
        novo_conc->freguesias = NULL; // Inicialmente sem freguesias

        // Criar um novo elemento para a lista de concelhos e alocar mem�ria
        ElementoC *novo_elemento = (ElementoC *)malloc(sizeof(ElementoC));
        if (novo_elemento == NULL) {
            printf("Erro ao alocar mem�ria para novo_elemento.\n");
            fclose(arquivo);
            LibertarConcelhos(lista);
            free(novo_conc);
            return NULL;
        }

        // Preencher o elemento com o novo concelho
        novo_elemento->concelho = novo_conc;
        novo_elemento->prox = lista->Inicio;
        lista->Inicio = novo_elemento;
        lista->num_Concelhos++;

        printf("Novo concelho adicionado: ID_DIST=%d, ID_CONC=%d, Nome=%s\n", id_dist, id_conc, nome);
    }

    fclose(arquivo);
    return lista;
}
void LibertarConcelhos(Lista_C *lista) {
    ElementoC *atual = lista->Inicio;
    while (atual != NULL) {
        ElementoC *temp = atual;
        atual = atual->prox;
        free(temp->concelho);
        free(temp);
    }
    free(lista);
}


void LibertarDistritos(Lista_D *lista) {
    ElementoD *atual = lista->Inicio;
    while (atual != NULL) {
        ElementoD *temp = atual;
        atual = atual->Prox;
        free(temp->Info->nome); // Libera o nome do distrito
        free(temp->Info->Conc); // Libera a lista de concelhos associados ao distrito
        free(temp->Info); // Libera a estrutura do distrito
        free(temp); // Libera o elemento da lista
    }
    free(lista); // Libera a lista de distritos
}


Lista_D* LerTXTDist() {
    FILE *arquivo;
    char linha[109];
    Lista_D *distritos = malloc(sizeof(Lista_D)); // Aloca mem�ria para a estrutura Lista_D
    if (distritos == NULL) {
        printf("Erro ao alocar mem�ria para a lista de distritos.\n");
        return NULL;
    }

    // Inicializa distritos
    distritos->num_Distritos = 0;
    distritos->Inicio = NULL;

    arquivo = fopen("../data/recursos/distritios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(distritos); // Libera a mem�ria alocada para a lista de distritos
        return NULL;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Extrair o ID do distrito
        int id_dist = (linha[0] - '0') * 10 + (linha[1] - '0');

        // Encontrar o in�cio do nome do distrito (ap�s os 3 primeiros caracteres)
        char *nome = strdup(linha + 3); // Copia o nome do distrito (aloca e copia)

        // Remover o caractere de nova linha, se houver
        nome[strcspn(nome, "\n")] = '\0';

        // Verifica a aloca��o de mem�ria para o nome
        if (nome == NULL) {
            printf("Erro ao alocar mem�ria para o nome do distrito.\n");
            fclose(arquivo);
            free(distritos); // Libera a mem�ria alocada para a lista de distritos
            return NULL;
        }

        // Alocar mem�ria para a nova estrutura Distrito
        Distrito *novo_distrito = malloc(sizeof(Distrito));
        if (novo_distrito == NULL) {
            printf("Erro ao alocar mem�ria para novo distrito.\n");
            fclose(arquivo);
            free(nome); // Libera a mem�ria alocada para o nome do distrito
            free(distritos); // Libera a mem�ria alocada para a lista de distritos
            return NULL;
        }

        // Inicializar a lista de concelhos associados ao distrito
        Lista_C *lista_concelhos = malloc(sizeof(Lista_C));
        if (lista_concelhos == NULL) {
            printf("Erro ao alocar mem�ria para lista de concelhos.\n");
            fclose(arquivo);
            free(nome); // Libera a mem�ria alocada para o nome do distrito
            free(novo_distrito); // Libera a mem�ria alocada para a estrutura Distrito
            free(distritos); // Libera a mem�ria alocada para a lista de distritos
            return NULL;
        }
        lista_concelhos->num_Concelhos = 0;
        lista_concelhos->Inicio = NULL;
        novo_distrito->Conc = lista_concelhos;

        // Preencher os campos do distrito
        novo_distrito->ID_DIST = id_dist;
        novo_distrito->nome = nome;
        novo_distrito->NEL = 0; // Inicialmente, nenhum concelho associado

        // Criar um novo elemento para a lista de distritos e alocar mem�ria
        ElementoD *novo_elemento = malloc(sizeof(ElementoD));
        if (novo_elemento == NULL) {
            printf("Erro ao alocar mem�ria para novo_elemento.\n");
            fclose(arquivo);
            free(nome); // Libera a mem�ria alocada para o nome do distrito
            free(novo_distrito); // Libera a mem�ria alocada para a estrutura Distrito
            free(lista_concelhos); // Libera a mem�ria alocada para a lista de concelhos
            free(distritos); // Libera a mem�ria alocada para a lista de distritos
            return NULL;
        }

        // Preencher o elemento com o novo distrito
        novo_elemento->Info = novo_distrito;
        novo_elemento->Prox = distritos->Inicio;
        distritos->Inicio = novo_elemento;
        distritos->num_Distritos++;
    }

    fclose(arquivo);

    return distritos;
}











// Fun��o para ler freguesias de um arquivo
/*int lerFreguesias(const char* nome_arquivo, Freguesia **freguesias) {
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

// Fun��o para ler pessoas de um arquivo

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


// Fun��o para ler distritos de um arquivo
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

// Fun��o para ler Concelhos de um arquivo
int lerConcelhos(const char* nome_arquivo, Concelho **Concelhos) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) return -1;
    int num_Concelhos;
    fscanf(file, "%d", &num_Concelhos);
    *Concelhos = (Concelho *)malloc(num_Concelhos * sizeof(Concelho));
    for (int i = 0; i < num_Concelhos; i++) {
        fscanf(file, "%s %s", (*Concelhos)[i].codigo, (*Concelhos)[i].nome);
    }
    fclose(file);
    return num_Concelhos;
}*/

void LiberarListaChaves_P(Lista_Chaves_P *lista) {
    ElementoP *atual = lista->Inicio;
    while (atual != NULL) {
        ElementoP *temp = atual;
        atual = atual->proximo;
        free(temp->pessoa); // Libera a pessoa apontada por este elemento
        free(temp);         // Libera o pr�prio elemento
    }
    free(lista); // Libera a estrutura de lista
}