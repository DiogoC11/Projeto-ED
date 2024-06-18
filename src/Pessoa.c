#define MAX_SOBRENOMES 100
#include <time.h>
#include <ctype.h>
#include "Pessoa.h"
#include "Uteis.h"

char *trim(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

// Função para criar uma pessoa
PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome,char *Nome, int dia, int mes, int ano,char *id, Freguesia *freguesia){
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

    P->NOME = (char *)malloc((strlen(Nome) + 1) * sizeof(char));
    if (P->UltimoNome == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA UltimoNome\n");
        free(P->PrimeiroNome);
        free(P);
        return NULL;
    }
    strcpy(P->NOME, Nome);

    P->freguesia = freguesia;

    P->dataNascimento = (data *)malloc(sizeof(data));
    if (P->dataNascimento == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA dataNascimento\n");
        free(P->PrimeiroNome);
        free(P->UltimoNome);
        free(P->NOME);
        free(P);
        return NULL;
    }
    P->dataNascimento->dia = dia;
    P->dataNascimento->mes = mes;
    P->dataNascimento->ano = ano;

    P->ID = (char *)malloc((strlen(id) + 1) * sizeof(char));
    if (P->ID == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA ID\n");
        free(P->PrimeiroNome);
        free(P->UltimoNome);
        free(P->NOME);
        free(P->dataNascimento);
        free(P);
        return NULL;
    }
    strcpy(P->ID, id);
    return P;
}

char *GerarIDPessoa(Lista_Chaves_P *L) {
    char *id = (char *)malloc(10 * sizeof(char));
    if (id == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA ID\n");
        return NULL;
    }
    srand(time(NULL));

    for(int i = 0; i < 9; i++) {
        id[i] = Aleatorio() + '0';
    }

    int soma = 0;
    for(int i = 0; i < 8; i++) {
        soma += id[i] - '0';
    }
    int ultimoDigito = (10 - (soma % 10)) % 10;

    id[8] = '0' + ultimoDigito;
    id[9] = '\0';

    /*
    if(L != NULL) {
        NO_CHAVE_P *P = L->Inicio;
        while (P != NULL) {
            if(P->DADOS != NULL && P->DADOS.)
        }
    }
    */
    return id;
}

// Função para pedir dados de uma pessoa
PESSOA *PedirDadosPessoa(Lista_Chaves_P *P, Lista_D *D, Lista_C *C, Lista_F *F) {
    int dia, mes, ano, id_dist, id_conc;
    char primeiroNome[30], ultimoNome[30], nomeCompleto[100], id_freg[3], *id;
    Freguesia *freguesia = NULL;
    printf("\nAdicionar Pessoa:\n");

    do {
        printf("\nPrimeiro Nome: (0 - Voltar menu) ");
        lerString(primeiroNome, sizeof(primeiroNome));
        if(primeiroNome[0] == '0'){
            return NULL;
        }else if (!strlen(primeiroNome)) {
            printf("\nErro: O primeiro nome e muito pequeno\n");
        }else if(contem_numero(primeiroNome)){
            printf("\nErro: O nome nao pode conter numeros.\n");
        }
    }while(!strlen(primeiroNome) || contem_numero(primeiroNome));

    do {
        printf("\nUltimo Nome: ");
        lerString(ultimoNome, sizeof(ultimoNome));
        if(primeiroNome[0] == '0'){
            return NULL;
        }else if (!strlen(ultimoNome)) {
            printf("\nErro: O ultimo nome e muito pequeno\n");
        }else if(contem_numero(ultimoNome)){
            printf("\nErro: O nome nao pode conter numeros.\n");
        }
    }while(!strlen(primeiroNome) || contem_numero(ultimoNome));

    printf("\nData de nascimento:\n");
    do {
        do {
            printf("  Ano: ");
            scanf("%d", &ano);
            limparBuffer();
            if (ano < 1900 || ano > 2024) {
                printf("\nErro: Ano invalido.\n");
            }
        } while (ano < 1900 || ano > 2024);

        do {
            printf(" Mes: ");
            scanf("%d", &mes);
            limparBuffer();
            if (mes < 1 || mes > 12) {
                printf("\nErro: Mês invalido.\n");
            }
        } while (mes < 1 || mes > 12);

        do {
            printf(" Dia: ");
            scanf("%d", &dia);
            limparBuffer();
            if (dia < 1 || dia > 31) {
                printf("\nErro: Dia invalido.\n");
            }
        } while (dia < 1 || dia > 31 ) ;
        if(validarData(dia,mes,ano) == 0){
            printf("\nErro: Data invalida. Insira outra data que seja válida.\n");
        }
    }while(validarData(dia,mes,ano) == 0);
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
            if (strlen(id_freg) == 1) {
                id_freg[2] = '\0';
                id_freg[1] = id_freg[0];
                id_freg[0] = '0';
            }else if(strlen(id_freg) != 2){
                printf("\nErro: ID de freguesia invalido.\n");
            }
        }while(strlen(id_freg) != 2);
        if(ProcurarFreguesiaPorID(F,id_freg,id_conc,id_dist) == NULL){
            printf("\nErro: Freguesia nao encontrada.\n");
        }else{
            freguesia = ProcurarFreguesiaPorID(F,id_freg,id_conc,id_dist);
        }
    }while(freguesia == NULL);
    id = GerarIDPessoa(P);
    if(id == NULL) {
        printf("\nErro: ID nao foi criado.\n");
        return NULL;
    }
    strcpy(nomeCompleto, primeiroNome);
    strcat(nomeCompleto, " ");
    strcat(nomeCompleto, ultimoNome);
    return CriarPessoa(primeiroNome, ultimoNome, nomeCompleto, dia, mes, ano,id, freguesia);
}

