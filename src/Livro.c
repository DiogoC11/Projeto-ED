
#include "Livro.h"

LIVRO *CriarLivro( char *_ISBN, char *_nome, char *_area, int _anoPublicacao, char *_autor)
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
    return P;
}
LIVRO *PedirDadosLivro(){
    char nome[50], area[50], ISBN[50], autor[50], temp[100];
    int anoPublicacao;
    fflush(stdin);
    printf("\nCriar Livro: ");
    printf("\nTitulo do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%[^\n]", nome);

    printf("\nArea do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%[^\n]", area);

    printf("\nAno de Publicacao: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%d", &anoPublicacao);

    printf("\nISBN: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%49[^\n]", ISBN);

    printf("\nAutor do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%49[^\n]", autor);

    return CriarLivro(ISBN, nome, area, anoPublicacao, autor);
}
void MostrarLivro(LIVRO *P)
{
    printf("\nLivro: \nISBN: %s\nTitulo: %s \nArea: %s \nAutor: %s \nAno de Publicacao: %d\n\n", P->ISBN, P->NOME, P->AREA, P->Autor, P->anoPublicacao);
}
void DestruirLivro(LIVRO *P)
{
    free (P->NOME);
    free (P->AREA);
    free(P->ISBN);
    free(P->Autor);
    free (P);
}
ListaLivro *criarLista(){
    ListaLivro *L = (ListaLivro *) malloc(sizeof (ListaLivro));
    if (!L) return NULL;
    L->num_Livros = 0;
    L->Inicio = NULL;
    return L;
}

Elemento *criar_elemento(LIVRO *L){
    Elemento *e = (Elemento * ) malloc(sizeof (Elemento));
    if(!e) return NULL;
    e->livro = L;
    e->proximo = NULL;
    return e;
}

void *AdicionarLivro(ListaLivro *L,Elemento *E){
    if(!L) return NULL;
    if(!E) return NULL;
    if(L->num_Livros == 0){
        L->Inicio = E;
    }else {
        Elemento *ultimo = L->Inicio;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = E;
    }
    L->num_Livros ++;
    printf("\nLivro adicionado a biblioteca.");
}

void ListarLivros(ListaLivro *L){
    printf("\nLista de Livros:\n");
    Elemento *E = L->Inicio;
    for (int i = 0; i < L->num_Livros; i++){
        printf("Livro %d:\n", i + 1);
        MostrarLivro(E->livro);
        E = E->proximo;
    }
}
LIVRO *PesquisarLivroPorISBN(ListaLivro *L, char *isbn) {
    Elemento *E = L->Inicio;
    for (int i = 0; i < L->num_Livros; i++) {
        if(strcmp(E->livro->ISBN,isbn) == 0){
            return E->livro;
        }
        E = E->proximo;
    }
    return NULL;
}
LIVRO *LivroMaisRecente(ListaLivro *L) {
    if (L->num_Livros == 0) {
        return NULL;
    }
    Elemento *E = L->Inicio;
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
