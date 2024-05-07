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
    char *PrimeiroNome;
    char *UltimoNome;
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

PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, int dia, int mes, int ano);
PESSOA *PedirDadosPessoa();
ListaPessoa *criarListaP();
ElementoP *criar_elementoP(PESSOA *P);
void *AdicionarPessoa(ListaPessoa *L,ElementoP *E);
void *PesquisarPesssoaPorNome(ListaPessoa *L, char *nome);
int compararPrimeiroNome(const void *a, const void *b);
int compararUltimoNome(const void *a, const void *b);
void *OrganizarPorNome(ListaPessoa *L, int op);
void *ListarPessoas(ListaPessoa *L);
void MostrarPessoa(PESSOA *P);
NO_CHAVE *criarNoChave(char *chave);
void inserirPessoaHash(NO_CHAVE **tabela, char *chave, PESSOA *pessoa);
PESSOA *buscarPessoaPorID(ptListaP lista, int id);
int verificarIDArquivo(char *idRequisitante);
//criar uma requisição de um livro
//devolver livro requisitado
//listar livros requisitados

#endif // PESSOA_H_INCLUDED
