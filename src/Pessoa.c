#include <time.h>
#include "Pessoa.h"
#include "Uteis.h"

// Função para criar uma pessoa
PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, int dia, int mes, int ano, char *NIF, Freguesia *freguesia){
    PESSOA *P = (PESSOA *)malloc(sizeof(PESSOA));
    if (P == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA PESSOA\n");
        return NULL;
    }

    P->PrimeiroNome = (char *)malloc((strlen(primeiroNome) + 1) * sizeof(char));
    if (P->PrimeiroNome == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA PrimeiroNome\n");
        free(P);
        return NULL;
    }
    strcpy(P->PrimeiroNome, primeiroNome);

    P->UltimoNome = (char *)malloc((strlen(ultimoNome) + 1) * sizeof(char));
    if (P->UltimoNome == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA UltimoNome\n");
        free(P->PrimeiroNome);
        free(P);
        return NULL;
    }
    strcpy(P->UltimoNome, ultimoNome);

    P->NOME = (char *)malloc((strlen(primeiroNome) + strlen(ultimoNome) + 2) * sizeof(char)); // +2 para espaço e '\0'
    if (P->NOME == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA NOME\n");
        free(P->PrimeiroNome);
        free(P->UltimoNome);
        free(P);
        return NULL;
    }
    strcpy(P->NOME, primeiroNome);
    strcat(P->NOME, " ");
    strcat(P->NOME, ultimoNome);

    P->NIF = (char *)malloc((strlen(NIF) + 1) * sizeof(char));
    if (P->NIF == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA NIF\n");
        free(P->PrimeiroNome);
        free(P->UltimoNome);
        free(P->NOME);
        free(P);
        return NULL;
    }
    strcpy(P->NIF, NIF);

    P->freguesia = freguesia;

    P->dataNascimento = (data *)malloc(sizeof(data));
    if (P->dataNascimento == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA dataNascimento\n");
        free(P->PrimeiroNome);
        free(P->UltimoNome);
        free(P->NOME);
        free(P->NIF);
        free(P);
        return NULL;
    }
    P->dataNascimento->dia = dia;
    P->dataNascimento->mes = mes;
    P->dataNascimento->ano = ano;

    P->numero_requisicoes = 0;

    return P;
}