// Função para criar uma lista de pessoas/
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
    if (L->Inicio == NULL || L->num_chaves == 0) {
        printf("\nErro: Lista vazia\n");
        return NULL;
    }
    int a = 0;
    printf("Lista de pessoas com nome %s:\n", nome);
    NO_CHAVE_P *N = L->Inicio;
    while (N != NULL) {
        ElementoP *E = N->DADOS->Inicio;
        while (E != NULL) {
            //printf("NOME: %s, Primeiro Nome: %s, Ultimo Nome: %s, Nome completo: %s \n", nome, E->pessoa->PrimeiroNome, E->pessoa->UltimoNome, E->pessoa->NOME);
            if (strstr(E->pessoa->PrimeiroNome, nome) != NULL ||
                strstr(E->pessoa->UltimoNome, nome) != NULL ||
                strstr(E->pessoa->NOME, nome) != NULL) {
                printf("\nPessoa encontrada:\n");
                MostrarPessoa(E->pessoa);
                a = 1;
            }
            E = E->proximo;
        }
        N = N->Prox;
    }
    if(a == 0){
        printf("\nNenhuma pessoa encontrada.\n");
    }
}

/*void *PesquisarPessoaPorNIF(Lista_Chaves_P *L, char *nif) {
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
*/

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
    if(pessoasArray == NULL){
        printf("Erro: Array de pessoas vazio.\n");
        return;
    }
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
    printf("ID: %s\n", P->ID);
    printf("Data de Nascimento: %d/%d/%d\n", P->dataNascimento->dia, P->dataNascimento->mes, P->dataNascimento->ano);
    printf("Freguesia: %s (ID: %s)\n", P->freguesia->nome, P->freguesia->ID_Todo);
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
            printf("IDADE MAX: %d IDADE:\n", idadeMaxima, anos);
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

