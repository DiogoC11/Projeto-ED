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
    int quant_requisicaoL;
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
    int quant_requisicaoN;
    ListaLivro *DADOS;
    struct NO_CHAVE_L *Prox;
} NO_CHAVE_L;

typedef struct{
    int num_chaves;
    NO_CHAVE_L *Inicio;
}Lista_Chaves_L;

//criar livro
LIVRO *CriarLivro( char *ISBN, char *_nome, char *_area, int _anoPublicacao,char *_autor);
LIVRO *PedirDadosLivro(Lista_Chaves_L *C);
void MostrarLivro(LIVRO *P);
ListaLivro *criarListaL();
ElementoL *criar_elementoL(LIVRO *L);
Lista_Chaves_L *CriarListaChaves();
int *AdicionarChave(Lista_Chaves_L *L, char *categoria);

//funcoes principais
int AdicionarLivro(ElementoL *E, Lista_Chaves_L *C);
int ListarLivros(Lista_Chaves_L *C);
NO_CHAVE_L *AreaMaisLivros(Lista_Chaves_L *C);
LIVRO *PesquisarLivroPorISBN(Lista_Chaves_L *C, char *isbn);
LIVRO *LivroMaisRecente(Lista_Chaves_L * L);
LIVRO *LivroMaisRequisitado(Lista_Chaves_L *C);
NO_CHAVE_L *AreaMaisRequisitada(Lista_Chaves_L *C);
void DestruirLivro(LIVRO *P);

//apagar
void LiberarListaLivros(ListaLivro *lista);
void LiberarListaChaves_L(Lista_Chaves_L *lista);

#endif // LIVRO_H_INCLUDED

