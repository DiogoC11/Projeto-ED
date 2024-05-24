#include <time.h>
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

// Função para comparar por id_freguesia
int compararIdFreguesia(const void* a, const void* b) {
    PESSOA* p1 = *(PESSOA**)a;
    PESSOA* p2 = *(PESSOA**)b;
    return strcmp(p1->freguesia->ID, p2->freguesia->ID);
}

// Função para organizar a lista de pessoas por nome / freguesia
ListaPessoa *ListaOrganizada(Lista_Chaves_P *L, int op) {
    if (!L) return NULL;

    // coletar todas as pessoas
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

    // ordenar por opçao
    switch (op) {
        case 0:
            qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararPrimeiroNome);
            break;
        case 1:
            qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararUltimoNome);
            break;
        case 2:
            qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararIdFreguesia);
            break;
        default:
            printf("Opcao de ordenacao invalida.\n");
            free(pessoasArray);
            return NULL;
    }

    // mostrar as pessoas ordenadas
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


//  Determinar a idade máxima de todos os requisitantes;
int CalcularIdadeMaxima(PESSOA** listaPessoas, int tamanhoListaPessoas) {
    time_t t = time(NULL); // retorna o tempo atual
    struct tm today = *localtime(&t); // isto converte o tempo atual numa estrutura tm que representa a data e hora do local atual
    int idadeMaxima = 0;

    for (int i = 0; i < tamanhoListaPessoas; i++) {
        DATANASC *dataNascimento = listaPessoas[i]->dataNascimento; // ver data de nasc da pessoa atual
        int anos = today.tm_year + 1900 - dataNascimento->ano; // calcular idade

        // ver se a pessoa ja fez anos nesse ano
        if (today.tm_mon + 1 < dataNascimento->mes || (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
            anos--; // se o mes de nasc for depois do mes atual / o mesmo mes mas o dia de nasc depois entao ainda tem -1 ano
        }
        if (anos > idadeMaxima) {
            idadeMaxima = anos;
        }
    }
    return idadeMaxima;
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



Lista_F* LerTXT() {
    FILE *arquivo;
    char linha[100];
    Lista_F *lista = (Lista_F *)malloc(sizeof(Lista_F));
    if (lista == NULL) {
        printf("Erro ao alocar memória para a lista de freguesias.\n");
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
            LibertarFreguesias(lista); // Supondo que isso libera a memória da lista
            return NULL;
        }



        // Criar uma nova freguesia e alocar memória
        Freguesia *nova_freg = (Freguesia *)malloc(sizeof(Freguesia));
        if (nova_freg == NULL) {
            printf("Erro ao alocar memória para nova_freg.\n");
            fclose(arquivo);
            LibertarFreguesias(lista); // Supondo que isso libera a memória da lista
            return NULL;
        }

        // Preencher os campos da freguesia
        sprintf(nova_freg->ID, "%s", ID); // Você pode copiar diretamente o ID
        nova_freg->ID_CONC = id_conc; // Não precisa usar sprintf para inteiros
        nova_freg->ID_DIST = id_dist; // Não precisa usar sprintf para inteiros
        strcpy(nova_freg->nome, nome); // Copia o nome da freguesia

        // Criar um novo elemento para a lista de freguesias e alocar memória
        ElementoF *novo_elemento = (ElementoF *)malloc(sizeof(ElementoF));
        if (novo_elemento == NULL) {
            printf("Erro ao alocar memória para novo_elemento.\n");
            fclose(arquivo);
            LibertarFreguesias(lista); // Supondo que isso libera a memória da lista
            free(nova_freg);
            return NULL;
        }

        // Preencher o elemento com a nova freguesia
        novo_elemento->freguesia = nova_freg;
        novo_elemento->prox = lista->Inicio;
        lista->Inicio = novo_elemento;
        //printf("Novo elemento: ID: %s,ID_DIST :%d, ID_CONC: %d, Nome: %s\n", novo_elemento->freguesia->ID,novo_elemento->freguesia->ID_DIST,novo_elemento->freguesia->ID_CONC ,novo_elemento->freguesia->nome);
        lista->num_Freguesias++;
    }

    fclose(arquivo);
    return lista;
}


// Função para liberar a memória da lista de freguesias
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



// Função para ler os concelhos a partir de um arquivo
Lista_C* LerTXTConc() {
    FILE *arquivo;
    char linha[100];
    Lista_C *lista = (Lista_C *)malloc(sizeof(Lista_C));
    if (lista == NULL) {
        printf("Erro ao alocar memória para a lista de concelhos.\n");
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

    //printf("Arquivo aberto com sucesso.\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Extrair os IDs DIST e CONC da linha (uso de ASCII)
        int id_dist = (linha[0] - '0') * 10 + (linha[1] - '0');
        int id_conc = (linha[2] - '0') * 10 + (linha[3] - '0');

        // Encontrar o início do nome do concelho (após os 5 primeiros caracteres)
        char nome[50];
        strncpy(nome, linha + 5, sizeof(nome) - 1); // Copia o nome
        nome[sizeof(nome) - 1] = '\0'; // Adiciona o caractere nulo ao final

        // Remover o caractere de nova linha, se houver
        nome[strcspn(nome, "\n")] = 0;

        // Criar um novo concelho e alocar memória
        Concelho *novo_conc = (Concelho *)malloc(sizeof(Concelho));
        if (novo_conc == NULL) {
            printf("Erro ao alocar memória para novo_conc.\n");
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

        // Criar um novo elemento para a lista de concelhos e alocar memória
        ElementoC *novo_elemento = (ElementoC *)malloc(sizeof(ElementoC));
        if (novo_elemento == NULL) {
            printf("Erro ao alocar memória para novo_elemento.\n");
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

        //printf("Novo concelho adicionado: ID_DIST=%d, ID_CONC=%d, Nome=%s\n", id_dist, id_conc, nome);
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


char* ObterNomeDistrito(Lista_D *listaDistritos, int idDistrito) {
    ElementoD *atualDistrito = listaDistritos->Inicio;
    while (atualDistrito != NULL) {
        if (atualDistrito->Info->ID_DIST == idDistrito) {
            // Encontrou o distrito correspondente ao ID especificado
            return atualDistrito->Info->nome;
        }
        atualDistrito = atualDistrito->Prox;
    }
    // Se não encontrar o distrito correspondente ao ID especificado, retorna NULL
    return NULL;
}

void ListarConcelhosPorDistrito(Lista_D *listadistritos,Lista_C *listaConcelhos, int idDistrito) {
    ElementoC *atualConcelho = listaConcelhos->Inicio;
    printf("ID do Distrito: %d\nNome: %s\n", idDistrito, ObterNomeDistrito(listadistritos,idDistrito) );
    while (atualConcelho != NULL) {
        if (atualConcelho->concelho->ID_DIST == idDistrito) {
            // Encontrou o concelho correspondente ao ID do distrito especificado
            printf("ID do Concelho: %d\nNome: %s\n",
                   atualConcelho->concelho->ID_CONC, atualConcelho->concelho->nome);
        }
        atualConcelho = atualConcelho->prox;
    }
}




Lista_D* LerTXTDist() {
    FILE *arquivo;
    char linha[100]; // Aumentei o tamanho da linha para garantir que seja suficiente para ler cada linha
    Lista_D *distritos = malloc(sizeof(Lista_D)); // Aloca memória para a estrutura Lista_D
    if (distritos == NULL) {
        printf("Erro ao alocar memória para a lista de distritos.\n");
        return NULL;
    }

    // Inicializa distritos
    distritos->num_Distritos = 0;
    distritos->Inicio = NULL;

    arquivo = fopen("../data/recursos/distritios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(distritos); // Libera a memória alocada para a lista de distritos
        return NULL;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Extrair o ID do distrito
        int id_dist;
        sscanf(linha, "%d", &id_dist);

        // Encontrar o início do nome do distrito (após o ID e a tabulação)
        char *nome = strchr(linha, '\t');
        if (nome == NULL) {
            printf("Erro ao ler o nome do distrito.\n");
            fclose(arquivo);
            free(distritos); // Libera a memória alocada para a lista de distritos
            return NULL;
        }

        // Avança para o próximo caractere após a tabulação
        nome++;

        // Remover o caractere de nova linha, se houver
        nome[strcspn(nome, "\n")] = '\0';

        // Alocar memória para a nova estrutura Distrito
        Distrito *novo_distrito = malloc(sizeof(Distrito));
        if (novo_distrito == NULL) {
            printf("Erro ao alocar memória para novo distrito.\n");
            fclose(arquivo);
            free(distritos); // Libera a memória alocada para a lista de distritos
            return NULL;
        }

        // Preencher os campos do distrito
        novo_distrito->ID_DIST = id_dist;
        novo_distrito->nome = strdup(nome); // Copia o nome do distrito (aloca e copia)
        if (novo_distrito->nome == NULL) {
            printf("Erro ao alocar memória para o nome do distrito.\n");
            fclose(arquivo);
            free(novo_distrito); // Libera a memória alocada para a estrutura Distrito
            free(distritos); // Libera a memória alocada para a lista de distritos
            return NULL;
        }

        // Criar um novo elemento para a lista de distritos e alocar memória
        ElementoD *novo_elemento = malloc(sizeof(ElementoD));
        if (novo_elemento == NULL) {
            printf("Erro ao alocar memória para novo_elemento.\n");
            fclose(arquivo);
            free(novo_distrito); // Libera a memória alocada para a estrutura Distrito
            free(distritos); // Libera a memória alocada para a lista de distritos
            return NULL;
        }

        // Preencher o elemento com o novo distrito
        novo_elemento->Info = novo_distrito;
        novo_elemento->Prox = distritos->Inicio;
        distritos->Inicio = novo_elemento;
        distritos->num_Distritos++;
       //printf("Distrito: %s , ID: %d\n",novo_distrito->nome,novo_distrito->ID_DIST);

    }

    fclose(arquivo);

    return distritos;
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

void ListarDistritosPorID(Lista_D *listaDistritos, int idDistrito) {
    ElementoD *atualDistrito = listaDistritos->Inicio;
    while (atualDistrito != NULL) {
        if (atualDistrito->Info->ID_DIST == idDistrito) {
            // Encontrou o distrito correspondente ao ID especificado
            printf("Distrito encontrado:\n");
            printf("ID: %d\nNome: %s\n", atualDistrito->Info->ID_DIST, atualDistrito->Info->nome);
            return; // Termina a função após encontrar o distrito
        }
        atualDistrito = atualDistrito->Prox;
    }
    // Se não encontrar o distrito correspondente ao ID especificado
    printf("Distrito com ID %d não encontrado.\n", idDistrito);
}




void LiberarListaPessoas(ListaPessoa *lista) {
    ElementoP *atual = lista->Inicio;
    while (atual != NULL) {
        ElementoP *temp = atual;
        atual = atual->proximo;
        free(temp->pessoa->dataNascimento);
        free(temp->pessoa);
        free(temp);
    }
    free(lista);
}

void LiberarListaChaves_P(Lista_Chaves_P *lista) {
    NO_CHAVE_P *atual = lista->Inicio;
    while (atual != NULL) {
        NO_CHAVE_P *temp = atual;
        atual = atual->Prox;
        LiberarListaPessoas(temp->DADOS);
        free(temp);
    }
    free(lista);
}




void ListarFreguesiasPorConcelho(Lista_C *listaConcelhos, int idConcelho) {
    ElementoC *atualConcelho = listaConcelhos->Inicio;
    while (atualConcelho != NULL) {
        if (atualConcelho->concelho->ID_CONC == idConcelho) {
            // Encontrou o concelho correspondente ao ID especificado
            printf("Freguesias do concelho %s:\n", atualConcelho->concelho->nome);

            // Verifica se há freguesias associadas ao concelho
            if (atualConcelho->concelho->freguesias != NULL && atualConcelho->concelho->freguesias->Inicio != NULL) {
                ElementoF *atualFreguesia = atualConcelho->concelho->freguesias->Inicio;
                while (atualFreguesia != NULL) {
                    printf("- %s\n", atualFreguesia->freguesia->nome);
                    atualFreguesia = atualFreguesia->prox;
                }
            } else {
                printf("Nenhuma freguesia encontrada para este concelho.\n");
            }
            return; // Termina a função após listar as freguesias
        }
        atualConcelho = atualConcelho->prox;
    }
    // Se não encontrar o concelho correspondente ao ID especificado
    printf("Concelho com ID %d não encontrado.\n", idConcelho);
}




