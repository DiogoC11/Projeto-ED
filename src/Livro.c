#include "Livro.h"
#include "ctype.h"
#include "Uteis.h"

LIVRO *CriarLivro(char *ISBN, char *_nome, char *_area, int _anoPublicacao, char *_autor)
{
    LIVRO *P = (LIVRO *)malloc(sizeof(LIVRO));
    P->NOME = (char *)malloc((strlen(_nome) + 1)*sizeof(char));
    strcpy(P->NOME, _nome);
    P->AREA = (char *)malloc((strlen(_area) + 1)*sizeof(char));
    strcpy(P->AREA, _area);
    P->anoPublicacao = _anoPublicacao;
    P->ISBN = (char *) malloc(strlen(ISBN + 1)*sizeof(char));
    strcpy(P->ISBN,ISBN);
    P->Autor = (char *) malloc(strlen(_autor + 1)*sizeof(char));
    strcpy(P->Autor,_autor);
    P->Disponivel = 1;
    P->Requisitado = 0;
    P->quant_requisicaoL = 0;
    return P;
}

LIVRO *PedirDadosLivro(Lista_Chaves_L *C){
    char nome[50], area[50], autor[50], ISBN[14];
    int anoPublicacao, op;
    printf("\nCriar Livro: ");
    do {
        printf("\nISBN: ");
        scanf("%s", ISBN);
        limparBuffer();
        if (strlen(ISBN) != 13) {
            printf("\nErro: O ISBN tem de ter 13 digitos.(%d)\n", strlen(ISBN));
        } else if (PesquisarLivroPorISBN(C, ISBN) != NULL) {
            printf("\nErro: O ISBN inserido ja existe.\n");
        }
    } while ( strlen(ISBN) != 13 || PesquisarLivroPorISBN(C, ISBN) != NULL);

    do{
        printf("\nTitulo do Livro: ");
        lerString(nome,  sizeof (nome));
        if(!strlen(nome)){
            printf("\nErro: O nome do livro e muito pequeno\n");
        }
    }while(!strlen(nome));

    printf("\nArea do Livro: \n");
    do {
        NO_CHAVE_L *N = C->Inicio;
        printf("\nEscolha uma area: (0-Inserir nova area)\n");
        while(N != NULL){
            printf("- %s\n", N->categoria);
            N = N->Prox;
        }
        printf("\nInsira a area: ");
        scanf("%s", area);
        for (int i = 0; i < strlen(area); i++) {
        area[i] = toupper(area[i]);
        }
        strcat(area, " ");
        if(area[0] == '0'){
            do{
                printf("\nInsira a nova area: ");
                scanf("%s", area);
                strcat(area, " ");
                printf("\nDeseja adicionar a area %s? (1-Sim, 2-Nao): ", area);
                scanf("%d", &op);
                limparBuffer();
                switch (op) {
                    case 1:
                        if (!AdicionarChave(C, area)) {
                            printf("\nErro: Area nao adicionada.\n");
                        } else {
                            printf("\nArea %s adicionada.\n",area);
                        }
                        break;
                    case 2:
                        printf("\nArea nao foi adicionada.\n");
                        break;
                    default:
                        printf("\nOpcao invalida.\n");
                        break;
                }
            }while(op != 1 && op != 2);
        }else if(AreaExisteNaLista(C, area) == 0){
                printf("\nErro: A area inserida nao existe.\n");
        }
    }while(AreaExisteNaLista(C, area) == 0);
    do {
        printf("\nAno de Publicacao: ");
        scanf("%d", &anoPublicacao);
        limparBuffer();
        if(anoPublicacao>2024){
            printf("\nErro: Insira um ano anterior ao ano atual.\n");
        }else if(anoPublicacao<0) {
            printf("\nErro: O ano tem de ser positivo.\n");
        }else if(isalpha(anoPublicacao)){
            printf("\nErro: Insira um numero inteiro.\n");
        }
    }while( anoPublicacao>2024 || anoPublicacao<0);

    do{
        printf("\nAutor do Livro: ");
        lerString(autor,  sizeof (autor));
        if(strlen(autor) < 3){
            printf("\nErro: O nome do autor e muito pequeno\n");
        }
    }while(!strlen(autor));

    return CriarLivro(ISBN, nome, area, anoPublicacao, autor);
}

