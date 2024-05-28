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

typedef struct {
    int ID_DIST;
    char *nome;
    Lista_C *Conc;
} Distrito;

typedef struct elementoD {
    Distrito *Info;
    struct elementoD *Prox;
} ElementoD;

typedef struct {
    int num_Distritos;
    ElementoD *Inicio;
} Lista_D;


// Pessoa

typedef struct{
    int dia;
    int mes;
    int ano;
}data;

typedef struct{
    char *PrimeiroNome;
    char *UltimoNome;
    char *NOME;
    int ID;
    data *dataNascimento;
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

//listar distritos pelo id distrito
//listar concelhos de id do distrito
//listar freguesias de id do concelho


int CalcularIdadeMaxima(Lista_Chaves_P *listaChavesPessoa);  //idade maxima de todos os requisitantes

float CalcularIdadeMedia(Lista_Chaves_P *listaChavesPessoa); //idade media de todos os requisitantes
int IdadeComMaisRequisitantes(Lista_Chaves_P *listaChavesPessoa); //idade com mais requisitantes
int ContarPessoasComIdadeSuperiorA(Lista_Chaves_P *listaChavesPessoa, int idadeLimite); //numero de pessoas cuja a idade superior a x


//
// TESTAR DEPOIS ESTAS FUNCOES depois de fazer as requisiçoes
//
void ListarPessoasSemRequisicoes(Lista_Chaves_P *listaChavesPessoa); //lista de pessoas sem requisições
void ListarPessoasComRequisicao(Lista_Chaves_P *listaChavesPessoa); //lista de pessoas com requisiçao
char* SobrenomeMaisUsado(Lista_Chaves_P *listaChavesPessoa); //sobrenome mais usado nas requisiçoes

Lista_F* LerTXT();
void LibertarFreguesias(Lista_F *lista);
Lista_C* LerTXTConc();
void LibertarConcelhos(Lista_C *lista);
void ListarConcelhosPorDistrito(Lista_D *listadistritos,Lista_C *listaConcelhos, int idDistrito);
char* ObterNomeDistrito(Lista_D *listaDistritos, int idDistrito);
Lista_D* LerTXTDist();
void LibertarDistritos(Lista_D *lista);
void ListarDistritosPorID(Lista_D *listaDistritos, int idDistrito);
void ListarFreguesiasPorConcelho(Lista_C *listaConcelhos, int idConcelho);
void associa_concelhos_a_distritos(Lista_D *lista_distritos, Lista_C *lista_concelhos);
void mostra_concelhos_do_distrito(int id_distrito, Lista_D *listaDistrito);





void LiberarListaPessoas(ListaPessoa *lista);
void LiberarListaChaves_P(Lista_Chaves_P *lista);




void lerArquivoPessoas(const char *nome_arquivo, ListaPessoa *listaPessoa);


#endif // PESSOA_H_INCLUDED
