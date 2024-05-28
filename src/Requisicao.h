#ifndef REQUISICAO_H_INCLUDED
#define REQUISICAO_H_INCLUDED

#include "Pessoa.h"
#include "Biblioteca.h"
#include "Livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct
{
    int ID;
    ptPESSOA *Pessoa;
    LIVRO *Livro;
    data *Data_Requisicao;
}REQUISICAO;

typedef struct elementoR{
    REQUISICAO *requisicao;
    struct elementoR *proximo;
} ElementoR, *ptElementoR;

typedef struct {
    int num_Requisicoes;
    ElementoR *Inicio;
}ListaRequisicoes, *ptListaR;


ListaRequisicoes *criarListaR();
ElementoR *criarElementoR(REQUISICAO *R);
void MostrarRequisicao(REQUISICAO *P);
void DestruirRequisicao(REQUISICAO *P);

int countPeopleFromDistrictWithName(Lista_Chaves_P *peopleList, char *districtX, char *nameY);
int DevolverLivro(Lista_Chaves_L *bookList, ListaRequisicoes *reqList, char *ISBN);
void ListaLivrosRequisitados(ListaRequisicoes *bookList);

REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L, Lista_Chaves_L *C);


//TESTAR
void AdicionarRequisicao(Lista_Chaves_P *listaChavesPessoa, Lista_Chaves_L *listaChavesLivro, ListaRequisicoes *listaRequisicoes);
void LibertarListaRequisicoes(ListaRequisicoes *lista);



#endif // REQUISICAO_H_INCLUDED

