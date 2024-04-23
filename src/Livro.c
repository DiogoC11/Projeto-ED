
#include "Livro.h"

LIVRO *CriarLivro(int _id, char *_nome, char *_area, int _anoPublicacao)
{
    LIVRO *P = (LIVRO *)malloc(sizeof(LIVRO));
    P->NOME = (char *)malloc((strlen(_nome) + 1)*sizeof(char));
    strcpy(P->NOME, _nome);
    P->AREA = (char *)malloc((strlen(_area) + 1)*sizeof(char));
    strcpy(P->AREA, _area);
    P->ID = _id;
    P->anoPublicacao = _anoPublicacao;
    return P;
}
LIVRO PedirDadosLivro(){
    printf("\nCriar Livro: ");
    printf("\nNome do Livro: ");
    printf("\nArea");
}
void MostrarLivro(LIVRO *P)
{
    printf("\tPESSOA: ID: %d [%s] [%s]\n", P->ID, P->NOME, P->AREA);
}
void DestruirLivro(LIVRO *P)
{
    free (P->NOME);
    free (P->AREA);
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
    E->proximo = L->Inicio;
    L->Inicio = E;
    L->num_Livros++;
}

void ListarLivros(ListaLivro *L){
    printf("Lista de Livros:\n");
    Elemento *E = L->Inicio;
    for (int i = 0; i < L->num_Livros; i++){
        printf("Livro %d:\n", i + 1);
        MostrarLivro(E->livro);
        E = E->proximo;
    }
}
LIVRO *PesquisarLivroPorISBN(LIVRO *P, int numLivros, char *isbn) {
    for (int i = 0; i < numLivros; i++) {
        if (strcmp(&P[i].ISBN, isbn) == 0) {
            return &P[i];
        }
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
