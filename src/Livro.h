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
}LIVRO;

LIVRO *CriarLivro(int _id, char *_nome, char *_area);
void MostrarLivro(LIVRO *P);
void DestruirLivro(LIVRO *P);
void ListarLivros(LIVRO *P, int numLivros);
LIVRO *PesquisarLivroPorISBN(LIVRO *P, int numLivros, char *isbn);
//listar livros;
//pesquisar por isbn;
//livro mais recente;



//livro mais requisitado;
//area mais requisitada;
//area com mais livros;


#endif // LIVRO_H_INCLUDED
