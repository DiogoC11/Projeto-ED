#ifndef REQUISICAO_H_INCLUDED
#define REQUISICAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pessoa.h"
#include "Livro.h"
typedef struct
{
    //int ID_PESSOA;
    //int ID_LIVRO;
    int ID;
    PESSOA *Ptr_Req;
    LIVRO *Ptr_Livro;
    //DATA Data_Requisicao;
}REQUISICAO;

typedef struct elementoR{
    REQUISICAO *requisicao;
    struct elementoR *proximo;
} ElementoR, *ptElementoR;

typedef struct {
    int num_Requisicoes;
    ElementoR *Inicio;
}ListaRequisicoes, *ptListaR;
//qddwqdq


REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L);
ListaRequisicoes *criarListaR();
ElementoR *criarElementoR(REQUISICAO *R);
void MostrarRequisicao(REQUISICAO *P);
void DestruirRequisicao(REQUISICAO *P);

int CalcularIdadeMaxima(PESSOA** listaPessoas, int tamanhoListaPessoas);  //idade maxima de todos os requisitantes
float CalcularIdadeMedia(PESSOA** listaPessoas, int tamanhoListaPessoas); //idade media de todos os requisitantes
int IdadeComMaisRequisitantes(PESSOA** listaPessoas, int tamanhoListaPessoas); //idade com mais requisitantes
int NumeroPessoasIdadeSuperiorX(PESSOA** listaPessoas, int tamanhoListaPessoas, int x); //numero de pessoas cuja a idade superior a x

void ListarPessoasSemRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //lista de pessoas sem requisições
void ListarPessoasComRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //lista de pessoas com requisiçao
char* SobrenomeMaisUsadoNasRequisicoes(REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //sobrenome mais usado nas requisiçoes
//numero de pessoas do distrito x, com o nome/apelido y

//devolver livro requisitado
//listar livros requisitados
#endif // REQUISICAO_H_INCLUDED

