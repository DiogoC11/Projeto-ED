#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"


typedef struct
{
    char *NOME;
    int ID;
    char *AREA;
}LIVRO;

typedef struct elemento{
    LIVRO *livro;
    struct elemento *proximo;
}Elemento, *ptElemento;

typedef struct{
    int num_Livros;
    Elemento *Inicio;
}ListaLivro, *ptLista;

LIVRO *CriarLivro(int _id, char *_nome, char *_area);
void MostrarLivro(LIVRO *P);
void DestruirLivro(LIVRO *P);
ListaLivro *criarLista();
Elemento *criar_elemento(LIVRO *L);
void *AdicionarLivro(ListaLivro *L,Elemento *E);
void ListarLivros(ListaLivro *L)
//pesquisar por isbn;
//livro mais recente;



//livro mais requisitado;
//area mais requisitada;
//area com mais livros;


#endif // LIVRO_H_INCLUDED