// Função para pedir dados de uma pessoa
PESSOA *PedirDadosPessoa(Lista_Chaves_P *P, Lista_D *D, Lista_C *C, Lista_F *F) {
    int dia, mes, ano, id_dist, id_conc;
    char primeiroNome[30], ultimoNome[30], NIF[10], id_freg[7];
    Freguesia *freguesia = NULL;
    printf("\nAdicionar Pessoa:\n");
    do{
        printf("\nNIF: ");
        scanf("%s", NIF);
        limparBuffer();
        if (strlen(NIF) != 9) {
            printf("\nErro: O NIF tem de ter 9 digitos.(%d)\n", strlen(NIF));
        } else if (PesquisarPessoaPorNIF(P,NIF) != NULL) {
            printf("\nErro: O NIF inserido ja existe.\n");
        }
    }while(strlen(NIF) != 9 || PesquisarPessoaPorNIF(P,NIF) != NULL);

    do {
        printf("Primeiro Nome: ");
        lerString(primeiroNome, sizeof(primeiroNome));
        if (!strlen(primeiroNome)) {
            printf("\nErro: O primeiro nome e muito pequeno\n");
        }
    }while(!strlen(primeiroNome));

    do {
        printf("Ultimo Nome: ");
        lerString(ultimoNome, sizeof(ultimoNome));
        if (!strlen(ultimoNome)) {
            printf("\nErro: O ultimo nome e muito pequeno\n");
        }
    }while(!strlen(primeiroNome));

    printf("Data de nascimento:\n");

    do {
        printf("  Ano: ");
        scanf("%d", &ano);
        limparBuffer();
        if (ano < 1900 || ano > 2024) {
            printf("\nErro: Ano invalido.\n");
        }
    }while(ano < 1900 || ano > 2024);

    do{
        printf("  Mês: ");
        scanf("%d", &mes);
        limparBuffer();
        if (mes < 1 || mes > 12) {
            printf("\nErro: Mês invalido.\n");
        }
    }while(mes < 1 || mes > 12);

    do {
        printf("  Dia: ");
        scanf("%d", &dia);
        limparBuffer();
        if(mes == 2){
            if(dia < 1 || dia > 29){
                printf("\nErro: Dia invalido.\n");
            }
        }else{
            if (dia < 1 || dia > 31) {
                printf("\nErro: Dia invalido.\n");
            }
        }
    }while (mes == 2 && (dia < 1 || dia > 29) || (mes != 2 && (dia < 1 || dia > 31)));
    ListarDistritos(D);
    do{
        printf("\nEscolha o seu Distrito: ");
        scanf("%d", &id_dist);
        limparBuffer();
        if(ProcurarDistritoPorID(D, id_dist) == NULL){
            printf("\nErro: Distrito nao encontrado.\n");
        }
    }while(ProcurarDistritoPorID(D, id_dist) == NULL);
    MostraConcelhosDistrito(id_dist, D);
    do{
        printf("\nEscolha o seu Concelho: ");
        scanf("%d", &id_conc);
        limparBuffer();
        if(ProcurarConcelhoPorID(C, id_conc, id_dist) == NULL){
            printf("\nErro: Concelho nao encontrado.\n");
        }
    }while(ProcurarConcelhoPorID(C, id_conc, id_dist) == NULL);
    MostraFreguesiasConcelho(id_conc, C, id_dist);
    do{
        do {
            printf("\nEscolha a sua Freguesia: ");
            lerString(id_freg, sizeof(id_freg));
            if (strlen(id_freg) != 2) {
                printf("\nErro: Introduza um ID valido.\n");
            }
        }while(strlen(id_freg) != 2);
        if(ProcurarFreguesiaPorID(F,id_freg,id_conc,id_dist) == NULL){
            printf("\nErro: Freguesia nao encontrada.\n");
        }else{
            freguesia = ProcurarFreguesiaPorID(F,id_freg,id_conc,id_dist);
        }
    }while(freguesia == NULL);
    return CriarPessoa(primeiroNome, ultimoNome, dia, mes, ano, NIF, freguesia);
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

void *PesquisarPessoaPorNIF(Lista_Chaves_P *L, char *nif) {
    if (!L || !nif) return NULL;
    NO_CHAVE_P *N = L->Inicio;
    while (N != NULL) {
        ElementoP *E = N->DADOS->Inicio;
        while (E != NULL) {
            if (strcmp(E->pessoa->NIF, nif) == 0) {
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
void ListaOrganizada(Lista_Chaves_P *L, int op) {
    if (!L) return;

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
        case 1:
            qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararPrimeiroNome);
            break;
        case 2:
            qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararUltimoNome);
            break;
        case 3:
            qsort(pessoasArray, totalPessoas, sizeof(PESSOA *), compararIdFreguesia);
            break;
        default:
            printf("Opcao de ordenacao invalida.\n");
            free(pessoasArray);
            return;
    }

    // mostrar as pessoas ordenadas
    printf("Pessoas ordenadas:\n");
    for (int i = 0; i < totalPessoas; i++) {
        MostrarPessoa(pessoasArray[i]);
    }
    free(pessoasArray);
    return;
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
    printf("NIF: %s\n", P->NIF);
    printf("Data de Nascimento: %d/%d/%d\n", P->dataNascimento->dia, P->dataNascimento->mes, P->dataNascimento->ano);
    printf("Freguesia: %s (ID: %s)\n", P->freguesia->nome, P->freguesia->ID_Todo);
    printf("Numero de Requisicoes: %d\n", P->numero_requisicoes);
}


//  Determinar a idade máxima de todos os requisitantes;
int CalcularIdadeMaxima(Lista_Chaves_P *listaChavesPessoa) {
    if (listaChavesPessoa == NULL || listaChavesPessoa->Inicio == NULL) {
        return 0; // Lista vazia
    }

    time_t t = time(NULL);
    struct tm today;
    localtime_s(&today, &t);

    int idadeMaxima = 0;

    NO_CHAVE_P *noChaveAtual = listaChavesPessoa->Inicio;
    while (noChaveAtual != NULL) {
        ListaPessoa *listaPessoaAtual = noChaveAtual->DADOS;
        if (listaPessoaAtual == NULL || listaPessoaAtual->Inicio == NULL) {
            noChaveAtual = noChaveAtual->Prox;
            continue; // Lista de pessoas está vazia, passa para a próxima chave
        }

        ElementoP *atual = listaPessoaAtual->Inicio;
        while (atual != NULL) {
            if (atual->pessoa == NULL || atual->pessoa->dataNascimento == NULL) {
                printf("Erro: Pessoa ou data de nascimento é NULL.\n");
                atual = atual->proximo;
                continue;
            }

            PESSOA *pessoaAtual = atual->pessoa;
            data *dataNascimento = pessoaAtual->dataNascimento;
            int anos = today.tm_year + 1900 - dataNascimento->ano;

            if (today.tm_mon + 1 < dataNascimento->mes ||
                (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
                anos--;
            }

            if (anos > idadeMaxima) {
                idadeMaxima = anos;
            }

            atual = atual->proximo;
        }

        noChaveAtual = noChaveAtual->Prox;
    }

    return idadeMaxima;
}

//Idade Média
float CalcularIdadeMedia(Lista_Chaves_P *listaChavesPessoa) {
    if (listaChavesPessoa == NULL || listaChavesPessoa->Inicio == NULL) {
        return 0.0; // Lista vazia
    }

    time_t t = time(NULL);
    struct tm today;
    localtime_s(&today, &t);

    float totalIdade = 0.0;
    int countPessoas = 0;

    NO_CHAVE_P *noChaveAtual = listaChavesPessoa->Inicio;
    while (noChaveAtual != NULL) {
        ListaPessoa *listaPessoaAtual = noChaveAtual->DADOS;
        if (listaPessoaAtual == NULL || listaPessoaAtual->Inicio == NULL) {
            noChaveAtual = noChaveAtual->Prox;
            continue; // Lista de pessoas está vazia, passa para a próxima chave
        }

        ElementoP *atual = listaPessoaAtual->Inicio;
        while (atual != NULL) {
            if (atual->pessoa == NULL || atual->pessoa->dataNascimento == NULL) {
                printf("Erro: Pessoa ou data de nascimento é NULL.\n");
                atual = atual->proximo;
                continue;
            }

            PESSOA *pessoaAtual = atual->pessoa;
            data *dataNascimento = pessoaAtual->dataNascimento;
            int anos = today.tm_year + 1900 - dataNascimento->ano;

            if (today.tm_mon + 1 < dataNascimento->mes ||
                (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
                anos--;
            }

            totalIdade += anos;
            countPessoas++;

            atual = atual->proximo;
        }

        noChaveAtual = noChaveAtual->Prox;
    }

    if (countPessoas == 0) {
        return 0.0; // evitar divisão por zero
    }

    return totalIdade / countPessoas;
}

// idade com mais requisitantes
int IdadeComMaisRequisitantes(Lista_Chaves_P *listaChavesPessoa) {
    if (listaChavesPessoa == NULL || listaChavesPessoa->Inicio == NULL) {
        return -1; // Lista vazia
    }

    // supostamente nng tem mais do que 120 anos
    int maxIdade = 120;
    int contadorIdades[121] = {0}; // Array para contar quantiade de pessoas por idade

    time_t t = time(NULL);
    struct tm today;
    localtime_s(&today, &t);

    NO_CHAVE_P *noChaveAtual = listaChavesPessoa->Inicio;
    while (noChaveAtual != NULL) {
        ListaPessoa *listaPessoaAtual = noChaveAtual->DADOS;
        if (listaPessoaAtual == NULL || listaPessoaAtual->Inicio == NULL) {
            noChaveAtual = noChaveAtual->Prox;
            continue; // Lista de pessoas está vazia, passa para a próxima chave
        }

        ElementoP *atual = listaPessoaAtual->Inicio;
        while (atual != NULL) {
            if (atual->pessoa == NULL || atual->pessoa->dataNascimento == NULL) {
                printf("Erro: Pessoa ou data de nascimento é NULL.\n");
                atual = atual->proximo;
                continue;
            }

            PESSOA *pessoaAtual = atual->pessoa;
            data *dataNascimento = pessoaAtual->dataNascimento;
            int anos = today.tm_year + 1900 - dataNascimento->ano;

            if (today.tm_mon + 1 < dataNascimento->mes ||
                (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
                anos--;
            }

            if (anos >= 0 && anos <= maxIdade) {
                contadorIdades[anos]++;
            }

            atual = atual->proximo;
        }

        noChaveAtual = noChaveAtual->Prox;
    }

    int idadeMaisRequisitada = -1;
    int maxRequisicoes = 0;
    for (int i = 0; i <= maxIdade; i++) {
        if (contadorIdades[i] > maxRequisicoes) {
            maxRequisicoes = contadorIdades[i];
            idadeMaisRequisitada = i;
        }
    }

    return idadeMaisRequisitada;
}

// contar pessoas com idade maior que x
int ContarPessoasComIdadeSuperiorA(Lista_Chaves_P *listaChavesPessoa, int idadeLimite) {
    if (listaChavesPessoa == NULL || listaChavesPessoa->Inicio == NULL) {
        return 0; // Lista vazia
    }

    int contador = 0;

    time_t t = time(NULL);
    struct tm today;
    localtime_s(&today, &t);

    NO_CHAVE_P *noChaveAtual = listaChavesPessoa->Inicio;
    while (noChaveAtual != NULL) {
        ListaPessoa *listaPessoaAtual = noChaveAtual->DADOS;
        if (listaPessoaAtual == NULL || listaPessoaAtual->Inicio == NULL) {
            noChaveAtual = noChaveAtual->Prox;
            continue; // Lista de pessoas está vazia, passa para a próxima chave
        }

        ElementoP *atual = listaPessoaAtual->Inicio;
        while (atual != NULL) {
            if (atual->pessoa == NULL || atual->pessoa->dataNascimento == NULL) {
                printf("Erro: Pessoa ou data de nascimento é NULL.\n");
                atual = atual->proximo;
                continue;
            }

            PESSOA *pessoaAtual = atual->pessoa;
            data *dataNascimento = pessoaAtual->dataNascimento;
            int anos = today.tm_year + 1900 - dataNascimento->ano;

            if (today.tm_mon + 1 < dataNascimento->mes ||
                (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
                anos--;
            }

            if (anos > idadeLimite) {
                contador++;
            }

            atual = atual->proximo;
        }

        noChaveAtual = noChaveAtual->Prox;
    }

    return contador;
}


// listar pessoas sem requisiçoes
void ListarPessoasSemRequisicoes(Lista_Chaves_P *listaChavesPessoa) {
    NO_CHAVE_P *chaveAtual = listaChavesPessoa->Inicio;
    int encontrou = 0;

    while (chaveAtual != NULL) {
        ElementoP *pessoaAtual = chaveAtual->DADOS->Inicio;

        while (pessoaAtual != NULL) {
            if (pessoaAtual->pessoa->numero_requisicoes == 0) {
                encontrou = 1;
                printf("Nome: %s %s\n", pessoaAtual->pessoa->PrimeiroNome, pessoaAtual->pessoa->UltimoNome);
                printf("NIF: %s\n", pessoaAtual->pessoa->NIF);
                printf("Data de Nascimento: %02d/%02d/%04d\n", pessoaAtual->pessoa->dataNascimento->dia,
                       pessoaAtual->pessoa->dataNascimento->mes,
                       pessoaAtual->pessoa->dataNascimento->ano);
                printf("\n");
            }
            pessoaAtual = pessoaAtual->proximo;
        }
        chaveAtual = chaveAtual->Prox;
    }

    if (!encontrou) {
        printf("Nenhuma pessoa sem requisições encontrada.\n");
    }
}


// Listar pessoa com requisição
void ListarPessoasComRequisicao(Lista_Chaves_P *listaChavesPessoa) {
    NO_CHAVE_P *chaveAtual = listaChavesPessoa->Inicio;
    int encontrou = 0;

    while (chaveAtual != NULL) {
        ElementoP *pessoaAtual = chaveAtual->DADOS->Inicio;

        while (pessoaAtual != NULL) {
            if (pessoaAtual->pessoa->numero_requisicoes > 0) {
                encontrou = 1;
                printf("Nome: %s %s\n", pessoaAtual->pessoa->PrimeiroNome, pessoaAtual->pessoa->UltimoNome);
                printf("ID: %d\n", pessoaAtual->pessoa->NIF);
                printf("Data de Nascimento: %02d/%02d/%04d\n", pessoaAtual->pessoa->dataNascimento->dia,
                       pessoaAtual->pessoa->dataNascimento->mes,
                       pessoaAtual->pessoa->dataNascimento->ano);
                printf("Número de Requisições: %d\n", pessoaAtual->pessoa->numero_requisicoes);
                printf("\n");
            }
            pessoaAtual = pessoaAtual->proximo;
        }
        chaveAtual = chaveAtual->Prox;
    }

    if (!encontrou) {
        printf("Nenhuma pessoa com requisições encontrada.\n");
    }
}

// Sobrenome mais usado nas pessoas com requisiçoes
char* SobrenomeMaisUsado(Lista_Chaves_P *listaChavesPessoa) {
    // Inicializar array para armazenar os sobrenomes e contadores
#define MAX_SOBRENOMES 100
    char sobrenomes[MAX_SOBRENOMES][50];
    int contadores[MAX_SOBRENOMES] = {0};
    int indice = 0;

    // Percorrer todas as pessoas com requisições
    NO_CHAVE_P *chaveAtual = listaChavesPessoa->Inicio;
    while (chaveAtual != NULL) {
        ElementoP *pessoaAtual = chaveAtual->DADOS->Inicio;
        while (pessoaAtual != NULL) {
            if (pessoaAtual->pessoa->numero_requisicoes > 0) {
                // ver o sobrenome da pessoa
                char* ultimoNome = pessoaAtual->pessoa->UltimoNome;

                // ver se o sobrenome já está na lista de sobrenomes
                int i;
                int encontrado = 0;
                for (i = 0; i < indice; i++) {
                    if (strcmp(sobrenomes[i], ultimoNome) == 0) {
                        encontrado = 1;
                        break;
                    }
                }

                // Se o sobrenome não estiver na lista, adicioná-lo
                if (!encontrado) {
                    strcpy(sobrenomes[indice], ultimoNome);
                    indice++;
                }

                // Incrementar o contador para esse sobrenome
                contadores[i]++;
            }
            pessoaAtual = pessoaAtual->proximo;
        }
        chaveAtual = chaveAtual->Prox;
    }

    // Encontrar o sobrenome com o maior contador
    int maiorContador = 0;
    char* sobrenomeMaisComum = NULL;
    for (int i = 0; i < indice; i++) {
        if (contadores[i] > maiorContador) {
            maiorContador = contadores[i];
            sobrenomeMaisComum = sobrenomes[i];
        }
    }

    // Retornar o sobrenome mais comum
    return sobrenomeMaisComum;
}


// Função para buscar pessoa por ID
/*PESSOA *buscarPessoaPorID(Lista_Chaves_P *L, int id) {
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
*/

// Função para verificar ID no arquivo
/*int verificarIDArquivo(char *idRequisitante) {
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
}*/


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
        char ID_Todo[7];
        char nome[50];
        if (sscanf(linha, "%2d%2d%2s %[^\n]", &id_dist, &id_conc, ID, nome) != 4) {
            printf("Erro ao ler os dados da linha.\n");
            fclose(arquivo);
            LibertarFreguesias(lista); // Supondo que isso libera a memória da lista
            return NULL;
        }

        sprintf(ID_Todo, "%02d%02d%2s", id_dist, id_conc, ID);

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
        sprintf(nova_freg->ID_Todo, "%s", ID_Todo); // Você pode copiar diretamente o ID
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
//colocar para ler as freguesias nos concelhos correspondentes
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



//colocar para ler os concelhos nos respetivos distritos
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

        //lerconcelho(id_distr);

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

/*void ListarDistritosPorID(Lista_D *listaDistritos, int idDistrito) {
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
}*/

void ListarDistritos(Lista_D *listaDistritos) {
    if (!listaDistritos || listaDistritos->num_Distritos == 0) {
        printf("Não há distritos.\n");
        return;
    }

    ElementoD *atual = listaDistritos->Inicio;
    printf("\nDistritos: \n");
    while (atual != NULL) {
        Distrito *distrito = atual->Info;
        if (distrito) {
            printf("- %s (ID: %d)\n", distrito->nome, distrito->ID_DIST);
        }
        atual = atual->Prox;
    }
}

void ListarFreguesias(Lista_F *listaFreguesias) {
    if (!listaFreguesias || listaFreguesias->num_Freguesias == 0) {
        printf("Não há freguesias.\n");
        return;
    }

    ElementoF *atual = listaFreguesias->Inicio;
    printf("\nFreguesias: \n");
    while (atual != NULL) {
        Freguesia *distrito = atual->freguesia;
        if (distrito) {
            printf("- %s (ID: %d, %d, %s)\n", distrito->nome, distrito->ID_DIST, distrito->ID_CONC, distrito->ID);
        }
        atual = atual->prox;
    }
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

void associa_concelhos_a_distritos(Lista_D *lista_distritos, Lista_C *lista_concelhos) {
    if (lista_distritos == NULL || lista_concelhos == NULL) {
        return;
    }

    ElementoD *current_distrito_elem = lista_distritos->Inicio;

    // Percorrer todos os distritos
    while (current_distrito_elem != NULL) {
        Distrito *current_distrito = current_distrito_elem->Info;

        // Inicializar a lista de concelhos do distrito, se ainda não estiver inicializada
        if (current_distrito->Conc == NULL) {
            current_distrito->Conc = (Lista_C *)malloc(sizeof(Lista_C));
            current_distrito->Conc->num_Concelhos = 0;
            current_distrito->Conc->Inicio = NULL;
        }

        ElementoC *current_concelho_elem = lista_concelhos->Inicio;

        // Percorrer todos os concelhos
        while (current_concelho_elem != NULL) {
            Concelho *current_concelho = current_concelho_elem->concelho;

            // Comparar IDs
            if (current_concelho->ID_DIST == current_distrito->ID_DIST) {
                // Criar um novo elemento para a lista de concelhos do distrito
                ElementoC *novo_elem_concelho = (ElementoC *)malloc(sizeof(ElementoC));
                novo_elem_concelho->concelho = current_concelho;
                novo_elem_concelho->prox = current_distrito->Conc->Inicio;

                // Adicionar o novo elemento no início da lista de concelhos do distrito
                current_distrito->Conc->Inicio = novo_elem_concelho;
                current_distrito->Conc->num_Concelhos++;
            }

            // Avançar para o próximo concelho na lista
            current_concelho_elem = current_concelho_elem->prox;
        }

        // Avançar para o próximo distrito na lista
        current_distrito_elem = current_distrito_elem->Prox;
    }
}

// Funções auxiliares para criação e adição de elementos nas listas (não requeridas mas úteis para testes)

ElementoD* cria_elemento_distrito(Distrito *distrito) {
    ElementoD *novo_elem = (ElementoD *)malloc(sizeof(ElementoD));
    novo_elem->Info = distrito;
    novo_elem->Prox = NULL;
    return novo_elem;
}

ElementoC* cria_elemento_concelho(Concelho *concelho) {
    ElementoC *novo_elem = (ElementoC *)malloc(sizeof(ElementoC));
    novo_elem->concelho = concelho;
    novo_elem->prox = NULL;
    return novo_elem;
}

ElementoF* cria_elemento_freguesia(Freguesia *freguesia) {
    ElementoF *novo_elem = (ElementoF *)malloc(sizeof(ElementoF));
    novo_elem->freguesia = freguesia;
    novo_elem->prox = NULL;
    return novo_elem;
}

void MostraConcelhosDistrito(int id_distrito, Lista_D *listaDistrito) {
    ElementoD *atualDistrito = listaDistrito->Inicio;
    Distrito *distrito = NULL;
    while (atualDistrito != NULL) {
        if (id_distrito == atualDistrito->Info->ID_DIST) {
            distrito = atualDistrito->Info;
            break;
        }
        atualDistrito = atualDistrito->Prox;
    }
    if (distrito == NULL || distrito->Conc == NULL) {
        printf("Distrito ou lista de concelhos não está inicializada.\n");
        return;
    }

    printf("\nConcelhos do Distrito %s:\n", distrito->nome);
    ElementoC *current_concelho_elem = distrito->Conc->Inicio;

    // Percorrer todos os concelhos do distrito
    while (current_concelho_elem != NULL) {
        printf("- %s (ID: %d)\n", current_concelho_elem->concelho->nome, current_concelho_elem->concelho->ID_CONC);
        current_concelho_elem = current_concelho_elem->prox;
    }
}
Distrito *ProcurarDistritoPorID(Lista_D *listaDistritos, int id) {
    if (!listaDistritos) {
        return NULL;
    }
    ElementoD *atual = listaDistritos->Inicio;
    while (atual != NULL) {
        Distrito *distrito = atual->Info;
        if (distrito && distrito->ID_DIST == id) {
            return distrito;
        }
        atual = atual->Prox;
    }
    return NULL;
}

Concelho *ProcurarConcelhoPorID(Lista_C *listaConcelhos, int id_conc, int id_dist) {
    if (!listaConcelhos) return NULL;

    ElementoC *atual = listaConcelhos->Inicio;
    while (atual != NULL) {
        Concelho *concelho = atual->concelho;
        if (concelho && concelho->ID_DIST == id_dist && concelho->ID_CONC == id_conc ) {
            return concelho;
        }
        atual = atual->prox;
    }

    return NULL;
}

Freguesia *ProcurarFreguesiaPorID(Lista_F *listafreguesias, char *id_freg, int id_conc, int id_dist){
    if(!listafreguesias) return NULL;

    ElementoF *atual = listafreguesias->Inicio;
    while(atual != NULL){
        Freguesia *freguesia = atual->freguesia;
        if(freguesia && strcmp(freguesia->ID,id_freg) == 0 && freguesia->ID_DIST == id_dist && freguesia->ID_CONC == id_conc){
            return freguesia;
        }
        atual = atual->prox;
    }
    return NULL;
}

void associa_freguesias_a_concelhos(Lista_C *lista_concelhos, Lista_F *lista_freguesias) {
    if (lista_concelhos == NULL || lista_freguesias == NULL) {
        return;
    }

    ElementoC *ElementoConcelho = lista_concelhos->Inicio;

    // Percorrer todos os concelhos
    while (ElementoConcelho != NULL) {
        Concelho *atualConcelho = ElementoConcelho->concelho;

        // Inicializar a lista de freguesias do concelho, se ainda não estiver inicializada
        if (atualConcelho->freguesias == NULL) {
            atualConcelho->freguesias = (Lista_F *)malloc(sizeof(Lista_F));
            atualConcelho->freguesias->num_Freguesias = 0;
            atualConcelho->freguesias->Inicio = NULL;
        }

        ElementoF *ElementoFreguesias = lista_freguesias->Inicio;

        // Percorrer todas as freguesias
        while (ElementoFreguesias != NULL) {
            Freguesia *atualFreguesia = ElementoFreguesias->freguesia;

            // Comparar IDs
            if (atualFreguesia->ID_DIST == atualConcelho->ID_DIST && atualFreguesia->ID_CONC == atualConcelho->ID_CONC) {
                // Criar um novo elemento para a lista de freguesias do concelho
                ElementoF *novo_elem_freguesia = (ElementoF *)malloc(sizeof(ElementoF));
                novo_elem_freguesia->freguesia = atualFreguesia;
                novo_elem_freguesia->prox = atualConcelho->freguesias->Inicio;

                // Adicionar o novo elemento no início da lista de freguesias do concelho
                atualConcelho->freguesias->Inicio = novo_elem_freguesia;
                atualConcelho->freguesias->num_Freguesias++;
            }

            // Avançar para a próxima freguesia na lista
            ElementoFreguesias = ElementoFreguesias->prox;
        }

        // Avançar para o próximo concelho na lista
        ElementoConcelho = ElementoConcelho->prox;
    }
}

void MostraFreguesiasConcelho(int id_concelho, Lista_C *listaConcelhos, int id_distrito) {
    ElementoC *atualConcelho = listaConcelhos->Inicio;
    Concelho *concelho = NULL;

    // Procurar o concelho com o ID correspondente
    while (atualConcelho != NULL) {
        if (id_concelho == atualConcelho->concelho->ID_CONC && id_distrito == atualConcelho->concelho->ID_DIST) {
            concelho = atualConcelho->concelho;
            break;
        }
        atualConcelho = atualConcelho->prox;
    }

    if (concelho == NULL || concelho->freguesias == NULL) {
        printf("Concelho ou lista de freguesias não está inicializada.\n");
        return;
    }

    printf("\nFreguesias do Concelho %s:\n", concelho->nome);
    ElementoF *current_freguesia_elem = concelho->freguesias->Inicio;

    // Percorrer todas as freguesias do concelho
    while (current_freguesia_elem != NULL) {
        printf("- %s (ID: %s)\n", current_freguesia_elem->freguesia->nome, current_freguesia_elem->freguesia->ID);
        current_freguesia_elem = current_freguesia_elem->prox;
    }
}
int ContarPessoasDeUmLocal(Lista_Chaves_P *listaPessoas, int id_dist, int id_conc, char *nome, char *apelido) {
    if(listaPessoas->num_chaves == 0 || id_dist < 0 || (nome == NULL && apelido == NULL)){
        return 0;
    }
    int count = 0;
    NO_CHAVE_P *atual = listaPessoas->Inicio;
    while (atual != NULL) {
        ElementoP *ElementoPessoa = atual->DADOS->Inicio;
        while (ElementoPessoa != NULL) {
            PESSOA *pessoa = ElementoPessoa->pessoa;
            if(id_conc == 0){
                if(apelido == ""){
                    if(pessoa->freguesia->ID_DIST == id_dist && strcmp(pessoa->PrimeiroNome, nome) == 0){
                        count++;
                    }
                }else if(nome == ""){
                    if(pessoa->freguesia->ID_DIST == id_dist && strcmp(pessoa->UltimoNome, apelido) == 0){
                        count++;
                    }
                }

            }else{
                if(apelido == ""){
                    if(pessoa->freguesia->ID_DIST == id_dist && pessoa->freguesia->ID_CONC == id_conc && strcmp(pessoa->PrimeiroNome, nome) == 0){
                        count++;
                    }
                }else if(nome == ""){
                    if(pessoa->freguesia->ID_DIST == id_dist && pessoa->freguesia->ID_CONC == id_conc && strcmp(pessoa->UltimoNome, apelido) == 0){
                        count++;
                    }
                }
            }
            ElementoPessoa = ElementoPessoa->proximo;
        }
        atual = atual->Prox;
    }
    return count;
}