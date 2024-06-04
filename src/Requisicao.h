#ifndef REQUISICAO_H_INCLUDED
#define REQUISICAO_H_INCLUDED

#include "Pessoa.h"
#include "Livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct {
    int ID;
    PESSOA *Pessoa;
    LIVRO *Livro;
    data *Data_Requisicao;
    int Entregue;
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
REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L);
ListaRequisicoes *criarListaR();
ElementoR *criarElementoR(REQUISICAO *R);
void InserirRequisicaoNaLista(ptListaR listaRequisicoes, ElementoR *elemento, Lista_Chaves_L *listaLivros);
void MostrarRequisicao(REQUISICAO *P);
void DestruirRequisicao(REQUISICAO *P);

//funcoes principais
void DevolverLivro(Lista_Chaves_L *bookList, ListaRequisicoes *reqList, char *ISBN, char *ID);
void ListarLivrosRequisitados(ListaRequisicoes *listaRequisicoes);
void MostrarRequisicoesPorID(ListaRequisicoes *listaRequisicoes, Lista_Chaves_P *listaChavesPessoa, char *ID);

//funcoes secundarias
void ListarPessoasSemRequisicoes(Lista_Chaves_P *listaChavesPessoa, ListaRequisicoes *listaRequisicoes);
void ListarPessoasComRequisicao(Lista_Chaves_P *listaChavesPessoa, ListaRequisicoes *listaRequisicoes);

//TESTAR///
REQUISICAO *AdicionarRequisicao(Lista_Chaves_P *listaChavesPessoa, Lista_Chaves_L *listaChavesLivro, ListaRequisicoes *listaRequisicoes);
void LibertarListaRequisicoes(ListaRequisicoes *lista);

//funcoes apagar
void LiberarRequisicao(REQUISICAO *R);


#endif // REQUISICAO_H_INCLUDED