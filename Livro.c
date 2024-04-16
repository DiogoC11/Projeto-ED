
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