void MostrarLivro(LIVRO *P)
{
    char disponivel[4];
    char requisitado[4];
    if(P->Disponivel ){
        strcpy(disponivel,"SIM");
    }else{
        strcpy(disponivel,"NAO");
    }
    if(P->Requisitado ){
        strcpy(requisitado,"SIM");
    }else{
        strcpy(requisitado,"NAO");
    }
    if(P->quant_requisicaoL > 0){
        printf("\nTitulo: %s\n ISBN: %s \n Area: %s \n Ano de Publicacao: %d \n Autor: %s \n Disponivel? %s\n Requisitado? %s\n Quantidade de vezes requisitado: %d\n", P->NOME, P->ISBN, P->AREA, P->anoPublicacao, P->Autor,disponivel,requisitado,P->quant_requisicaoL);
    }else{
        printf("\nTitulo: %s\n ISBN: %s \n Area: %s \n Ano de Publicacao: %d \n Autor: %s \n Disponivel? %s\n Requisitado? %s\n",P->NOME , P->ISBN, P->AREA, P->anoPublicacao, P->Autor,disponivel, requisitado);
    }
}
void DestruirLivro(LIVRO *P)
{
    /*free (P->NOME);
    free (P->AREA);
    free(P->Autor);*/
    P->Disponivel = 1;
    free (P);
}
ListaLivro *criarListaL(){
    ListaLivro *L = (ListaLivro *) malloc(sizeof (ListaLivro));
    if (!L) return NULL;
    L->num_Livros = 0;
    L->Inicio = NULL;
    return L;
}

ElementoL *criar_elementoL(LIVRO *L){
    ElementoL *e = (ElementoL * ) malloc(sizeof (ElementoL));
    if(!e) return NULL;
    e->livro = L;
    e->proximo = NULL;
    return e;
}

int AdicionarLivro(ElementoL *E, Lista_Chaves_L *C) {
    if (!C) return 0;
    if (!E) return 0;
    NO_CHAVE_L *Inicio = C->Inicio;
    while (Inicio != NULL) {
        if (strcmp(Inicio->categoria, E->livro->AREA) == 0) {
            if (Inicio->DADOS->Inicio == NULL) {
                Inicio->DADOS->Inicio = E;
                //printf("\nLivro adicionado a biblioteca no inicio da categoria %s.\n", Inicio->categoria);
            } else {
                ElementoL *ultimo = Inicio->DADOS->Inicio;
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = E;
                //printf("\nLivro adicionado a biblioteca na categoria %s.\n", Inicio->categoria);
            }
            Inicio->DADOS->num_Livros++;
            //printf("\nO Livro foi adicionado a biblioteca.\n");
            return 1;
        }
        Inicio = Inicio->Prox;
    }
    //printf("\nO Livro nao foi adicionado a biblioteca.\n");
    return 0;
}
int ListarLivros(Lista_Chaves_L *C) {
    if (!C || C->num_chaves == 0) {
        printf("\nErro: Lista de Livros vazia.\n");
        return 1;
    }
    printf("\nLista de Livros:\n");
    NO_CHAVE_L *N = C->Inicio;
    while (N != NULL) {
        ElementoL *E = N->DADOS->Inicio;
        while (E != NULL) {
            MostrarLivro(E->livro);
            E = E->proximo;
        }
        N = N->Prox;
    }
    return 0;
}
LIVRO *PesquisarLivroPorISBN(Lista_Chaves_L *C, char *isbn) {
    if(C->Inicio == NULL) return NULL;
    NO_CHAVE_L *N = C->Inicio;
    while (N != NULL){
        ElementoL *E = N->DADOS->Inicio;
        while(E != NULL){
            if(strcmp(E->livro->ISBN,isbn) == 0){
                return E->livro;
            }
            E = E->proximo;
        }
        N = N->Prox;
    }

    return NULL;
}
LIVRO *LivroMaisRecente(Lista_Chaves_L *L) {
    if (L->num_chaves == 0) {
        return NULL;
    }
    NO_CHAVE_L *N = L->Inicio;
    LIVRO *maisRecente = NULL;
    while (N != NULL) {
        ElementoL *E = N->DADOS->Inicio;
        while (E != NULL) {
            if (maisRecente == NULL || E->livro->anoPublicacao > maisRecente->anoPublicacao) {
                maisRecente = E->livro;
            }
            E = E->proximo;
        }
        N = N->Prox;
    }
    return maisRecente;
}


NO_CHAVE_L *AreaMaisLivros(Lista_Chaves_L *C) {
    if (!C || C->num_chaves == 0) {
        printf("\nErro: Lista de Chaves vazia ou não inicializada.\n");
        return NULL;
    }
    NO_CHAVE_L *Area = C->Inicio;
    NO_CHAVE_L *Inicio = C->Inicio;
    while (Inicio != NULL) {
        if (Inicio->DADOS->num_Livros > Area->DADOS->num_Livros) {
            Area = Inicio;
        }
        Inicio = Inicio->Prox;
    }
    return Area;
}

