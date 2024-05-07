#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int dia;
    int mes;
    int ano;
}DATANASC;

typedef struct
{
    char *NOME;
    int ID;
    DATANASC *dataNascimento;
}PESSOA;

typedef struct elemento{
    PESSOA *pessoa;
    struct elemento *proximo;
}ElementoP, *ptElementoP;

typedef struct{
    int num_Pessoas;
    ElementoP *Inicio;
}ListaPessoa, *ptListaP;

// Hashing
typedef struct NO_CHAVE { // Inicial da pessoa
    char *KEY; // 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', ...
    ListaPessoa *DADOS;
    struct NO_CHAVE *Prox; // 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', ...
} NO_CHAVE;

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
