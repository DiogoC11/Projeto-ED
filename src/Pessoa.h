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
    char ID[10];
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

typedef struct NO_CHAVE { // Inicial da pessoa
    char *KEY; // 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', ...
    ListaPessoa *DADOS;
    struct NO_CHAVE *Prox; // 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', ...
} NO_CHAVE;

typedef struct {
    char codigo[7]; // O c�digo da freguesia
    char nome[100]; // O nome da freguesia
} Freguesia;

typedef struct {
    char codigo[10]; // O c�digo do requisitante
    char nome[100]; // O nome completo do requisitante
    char data_nascimento[11]; // A data de nascimento do requisitante (no formato dd-mm-yyyy)
    int numero_requisicoes; // O n�mero de requisi��es feitas pelo requisitante
} Requisitante;

typedef struct {
    char codigo[3]; // O c�digo do distrito
    char nome[50]; // O nome do distrito
} Distrito;

typedef struct {
    char codigo[5]; // O c�digo do conselho
    char nome[50]; // O nome do conselho
} Conselho;




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
//criar uma requisi��o de um livro
//devolver livro requisitado
//listar livros requisitados

#endif // PESSOA_H_INCLUDED
