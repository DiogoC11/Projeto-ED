#include "Livro.h"

// Função para encontrar o no_chave por uma KEY
NO_CHAVE *encontrarNoChave(NO_CHAVE *noChave, char *chave) {
    while (noChave != NULL) {
        if (strcmp(noChave->categoria, chave) == 0) {
            return noChave;
        }
        noChave = noChave->Prox;
    }
    return NULL;
}

LIVRO *CriarLivro(char *_ISBN, char *_nome, char *_area, int _anoPublicacao, char *_autor)
{
    LIVRO *P = (LIVRO *)malloc(sizeof(LIVRO));
    P->NOME = (char *)malloc((strlen(_nome) + 1)*sizeof(char));
    strcpy(P->NOME, _nome);
    P->AREA = (char *)malloc((strlen(_area) + 1)*sizeof(char));
    strcpy(P->AREA, _area);
    P->anoPublicacao = _anoPublicacao;
    P->ISBN = (char *) malloc(strlen(_ISBN + 1)*sizeof(char));
    strcpy(P->ISBN,_ISBN);
    P->Autor = (char *) malloc(strlen(_autor + 1)*sizeof(char));
    strcpy(P->Autor,_autor);
    P->Disponivel = 0;
    return P;
}

LIVRO *PedirDadosLivro(Lista_Chaves *C){
    char nome[50], area[50], ISBN[50], autor[50], temp[100];
    int anoPublicacao;
    fflush(stdin);
    printf("\nCriar Livro: ");

    do {
        printf("\nISBN: ");
        fgets(temp, sizeof(temp), stdin);
        sscanf(temp, "%49[^\n]", ISBN);

        if (PesquisarLivroPorISBN(C, ISBN) != NULL) {
            printf("\nErro: O ISBN inserido já existe.\n");
        }
    }while(PesquisarLivroPorISBN(C,ISBN) != NULL);

    printf("\nTitulo do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%[^\n]", nome);

    printf("\nArea do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%[^\n]", area);

    printf("\nAno de Publicacao: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%d", &anoPublicacao);

    printf("\nAutor do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%49[^\n]", autor);

    // Verifica se a area existe
    NO_CHAVE *noChave = encontrarNoChave(L->Inicio, area);
    if (noChave == NULL) {
        printf("\nErro: A area inserida nao existe.\n");
        return NULL;
    }
    return CriarLivro(ISBN, nome, area, anoPublicacao, autor);
}

void MostrarLivro(LIVRO *P)
{
    char disponivel[4];
    if(P->Disponivel ){
        strcpy(disponivel,"NAO");
    }else{
        strcpy(disponivel,"SIM");
    }
    printf("\nLivro: \nISBN: %s\nTitulo: %s \nArea: %s \nAutor: %s \nAno de Publicacao: %d\nDisponivel? %s\n", P->ISBN, P->NOME, P->AREA, P->Autor, P->anoPublicacao,disponivel);
}
void DestruirLivro(LIVRO *P)
{
    free (P->NOME);
    free (P->AREA);
    free(P->ISBN);
    free(P->Autor);
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

void *AdicionarLivro(ListaLivro *L,ElementoL *E, Lista_Chaves *C){
    int a = 0;
    if(!L) return NULL;
    if(!E) return NULL;
    if(L->num_Livros == 0){
        L->Inicio = E;
    }else {
        ElementoL *ultimo = L->Inicio;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = E;
    }
    for(int i = 0; i < C->num_chaves; i++){
        if(C->Inicio->categoria == E->livro->AREA){
            if(C->Inicio->DADOS->Inicio==0) {
                C->Inicio->DADOS->Inicio = E;
                a = 1;
            }else{
                ElementoL  *ultimo = C->Inicio->DADOS->Inicio;
                while (ultimo->proximo != NULL){
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = E;
                a = 1;
            }
            C->Inicio->DADOS->num_Livros ++;
        }
        C->Inicio = C->Inicio->Prox;
    }
    if(!a){
        NO_CHAVE *newChave = AdicionarChave(C,E->livro->AREA);
        C->Inicio->DADOS->Inicio = E;
        C->Inicio->DADOS->num_Livros ++;
    }
    printf("\nLivro adicionado a biblioteca.\n");
}

void ListarLivros(ListaLivro *L){
    printf("\nLista de Livros:\n");
    ElementoL *E = L->Inicio;
    for (int i = 0; i < L->num_Livros; i++){
        printf("Livro %d:\n", i + 1);
        MostrarLivro(E->livro);
        E = E->proximo;
    }
}
LIVRO *PesquisarLivroPorISBN(Lista_Chaves *C, char *isbn) {
    ElementoL *E = C->Inicio->DADOS->Inicio;
    for(int i = 0; i < C->num_chaves; i++){
        for (int j = 0; i < C->Inicio->DADOS->num_Livros; i++) {
            if(strcmp(E->livro->ISBN,isbn) == 0){
                return E->livro;
            }
            E = E->proximo;
        }
    }

    return NULL;
}
LIVRO *LivroMaisRecente(ListaLivro *L) {
    if (L->num_Livros == 0) {
        return NULL;
    }
    ElementoL *E = L->Inicio;
    LIVRO *maisRecente = E->livro;
    E = E->proximo;
    while (E != NULL) {
        if (E->livro->anoPublicacao > maisRecente->anoPublicacao) {
            maisRecente = E->livro;
        }
        E = E->proximo;
    }
    return maisRecente;
}

Lista_Chaves *CriarListaChaves(){
    Lista_Chaves *L = (Lista_Chaves *)malloc(sizeof(Lista_Chaves));
    L->num_chaves = 0;
    L->Inicio = NULL;
    return L;
}

NO_CHAVE *AdicionarChave(Lista_Chaves *L, char *categoria)
{
    if (!L) return NULL;
    NO_CHAVE *chave = (NO_CHAVE *)malloc(sizeof(NO_CHAVE));
    strcpy(chave->categoria, categoria);
    chave->DADOS = criarListaL();
    chave->Prox = L->Inicio;
    L->Inicio = chave;
    L->num_chaves ++;
    return L;
}
