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
    int codigo_freguesia[6];
    int numero_requiscoes;
}PESSOA;

typedef struct ElementoP{
    PESSOA *pessoa;
    struct elemento *proximo;
}ElementoP, *ptElementoP;

typedef struct{
    int num_Pessoas;
    ElementoP *Inicio;
}ListaPessoa, *ptListaP;

typedef struct NO_CHAVE_P { 
    char Key;
    ListaPessoa *DADOS;
    struct NO_CHAVE_P *Prox; 
} NO_CHAVE_P;

typedef struct{
    int num_chaves;
    NO_CHAVE_P *Inicio;
    int num_Pessoas;
}Lista_Chaves_P;

typedef struct {
    char codigo[7]; // O código da freguesia
    char nome[100]; // O nome da freguesia
} Freguesia;

typedef struct {
    char codigo[3]; // O código do distrito
    char nome[50]; // O nome do distrito
} Distrito;

typedef struct {
    char codigo[5]; // O código do conselho
    char nome[50]; // O nome do conselho
} Conselho;




PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, int dia, int mes, int ano);
PESSOA *PedirDadosPessoa(); // adicionar para pedir freguesia
ListaPessoa *criarListaP();
ElementoP *criar_elementoP(PESSOA *P);
void *AdicionarPessoa(Lista_Chaves_P *C,ElementoP *E);
void *PesquisarPesssoaPorNome(Lista_Chaves_P *L, char *nome);
int compararPrimeiroNome(const void *a, const void *b);
int compararUltimoNome(const void *a, const void *b);
void *OrganizarPorNome(ListaPessoa *L, int op);
void *ListarPessoas(ListaPessoa *L);
void MostrarPessoa(PESSOA *P);
NO_CHAVE_P *criarNoChave(char chave);
void inserirPessoaHash(NO_CHAVE_P **tabela, char *chave, PESSOA *pessoa);
PESSOA *buscarPessoaPorID(ptListaP lista, int id);
int verificarIDArquivo(char *idRequisitante);
//criar uma requisição de um livro
//devolver livro requisitado
//listar livros requisitados



#endif // PESSOA_H_INCLUDED
