#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include "Requisicao.h"
#include "Livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Localidade

typedef struct {
    char codigo[7];
    char nome[50];
} Freguesia;

typedef struct elementoF{
    Freguesia *freguesia;
    struct elementoF *prox;
}ElementoF;

typedef struct {
    int num_Freguesias;
    ElementoF *Inicio;
}Lista_F;

typedef struct {
    char codigo[5];
    char nome[50];
    Lista_F *freguesias;
} Conselho;

typedef struct elementoC{
    Conselho *conselho;
    struct elementoC *prox;
}ElementoC;

typedef struct {
    int num_Concelho;
    ElementoC *Inicio;
}Lista_C;

typedef struct {
    char codigo[3];
    char nome[50];
    Lista_C *concelhos;
} Distrito;

typedef struct elementoD{
    Distrito *distrito;
    struct elementoD *prox;
}ElementoD;

typedef struct {
    int num_Distrito;
    ElementoD *Inicio;
}Lista_D;

// Pessoa

typedef struct{
    int dia;
    int mes;
    int ano;
}DATANASC;

typedef struct{
    char *PrimeiroNome;
    char *UltimoNome;
    char *NOME;
    int ID;
    DATANASC *dataNascimento;
    Freguesia *freguesia;
    int numero_requisicoes;
}PESSOA, *ptPESSOA;

typedef struct ElementoP{
    PESSOA *pessoa;
    struct ElementoP *proximo;
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
}Lista_Chaves_P;

PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, int dia, int mes, int ano);
PESSOA *PedirDadosPessoa();
ListaPessoa *criarListaP();
ElementoP *criarElementoP(PESSOA *P);
NO_CHAVE_P *criarNoChave(char chave);
Lista_Chaves_P *criarListaChave ();
void *AdicionarPessoa(Lista_Chaves_P *C, ElementoP *E) ;
void *PesquisarPesssoaPorNome(Lista_Chaves_P *L, char *nome);
int compararPrimeiroNome(const void *a, const void *b);
int compararUltimoNome(const void *a, const void *b);
void *OrganizarPorNome(Lista_Chaves_P *L, int op);
void *ListarPessoas(Lista_Chaves_P *L);
void MostrarPessoa(PESSOA *P);
PESSOA *buscarPessoaPorID(Lista_Chaves_P *L, int id);
int verificarIDArquivo(char *idRequisitante);
int lerFreguesias(const char* nome_arquivo, Freguesia **freguesias);
void lerArquivoPessoas(const char *nome_arquivo, ListaPessoa *listaPessoa);
int lerDistritos(const char* nome_arquivo, Distrito **distritos);
int lerConselhos(const char* nome_arquivo, Conselho **conselhos);

#endif // PESSOA_H_INCLUDED
