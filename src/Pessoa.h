#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED
#include "Livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Localidade

typedef struct {
    int ID_DIST;
    int ID_CONC;
    char ID[3];
    char nome[50];
} Freguesia;

typedef struct elementoF {
    Freguesia *freguesia;
    struct elementoF *prox;
} ElementoF;

typedef struct {
    int num_Freguesias;
    ElementoF *Inicio;
} Lista_F;

typedef struct {
    int ID_DIST;
    int ID_CONC;
    char nome[50];
    Lista_F *freguesias;
} Concelho;

typedef struct elementoC {
    Concelho *concelho;
    struct elementoC *prox;
} ElementoC;

typedef struct {
    int num_Concelhos;
    ElementoC *Inicio;
} Lista_C;

typedef struct Distrito {
    int ID_DIST;
    char *nome;
    Lista_C *Conc; // Lista de concelhos associados ao distrito
    int NEL; // Número de concelhos associados
} Distrito;

// Estrutura para Elemento de Distrito na Lista
typedef struct ElementoD {
    Distrito *Info;
    struct ElementoD *Prox;
} ElementoD;

// Estrutura para Lista de Distritos
typedef struct {
    int num_Distritos;
    ElementoD *Inicio;
} Lista_D;
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
int compararIdFreguesia(const void* a, const void* b);
void *OrganizarPorNome(Lista_Chaves_P *L, int op);
void *ListarPessoas(Lista_Chaves_P *L);
void MostrarPessoa(PESSOA *P);
PESSOA *buscarPessoaPorID(Lista_Chaves_P *L, int id);
int verificarIDArquivo(char *idRequisitante);
//int lerFreguesias(const char* nome_arquivo, Freguesia **freguesias);

int CalcularIdadeMaxima(PESSOA** listaPessoas, int tamanhoListaPessoas);  //idade maxima de todos os requisitantes
//float CalcularIdadeMedia(PESSOA** listaPessoas, int tamanhoListaPessoas); //idade media de todos os requisitantes
//int IdadeComMaisRequisitantes(PESSOA** listaPessoas, int tamanhoListaPessoas); //idade com mais requisitantes
//int NumeroPessoasIdadeSuperiorX(PESSOA** listaPessoas, int tamanhoListaPessoas, int x); //numero de pessoas cuja a idade superior a x


Lista_F* LerTXT();
void LibertarFreguesias(Lista_F *lista);
Lista_C* LerTXTConc();
void LibertarConcelhos(Lista_C *lista);
Lista_D* LerTXTDist();
void LibertarDistritos(Lista_D *lista);
void LibertarListaChaves_P(Lista_Chaves_P *lista);




void lerArquivoPessoas(const char *nome_arquivo, ListaPessoa *listaPessoa);
int lerDistritos(const char* nome_arquivo, Distrito **distritos);
int lerConcelhos(const char* nome_arquivo, Concelho **Concelhos);

#endif // PESSOA_H_INCLUDED