LIVRO *LivroMaisRequisitado(Lista_Chaves_L *C){
    if(!C || C->Inicio == NULL) return NULL;
    NO_CHAVE_L *N = C->Inicio;
    LIVRO *maisRequisitado = NULL;
    while (N != NULL){
        ElementoL *E = C->Inicio->DADOS->Inicio;
        while(E != NULL){
            if(E->livro->quant_requisicaoL > 0){
                if(maisRequisitado == NULL || E->livro->quant_requisicaoL > maisRequisitado->quant_requisicaoL){
                    maisRequisitado = E->livro;
                }
            }
            E = E->proximo;
        }
        N = N->Prox;
    }
    return maisRequisitado;
}

NO_CHAVE_L *AreaMaisRequisitada(Lista_Chaves_L *C){
    if(!C || C->Inicio == NULL) return NULL;
    NO_CHAVE_L *N = C->Inicio;
    NO_CHAVE_L *Area = C->Inicio;
    while (N != NULL){
        if(N->quant_requisicaoN > 0){
            if(N->quant_requisicaoN > Area->quant_requisicaoN){
                Area = N;
            }
        }
        N = N->Prox;
    }
    return Area;
}


Lista_Chaves_L *CriarListaChaves(){
    Lista_Chaves_L *L = (Lista_Chaves_L *)malloc(sizeof(Lista_Chaves_L));
    L->num_chaves = 0;
    L->Inicio = NULL;
    return L;
}

int *AdicionarChave(Lista_Chaves_L *L, char *categoria){
    if (!L) return 0;
    for (int i = 0; i < strlen(categoria); i++) {
        categoria[i] = toupper(categoria[i]);
    }
    NO_CHAVE_L *chave = (NO_CHAVE_L *)malloc(sizeof(NO_CHAVE_L));
    strcpy(chave->categoria, categoria);
    chave->DADOS = criarListaL();
    chave->Prox = L->Inicio;
    chave->quant_requisicaoN = 0;
    L->Inicio = chave;
    L->num_chaves ++;
    return (int *)1;
}

void LiberarListaLivros(ListaLivro *lista) {
    ElementoL *atual = lista->Inicio;
    while (atual != NULL) {
        ElementoL *temp = atual;
        atual = atual->proximo;
        free(temp->livro);
        free(temp);
    }
    free(lista);
}


void LiberarListaChaves_L(Lista_Chaves_L *lista) {
    NO_CHAVE_L *atual = lista->Inicio;
    while (atual != NULL) {
        NO_CHAVE_L *temp = atual;
        atual = atual->Prox;
        LiberarListaLivros(temp->DADOS);
        free(temp);
    }
    free(lista);
}

NO_CHAVE_L* ProcurarNoChavePorLivro(LIVRO *livro, Lista_Chaves_L *listaChaves) {
    if (livro == NULL || listaChaves == NULL) {
        return NULL;
    }

    NO_CHAVE_L *atual = listaChaves->Inicio;
    while (atual != NULL) {
        if (strcmp(atual->categoria, livro->AREA) == 0) {
            return atual;
        }
        atual = atual->Prox;
    }

    return NULL; // Se não encontrar, retorna NULL
}

