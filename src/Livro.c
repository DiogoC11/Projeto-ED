
#include "Livro.h"

LIVRO *CriarLivro(int _id, char *_nome, char *_area)
{
    LIVRO *P = (LIVRO *)malloc(sizeof(LIVRO));
    P->NOME = (char *)malloc((strlen(_nome) + 1)*sizeof(char));
    strcpy(P->NOME, _nome);
    P->AREA = (char *)malloc((strlen(_area) + 1)*sizeof(char));
    strcpy(P->AREA, _area);
    P->ID = _id;
    return P;
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
void ListarLivros(LIVRO *P, int numLivros)
{
    printf("Lista de Livros:\n");
    for (int i = 0; i < numLivros; i++)
    {
        printf("Livro %d:\n", i + 1);
        MostrarLivro(&P[i]);
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
