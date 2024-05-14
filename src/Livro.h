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
typedef struct NO_CHAVE_L {
    char categoria[50];
    ListaLivro *DADOS;
    struct NO_CHAVE_L *Prox;
} NO_CHAVE_L;

typedef struct{
    int num_chaves;
    NO_CHAVE_L *Inicio;
}Lista_Chaves_L;

LIVRO *CriarLivro(char *_ISBN, char *_nome, char *_area, int _anoPublicacao,char *_autor);
LIVRO *PedirDadosLivro(Lista_Chaves_L *C);
void MostrarLivro(LIVRO *P);
void DestruirLivro(LIVRO *P);
ListaLivro *criarListaL();
ElementoL *criar_elementoL(LIVRO *L);
void *AdicionarLivro(ElementoL *E, Lista_Chaves_L *C);
void ListarLivros(Lista_Chaves_L *C);
LIVRO *PesquisarLivroPorISBN(Lista_Chaves_L *C, char *isbn);
LIVRO *LivroMaisRecente(Lista_Chaves_L * L);
void AreaMaisLivros(Lista_Chaves_L *C);

//funcoes hashing-----------------------------------------------------------------------
Lista_Chaves_L *CriarListaChaves();
NO_CHAVE_L *AdicionarChave(Lista_Chaves_L *L, char *categoria);

//---------------------------------------------------------------------------------------


//livro mais requisitado;
//area mais requisitada;

#endif // LIVRO_H_INCLUDED
