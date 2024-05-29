#ifndef REQUISICAO_H_INCLUDED
#define REQUISICAO_H_INCLUDED

#include "Pessoa.h"
#include "Biblioteca.h"
#include "Livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct {
    int ID;
    PESSOA *Pessoa;
    LIVRO *Livro;
    data *Data_Requisicao;
} REQUISICAO;


typedef struct elementoR{
    REQUISICAO *requisicao;
    struct elementoR *proximo;
} ElementoR, *ptElementoR;

typedef struct {
    int num_Requisicoes;
    ElementoR *Inicio;
}ListaRequisicoes, *ptListaR;

//criar REQUISICAO
REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L, Lista_Chaves_L *C);
ListaRequisicoes *criarListaR();
ElementoR *criarElementoR(REQUISICAO *R);
void MostrarRequisicao(REQUISICAO *P);
void DestruirRequisicao(REQUISICAO *P);

//funcoes principais
int DevolverLivro(Lista_Chaves_L *bookList, ListaRequisicoes *reqList, char *ISBN);
void ListarLivrosRequisitados(ListaRequisicoes *listaRequisicoes);
void MostrarRequisicoesPorNIF(ListaRequisicoes *listaRequisicoes, Lista_Chaves_P *listaChavesPessoa, char *NIF);



//TESTAR//
void AdicionarRequisicao(Lista_Chaves_P *listaChavesPessoa, Lista_Chaves_L *listaChavesLivro, ListaRequisicoes *listaRequisicoes);
void LibertarListaRequisicoes(ListaRequisicoes *lista);



#endif // REQUISICAO_H_INCLUDED