void GuardarLivrosEmFicheiro(Lista_Chaves_L *listaChaves, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro %s\n", nomeFicheiro);
        return;
    }

    NO_CHAVE_L *noChaveAtual = listaChaves->Inicio;
    while (noChaveAtual != NULL) {
        ElementoL *elementoAtual = noChaveAtual->DADOS->Inicio;
        while (elementoAtual != NULL) {
            LIVRO *livroAtual = elementoAtual->livro;
            fprintf(ficheiro, "%s %s %s %d %s %d %d %d\n",
                    livroAtual->NOME,
                    livroAtual->ISBN,
                    livroAtual->AREA,
                    livroAtual->anoPublicacao,
                    livroAtual->Autor,
                    livroAtual->Disponivel,
                    livroAtual->Requisitado,
                    livroAtual->quant_requisicaoL);
            elementoAtual = elementoAtual->proximo;
        }
        noChaveAtual = noChaveAtual->Prox;
    }

    fclose(ficheiro);
}
int isStringEmptyOrSpaces(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

int AreaExisteNaLista(Lista_Chaves_L *listaChaves, const char *area) {
    if (listaChaves == NULL || area == NULL) {
        return 0;
    }

    NO_CHAVE_L *chaveAtual = listaChaves->Inicio;
    while (chaveAtual != NULL) {
        if (strcmp(chaveAtual->categoria, area) == 0) {
            return 1;
        }
        chaveAtual = chaveAtual->Prox;
    }

    return 0;
}

void LerLivrosDoFicheiro(Lista_Chaves_L *listaChaves, const char *nomeFicheiro) {
    char linha[200];
    char texto[256];
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) {
        snprintf(texto, sizeof(texto), "\nErro ao abrir o ficheiro %s (LerLivrosDoFicheiro)\n", nomeFicheiro);
        EscreverLogs(texto);
        return;
    }
    while(fgets(linha, sizeof (linha), ficheiro) != NULL) {
        char nome[50] = "", isbn[14], area[50] = "", autor[50] = "";
        int anoPublicacao, disponivel, requisitado, quant_requisicaoL;

        char *token = strtok(linha, " ");
        while (token != NULL && !isdigit(token[0])) {
            strcat(nome, token);
            strcat(nome, " ");
            token = strtok(NULL, " ");
        }
        if (isStringEmptyOrSpaces(nome)) {
            snprintf(texto, sizeof(texto), "\nErro: O nome esta vazio ou contem apenas espaços linha: %s (livros.txt)\n", linha);
            EscreverLogs(texto);
            continue;
        }

        strcpy(isbn, token);
        if (strlen(isbn) != 13) {
            snprintf(texto, sizeof(texto), "\nErro: O ISBN não tem 13 dígitos linha: %s (livros.txt)\n", linha);
            EscreverLogs(texto);
            continue;
        }

        token = strtok(NULL, " ");
        while (token != NULL && !isdigit(token[0])) {
            strcat(area, token);
            strcat(area, " ");
            token = strtok(NULL, " ");
        }
        if (isStringEmptyOrSpaces(area)) {
            snprintf(texto, sizeof(texto), "\nErro: A área está vazia ou contém apenas espaços linha: %s (livros.txt)\n", linha);
            EscreverLogs(texto);
            continue;
        }

        anoPublicacao = atoi(token);
        if (anoPublicacao > 2024 || anoPublicacao < 0) {
            snprintf(texto, sizeof(texto), "\nErro: O ano de publicação não é válido linha: %s (livros.txt)\n", linha);
            EscreverLogs(texto);
            continue;
        }

        token = strtok(NULL, " ");
        while (token != NULL && !isdigit(token[0])) {
            strcat(autor, token);
            strcat(autor, " ");
            token = strtok(NULL, " ");
        }
        if (isStringEmptyOrSpaces(autor)) {
            snprintf(texto, sizeof(texto), "\nErro: O autor está vazio ou contém apenas espaços linha: %s (livros.txt)\n", linha);
            EscreverLogs(texto);
            continue;
        }

        disponivel = atoi(token);
        if(disponivel != 0 && disponivel != 1) {
            snprintf(texto, sizeof(texto), "\nErro: O valor de disponível %d não é válido linha: %s (livros.txt)\n", disponivel, linha);
            EscreverLogs(texto);
            continue;
        }

        token = strtok(NULL, " ");
        requisitado = atoi(token);
        if(requisitado != 0 && requisitado != 1) {
            snprintf(texto, sizeof(texto), "\nErro: O valor de requisitado %d não é válido linha: %s (livros.txt)\n", requisitado, linha);
            EscreverLogs(texto);
            continue;
        }

        token = strtok(NULL, " ");
        quant_requisicaoL = atoi(token);
        if(quant_requisicaoL < 0) {
            snprintf(texto, sizeof(texto), "\nErro: O valor da quantidade de requisicoes %d não é válido linha: %s (livros.txt)\n", quant_requisicaoL, linha);
            EscreverLogs(texto);
            continue;
        }

        LIVRO *novoLivro = CriarLivro(isbn, nome, area, anoPublicacao, autor);
        novoLivro->Disponivel = disponivel;
        novoLivro->Requisitado = requisitado;
        novoLivro->quant_requisicaoL = quant_requisicaoL;
        /*MostrarLivro(novoLivro);
        printf("disponivel %d\n", disponivel);
        printf("requisitado %d\n", requisitado);
        printf("quant_requisicaoL %d\n", quant_requisicaoL);*/
        if(!AreaExisteNaLista(listaChaves, area)) {
            AdicionarChave(listaChaves, area);
        }
        ElementoL *novoElemento = criar_elementoL(novoLivro);
        AdicionarLivro(novoElemento, listaChaves);
    }

    fclose(ficheiro);
}


