#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *NOME;
    char *ISBN;
    char *AREA;
    int anoPublicacao;
    char *Autor;
    int Disponivel;
}LIVRO;

typedef struct elemento{
    LIVRO *livro;
    struct elemento *proximo;
}ElementoL, *ptElementoL;

typedef struct{
    int num_Livros;
    ElementoL *Inicio;
}ListaLivro, *ptListaL;

// Hashing
typedef struct NO_CHAVE { // Inicial do livro
    char *KEY; // 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', ...
    ListaLivro *DADOS;
    struct NO_CHAVE *Prox; // 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', ...
} NO_CHAVE;

LIVRO *CriarLivro(char *_ISBN, char *_nome, char *_area, int _anoPublicacao,char *_autor);
LIVRO *PedirDadosLivro(ListaLivro *L);
void MostrarLivro(LIVRO *P);
void DestruirLivro(LIVRO *P);
ListaLivro *criarListaL();
ElementoL *criar_elementoL(LIVRO *L);
void *AdicionarLivro(ListaLivro *L,ElementoL *E);
void ListarLivros(ListaLivro *L);
LIVRO *PesquisarLivroPorISBN(ListaLivro *L, char *isbn);
LIVRO *LivroMaisRecente(ListaLivro *L);
//---------------------------------------------------------------------------------------


//livro mais requisitado;
//area mais requisitada;
//area com mais livros;


#endif // LIVRO_H_INCLUDED
