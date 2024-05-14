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
typedef struct NO_CHAVE {
    char categoria[50];
    ListaLivro *DADOS;
    struct NO_CHAVE *Prox;
} NO_CHAVE;

typedef struct{
    int num_chaves;
    NO_CHAVE *Inicio;
}Lista_Chaves;

LIVRO *CriarLivro(char *_ISBN, char *_nome, char *_area, int _anoPublicacao,char *_autor);
LIVRO *PedirDadosLivro(Lista_Chaves *C);
void MostrarLivro(LIVRO *P);
void DestruirLivro(LIVRO *P);
ListaLivro *criarListaL();
ElementoL *criar_elementoL(LIVRO *L);
void *AdicionarLivro(ListaLivro *L,ElementoL *E, Lista_Chaves *C);
void ListarLivros(ListaLivro *L);
LIVRO *PesquisarLivroPorISBN(Lista_Chaves *C, char *isbn);
LIVRO *LivroMaisRecente(ListaLivro *L);

//funcoes hashing-----------------------------------------------------------------------
Lista_Chaves *CriarListaChaves();
NO_CHAVE *AdicionarChave(Lista_Chaves *L, char *categoria);

//---------------------------------------------------------------------------------------


//livro mais requisitado;
//area mais requisitada;
//area com mais livros;


#endif // LIVRO_H_INCLUDED
