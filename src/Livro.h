#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *NOME;
    char ISBN;
    int ID;
    char *AREA;
    int anoPublicacao;
}LIVRO;

typedef struct elemento{
    LIVRO *livro;
    struct elemento *proximo;
}Elemento, *ptElemento;

typedef struct{
    int num_Livros;
    Elemento *Inicio;
}ListaLivro, *ptLista;

LIVRO *CriarLivro(int _id, char *_nome, char *_area, int _anoPublicacao);
void MostrarLivro(LIVRO *P);
void DestruirLivro(LIVRO *P);
ListaLivro *criarLista();
Elemento *criar_elemento(LIVRO *L);
void *AdicionarLivro(ListaLivro *L,Elemento *E);
void ListarLivros(ListaLivro *L);
LIVRO *PesquisarLivroPorISBN(LIVRO *P, int numLivros, char *isbn);
LIVRO *LivroMaisRecente(ListaLivro *L);
//---------------------------------------------------------------------------------------

//listar livros;
//pesquisar por isbn;
//livro mais recente;



//livro mais requisitado;
//area mais requisitada;
//area com mais livros;


#endif // LIVRO_H_INCLUDED
