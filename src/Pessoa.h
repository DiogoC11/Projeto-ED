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

PESSOA *CriarPessoa(char *_nome, int _ID, int _dia, int _mes, int _ano);
void MostrarPessoa(PESSOA *P);
ptListaP criarListaPessoa();
ptElementoP criarElemento(PESSOA *pessoa);
void inserirPessoa(ptListaP lista, PESSOA *pessoa);
NO_CHAVE *criarNoChave(char *chave);
void inserirPessoaHash(NO_CHAVE **tabela, char *chave, PESSOA *pessoa);
//criar uma requisição de um livro
//devolver livro requisitado
//listar livros requisitados

#endif // PESSOA_H_INCLUDED
