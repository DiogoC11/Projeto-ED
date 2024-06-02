
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
    char ID_Todo[7];
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
    char *ID;
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

//adicional

typedef struct {
    char *sobrenome;
    int contagem;
} ResultadoSobrenome;

//criar pessoa
ListaPessoa *LerRequisitantesTXT(Lista_F *listaFreguesias);
PESSOA *CriarPessoa(char *primeiroNome, char *ultimoNome, char *Nome, int dia, int mes, int ano, char *id, Freguesia *freguesia);
char *GerarIDPessoa(Lista_Chaves_P *L);
PESSOA *PedirDadosPessoa(Lista_Chaves_P *P, Lista_D *D, Lista_C *C, Lista_F *F);
ListaPessoa *criarListaP();
ElementoP *criarElementoP(PESSOA *P);
NO_CHAVE_P *criarNoChave(char chave);
Lista_Chaves_P *criarListaChave ();

//funcoes principais
void *AdicionarPessoa(Lista_Chaves_P *C, ElementoP *E) ;
void *PesquisarPesssoaPorNome(Lista_Chaves_P *L, char *nome);
void ListaOrganizada(Lista_Chaves_P *L, int op);
int CalcularIdadeMaxima(Lista_Chaves_P *listaChavesPessoa);  //idade maxima de todos os requisitantes
float CalcularIdadeMedia(Lista_Chaves_P *listaChavesPessoa); //idade media de todos os requisitantes
int IdadeComMaisRequisitantes(Lista_Chaves_P *listaChavesPessoa); //idade com mais requisitantes
int ContarPessoasComIdadeSuperiorA(Lista_Chaves_P *listaChavesPessoa, int idadeLimite); //numero de pessoas cuja a idade superior a x
int IdadeComMaisRequisitantes(Lista_Chaves_P *listaChavesPessoa); //idade com mais requisitantes
void ListarPessoasSemRequisicoes(Lista_Chaves_P *listaChavesPessoa); //lista de pessoas sem requisições
void ListarPessoasComRequisicao(Lista_Chaves_P *listaChavesPessoa); //lista de pessoas com requisiçao
ResultadoSobrenome *SobrenomeMaisUsado(Lista_Chaves_P *listaChavesPessoa); //sobrenome mais usado nas requisiçoes
int ContarPessoasDeUmLocal(Lista_Chaves_P *listaPessoas, int id_dist, int id_conc, char *nome, char *apelido);

//funcoes secundarias
//void *PesquisarPessoaPorNIF(Lista_Chaves_P *L, char *nif);
int compararPrimeiroNome(const void *a, const void *b);
int compararUltimoNome(const void *a, const void *b);
int compararIdFreguesia(const void* a, const void* b);
void *ListarPessoas(Lista_Chaves_P *L);
void MostrarPessoa(PESSOA *P);
PESSOA *buscarPessoaPorID(Lista_Chaves_P *L, char *id);
int verificarIDArquivo(char *idRequisitante);
void MostrarPessoas(Lista_Chaves_P *listaChaves);
Lista_Chaves_P *OrganizarListaPessoaPorChave(ListaPessoa *listaPessoa);
void AdicionarPessoaNaLista(ListaPessoa *lista, PESSOA *pessoa);

//freguesias
void ListarFreguesias(Lista_F *listaFreguesias);
Lista_F* LerTXT();
void LibertarFreguesias(Lista_F *lista);
void ListarFreguesiasPorConcelho(Lista_C *listaConcelhos, int idConcelho);
void associa_freguesias_a_concelhos(Lista_C *lista_concelhos, Lista_F *lista_freguesias);
void MostraFreguesiasConcelho(int id_concelho, Lista_C *listaConcelhos,int id_distrito);
Freguesia* ProcurarFreguesiaPorID(Lista_F *listaFreguesias, char *id_freg, int id_conc, int id_dist);


//concelhos
Lista_C* LerTXTConc();
void LibertarConcelhos(Lista_C *lista);
void ListarConcelhosPorDistrito(Lista_D *listadistritos,Lista_C *listaConcelhos, int idDistrito);
char* ObterNomeDistrito(Lista_D *listaDistritos, int idDistrito);
Lista_D* LerTXTDist();
void LibertarDistritos(Lista_D *lista);
void ListarDistritosPorID(Lista_D *listaDistritos, int idDistrito);
void ListarFreguesiasPorConcelho(Lista_C *listaConcelhos, int idConcelho);
void associa_concelhos_a_distritos(Lista_D *lista_distritos, Lista_C *lista_concelhos);
void associa_freguesias_a_concelhos(Lista_C *lista_concelhos, Lista_F *lista_freguesias);
void MostraConcelhosDistrito(int id_distrito, Lista_D *listaDistrito);
Concelho* ProcurarConcelhoPorID(Lista_C *listaConcelhos, int id_conc, int id_dist);


//distritos
Lista_D* LerTXTDist();
void LibertarDistritos(Lista_D *lista);
//void ListarDistritosPorID(Lista_D *listaDistritos, int idDistrito);
void ListarDistritos(Lista_D *listaDistritos);
char* ObterNomeDistrito(Lista_D *listaDistritos, int idDistrito);
Distrito* ProcurarDistritoPorID(Lista_D *listaDistritos, int id);

//funcoes apagar
void LiberarListaPessoas(ListaPessoa *lista);
void LiberarListaChaves_P(Lista_Chaves_P *lista);
void LiberarPessoa(PESSOA *pessoa);

//funcoes guardar
//void GuardarPessoas(ListaPessoa *listaPessoas);


#endif // PESSOA_H_INCLUDED