ResultadoSobrenome* SobrenomeMaisUsado(Lista_Chaves_P *listaChavesPessoa) {
    if(!listaChavesPessoa || !listaChavesPessoa->Inicio) return NULL;

    NO_CHAVE_P *chaveAtual = listaChavesPessoa->Inicio;
    int ContadorNomes = 0;
    int capacidade = 10;
    char **nomes = (char **)malloc(capacidade * sizeof(char *));
    int *contagem = (int *)calloc(capacidade, sizeof(int));
    if (!nomes || !contagem) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    while (chaveAtual != NULL) {
        ElementoP *pessoaAtual = chaveAtual->DADOS->Inicio;
        while (pessoaAtual != NULL) {
            char *nome = pessoaAtual->pessoa->UltimoNome;
            int found = 0;

            for (int i = 0; i < ContadorNomes; i++) {
                if (strcmp(nomes[i], nome) == 0) {
                    contagem[i]++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (ContadorNomes == capacidade) {
                    capacidade *= 2;
                    nomes = (char **)realloc(nomes, capacidade * sizeof(char *));
                    contagem = (int *)realloc(contagem, capacidade * sizeof(int));
                    if (!nomes || !contagem) {
                        printf("Erro ao realocar memória.\n");
                        free(nomes);
                        free(contagem);
                        return NULL;
                    }
                }
                nomes[ContadorNomes] = strdup(nome);
                contagem[ContadorNomes] = 1;
                ContadorNomes++;
            }

            pessoaAtual = pessoaAtual->proximo;
        }
        chaveAtual = chaveAtual->Prox;
    }

    int maiorContagem = 0;
    char *sobrenomeMaisUsado = NULL;

    for (int i = 0; i < ContadorNomes; i++) {
        if (contagem[i] > maiorContagem) {
            maiorContagem = contagem[i];
            sobrenomeMaisUsado = nomes[i];
        }
    }

    ResultadoSobrenome *resultado = (ResultadoSobrenome *)malloc(sizeof(ResultadoSobrenome));
    if (!resultado) {
        printf("Erro ao alocar memória para o resultado.\n");
        for (int i = 0; i < ContadorNomes; i++) {
            free(nomes[i]);
        }
        free(nomes);
        free(contagem);
        return NULL;
    }

    resultado->sobrenome = sobrenomeMaisUsado ? strdup(sobrenomeMaisUsado) : NULL;
    resultado->contagem = maiorContagem;

    for (int i = 0; i < ContadorNomes; i++) {
        free(nomes[i]);
    }
    free(nomes);
    free(contagem);

    return resultado;
}


// Função para buscar pessoa por ID
PESSOA *buscarPessoaPorID(Lista_Chaves_P *L, char *id) {
    if (!L) return NULL;
    NO_CHAVE_P *N = L->Inicio;
    while (N != NULL) {
        ElementoP *E = N->DADOS->Inicio;
        while (E != NULL) {
            //printf("\n IDPESSOA: %s     ID: %s ", E->pessoa->ID, id);
            if (strcmp(E->pessoa->ID, id) == 0) {
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

            int condicao_Dist = pessoa->freguesia->ID_DIST == id_dist;
            int condicao_Conc = id_conc == 0 || pessoa->freguesia->ID_CONC == id_conc;
            int condicao_Nome = (nome == NULL || strcmp(pessoa->PrimeiroNome, nome) == 0);
            int condicao_Apelido = (apelido == NULL || strcmp(pessoa->UltimoNome, apelido) == 0);
            printf("\nApelido: |%s| e apelido: |%s|\n", pessoa->UltimoNome, apelido);
            if (condicao_Dist && condicao_Conc && condicao_Nome && condicao_Apelido) {
                count++;
            }

            ElementoPessoa = ElementoPessoa->proximo;
        }
        atual = atual->Prox;
    }
    return count;
}


ListaPessoa *LerRequisitantesTXT(Lista_F *listaFreguesias) {
    FILE *arquivo;
    char texto[256];
    char linha[200];
    ListaPessoa *lista = (ListaPessoa *)malloc(sizeof(ListaPessoa));
    if (lista == NULL) {
        snprintf(texto, sizeof(texto), "\nErro ao alocar memória para a lista de pessoas. (LerRequisitantes)\n");
        EscreverLogs(texto);
        return NULL;
    }
    lista->num_Pessoas = 0;
    lista->Inicio = NULL;

    arquivo = fopen("../data/recursos/requisitantes.txt", "r");
    if (arquivo == NULL) {
        snprintf(texto, sizeof(texto), "\nErro ao abrir o arquivo. (LerRequisitantes)\n");
        EscreverLogs(texto);
        free(lista);
        return NULL;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Extrair NIF, nome, data de nascimento e ID da freguesia da linha
        char ID[10], primeiroNome[50] = "", ultimoNome[50] = "", nome[100], nome2[100], id_freg_todo[7], id_freg[3];
        int dia, mes, ano, id_dist, id_conc;
        Freguesia *freg;

        // Use sscanf para extrair dados da linha
        if (sscanf(linha, "%s %[^0-9] %d-%d-%d %6s", ID, nome2, &dia, &mes, &ano, id_freg_todo) != 6) {
            snprintf(texto, sizeof(texto), "\nErro ao ler os dados da linha: %s (requisitantes.txt)\n", linha);
            EscreverLogs(texto);
            continue;
        }


        // Encontrar o primeiro nome
        strcpy(nome, nome2);

        // Encontrar a última ocorrência de um espaço para ultimo nome

        char *token = strtok(nome2, " ");
        if (token != NULL) {
            strcpy(primeiroNome, token);
            char *ultimo = token;
            while ((token = strtok(NULL, " ")) != NULL) {
                ultimo = token;
            }
            strcpy(ultimoNome, ultimo);
        }
        char* temp = trim(ultimoNome);
        strcpy(ultimoNome, temp);

        // Extrair id_dist, id_conc e id_freg do id_freg_todo
        sscanf(id_freg_todo, "%2d%2d%2s", &id_dist, &id_conc, id_freg);

        // Debugging prints
        /*printf("Lendo linha: %s\n", linha);
        printf("ID: %s, Primeiro Nome: %s, Ultimo Nome: |%s|, Data: %02d-%02d-%04d, ID_Freg_Todo: %s\n",
               ID, primeiroNome, ultimoNome, dia, mes, ano, id_freg_todo);
        printf("ID_DIST: %d, ID_CONC: %d, ID_FREG: %s\n", id_dist, id_conc, id_freg);*/

        //Verificar ID
        if(strlen(ID) != 9){
            snprintf(texto, sizeof(texto), "\nErro: O ID %s nao e valido (Não tem 9 digitos) (requisitantes.txt) linha: %s\n", ID,linha);
            EscreverLogs(texto);
            continue;
        }else{
            int soma = 0;
            for(int i = 0; i < strlen(ID); i++){
                if (!isdigit(ID[i])) {
                    snprintf(texto, sizeof(texto), "\nErro: o ID %s nao e valido (Contem letras) (requisitantes.txt) linha: %s\n", ID, linha);
                    EscreverLogs(texto);
                    printf("\nErro: o ID %s nao e valido (requisitantes.txt) (Contem letras) linha: %s\n", ID, linha);
                    continue;
                }
                soma += ID[i] - '0';
            }
            if(soma % 10 != 0){
                snprintf(texto, sizeof(texto), "\nErro: O ID %s nao e valido (A soma nao e multiplo de 10) (requisitantes.txt) linha: %s\n", ID, linha);
                EscreverLogs(texto);
                continue;
            }
        }

        //Verificar Data

        if(validarData(dia,mes,ano) == 0){
            snprintf(texto, sizeof(texto), "\nErro: A data %d-%d-%d nao e valida (requisitantes.txt) linha: %s\n", dia, mes, ano, linha);
            EscreverLogs(texto);
            continue;
        }

        //Verificar FREG
        freg = ProcurarFreguesiaPorID(listaFreguesias, id_freg, id_conc, id_dist);
        if (freg == NULL) {
            snprintf(texto, sizeof(texto), "\nFreguesia nao encontrada para ID_DIST: %d, ID_CONC: %d, ID_FREG: %s (requisitantes.txt) linha: %s .\n", id_dist, id_conc, id_freg, linha);
            EscreverLogs(texto);
            continue;
        }

        // Criar uma nova pessoa e alocar memória
        PESSOA *nova_pessoa = CriarPessoa(primeiroNome, ultimoNome, nome, dia, mes, ano, ID, freg);
        if (nova_pessoa == NULL) {
            snprintf(texto, sizeof(texto), "\nErro ao alocar memória para nova_pessoa. (LerRequisitantes)\n");
            EscreverLogs(texto);
            fclose(arquivo);
            LiberarListaPessoas(lista);
            return NULL;
        }

        // Criar um novo elemento para a lista de pessoas e alocar memória
        ElementoP *novo_elemento = (ElementoP *)malloc(sizeof(ElementoP));
        if (novo_elemento == NULL) {
            snprintf(texto, sizeof(texto), "\nErro ao alocar memória para novo_elemento. (LerRequisitantes)\n");
            EscreverLogs(texto);
            fclose(arquivo);
            LiberarListaPessoas(lista);
            LiberarPessoa(nova_pessoa);
            return NULL;
        }

        // Preencher o elemento com a nova pessoa
        novo_elemento->pessoa = nova_pessoa;
        novo_elemento->proximo = lista->Inicio;
        lista->Inicio = novo_elemento;
        lista->num_Pessoas++;
    }
    fclose(arquivo);
    return lista;
}

void MostrarPessoas(Lista_Chaves_P *listaChaves) {
    if (listaChaves == NULL) {
        printf("Lista de chaves está vazia.\n");
        return;
    }

    NO_CHAVE_P *chaveAtual = listaChaves->Inicio;
    while (chaveAtual != NULL) {
        printf("Chave: %c\n", chaveAtual->Key);

        ListaPessoa *listaPessoas = chaveAtual->DADOS;
        ElementoP *atual = listaPessoas->Inicio;
        while (atual != NULL) {
            printf("ID: %s, Nome: %s, Data de Nascimento: %02d-%02d-%04d\n",
                   atual->pessoa->ID, atual->pessoa->NOME,
                   atual->pessoa->dataNascimento->dia, atual->pessoa->dataNascimento->mes,
                   atual->pessoa->dataNascimento->ano);
            atual = atual->proximo;
        }
        chaveAtual = chaveAtual->Prox;
    }
}

void LiberarPessoa(PESSOA *pessoa) {
    if (pessoa) {
        free(pessoa->PrimeiroNome);
        free(pessoa->UltimoNome);
        free(pessoa->NOME);
        free(pessoa->ID);
        free(pessoa->dataNascimento);
        free(pessoa->freguesia);
        free(pessoa);
    }
}

Lista_Chaves_P *OrganizarListaPessoaPorChave(ListaPessoa *listaPessoa) {
    if (!listaPessoa || listaPessoa->num_Pessoas == 0) {
        return NULL;
    }

    Lista_Chaves_P *listaChaves = (Lista_Chaves_P *)malloc(sizeof(Lista_Chaves_P));
    if (!listaChaves) {
        printf("Erro ao alocar memória para listaChaves.\n");
        return NULL;
    }
    listaChaves->num_chaves = 0;
    listaChaves->Inicio = NULL;

    ElementoP *atualPessoa = listaPessoa->Inicio;
    while (atualPessoa != NULL) {
        char chave = toupper(atualPessoa->pessoa->PrimeiroNome[0]);
        NO_CHAVE_P *atualChave = listaChaves->Inicio;
        NO_CHAVE_P *chaveAnterior = NULL;

        while (atualChave != NULL && atualChave->Key < chave) {
            chaveAnterior = atualChave;
            atualChave = atualChave->Prox;
        }

        if (atualChave == NULL || atualChave->Key != chave) {
            NO_CHAVE_P *novaChave = (NO_CHAVE_P *)malloc(sizeof(NO_CHAVE_P));
            if (!novaChave) {
                printf("Erro ao alocar memória para novaChave.\n");
                return NULL;
            }
            novaChave->Key = chave;
            novaChave->DADOS = (ListaPessoa *)malloc(sizeof(ListaPessoa));
            if (!novaChave->DADOS) {
                printf("Erro ao alocar memória para novaChave->DADOS.\n");
                return NULL;
            }
            novaChave->DADOS->num_Pessoas = 0;
            novaChave->DADOS->Inicio = NULL;
            novaChave->Prox = atualChave;

            if (chaveAnterior == NULL) {
                listaChaves->Inicio = novaChave;
            } else {
                chaveAnterior->Prox = novaChave;
            }
            listaChaves->num_chaves++;
            atualChave = novaChave;
        }

        AdicionarPessoaNaLista(atualChave->DADOS, atualPessoa->pessoa);
        atualPessoa = atualPessoa->proximo;
    }

    return listaChaves;
}

void AdicionarPessoaNaLista(ListaPessoa *lista, PESSOA *pessoa) {
    ElementoP *novoElemento = (ElementoP *)malloc(sizeof(ElementoP));
    if (!novoElemento) {
        printf("Erro ao alocar memória para novoElemento.\n");
        return;
    }
    novoElemento->pessoa = pessoa;
    novoElemento->proximo = lista->Inicio;
    lista->Inicio = novoElemento;
    lista->num_Pessoas++;
}

void GuardarPessoas(Lista_Chaves_P *listaPessoas, const char *nomeFicheiro){
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro %s.\n", nomeFicheiro);
        return;
    }

    NO_CHAVE_P *atualChave = listaPessoas->Inicio;
    while(atualChave != NULL){
        ElementoP *elementoAtual = atualChave->DADOS->Inicio;
        while(elementoAtual != NULL){
            PESSOA *pessoa = elementoAtual->pessoa;
            fprintf(ficheiro, "%s %s %d-%d-%d %s\n",
                    pessoa->ID,
                    pessoa->NOME,
                    pessoa->dataNascimento->dia,
                    pessoa->dataNascimento->mes,
                    pessoa->dataNascimento->ano,
                    pessoa->freguesia->ID_Todo);
            elementoAtual = elementoAtual->proximo;
        }
        atualChave = atualChave->Prox;
    }
    fclose(ficheiro);
}

