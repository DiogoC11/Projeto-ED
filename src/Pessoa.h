#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *NOME;
    int ID;
    char *dataNascimento;
}PESSOA;

typedef struct elemento{
    PESSOA *pessoa;
    struct elemento *proximo;
}ElementoP, *ptElementoP;

typedef struct{
    int num_Pessoas;
    ElementoP *Inicio;
}ListaPessoa, *ptListaP;

PESSOA *CriarPessoa(char *_nome, char *dataNascimento);
PESSOA *PedirDadosPessoa();
ListaPessoa *criarListaP();
ElementoP *criar_elementoP(PESSOA *L);
void *AdicionarPessoa(ListaPessoa *L,ElementoP *E);
void MostrarPessoa(PESSOA *P);
void DestruirPessoa(PESSOA *P);
int GerarID();
//criar uma requisição de um livro
//devolver livro requisitado
//listar livros requisitados

#endif // PESSOA_H_INCLUDED
