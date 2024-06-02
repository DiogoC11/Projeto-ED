#include "Livro.h"
#include "ctype.h"
#include "Uteis.h"

// Função para encontrar o NO_CHAVE_L por uma KEY
NO_CHAVE_L *encontrarNoChave(NO_CHAVE_L *noChave, char *chave) {
    while (noChave != NULL) {
        if (strcmp(noChave->categoria, chave) == 0) {
            return noChave;
        }
        noChave = noChave->Prox;
    }
    return NULL;
}

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
    NO_CHAVE_L *N = C->Inicio;
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
        printf("\nEscolha uma area: (0-Inserir nova area)\n");
        while(N != NULL){
            printf("%s\n", N->categoria);
            N = N->Prox;
        }
        printf("\nInsira a area: ");
        scanf("%s", area);
        for (int i = 0; i < strlen(area); i++) {
        area[i] = toupper(area[i]);
        }
        if(area[0] == '0'){
            do{
                printf("\nInsira a nova area: ");
                scanf("%s", area);
                printf("\nDeseja adicionar a area %s? (1-Sim, 2-Nao): ", area);
                scanf("%d", &op);
                limparBuffer();
                for (int i = 0; i < strlen(area); i++) {
                    area[i] = toupper(area[i]);
                }
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
        }else if(encontrarNoChave(C->Inicio, area) == NULL){
                printf("\nErro: A area inserida nao existe.\n");
        }
    }while(encontrarNoChave(C->Inicio, area) == NULL);
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
    }while( anoPublicacao>2024 || anoPublicacao<999);

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
        strcpy(disponivel,"NAO");
    }else{
        strcpy(disponivel,"SIM");
    }
    if(P->Requisitado ){
        strcpy(requisitado,"NAO");
    }else{
        strcpy(requisitado,"SIM");
    }
    if(P->quant_requisicaoL > 0){
        printf("\nTitulo: %s\n ISBN: %s \n Area: %s \n Autor: %s \n Ano de Publicacao: %d\n Disponivel? %s\n Requisitado? %s\n Quantidade de vezes requisitado: %d\n", P->NOME, P->ISBN, P->AREA, P->Autor, P->anoPublicacao,disponivel,requisitado,P->quant_requisicaoL);
    }else{
        printf("\nTitulo: %s\n ISBN: %s \n Area: %s \n Autor: %s \n Ano de Publicacao: %d\n Disponivel? %s\n Requisitado? %s\n",P->NOME , P->ISBN, P->AREA, P->Autor, P->anoPublicacao,disponivel, requisitado);
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
            printf("\nO Livro foi adicionado a biblioteca.\n");
            return 1;
        }
        Inicio = Inicio->Prox;
    }
    printf("\nO Livro nao foi adicionado a biblioteca.\n");
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
    ElementoL *E = C->Inicio->DADOS->Inicio;
    while (N != NULL){
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
            if(maisRequisitado == NULL || E->livro->quant_requisicaoL > maisRequisitado->quant_requisicaoL){
                maisRequisitado = E->livro;
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
        if(N->quant_requisicaoN > Area->quant_requisicaoN){
            Area = N;
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
    NO_CHAVE_L *chave = (NO_CHAVE_L *)malloc(sizeof(NO_CHAVE_L));
    strcpy(chave->categoria, categoria);
    chave->DADOS = criarListaL();
    chave->Prox = L->Inicio;
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