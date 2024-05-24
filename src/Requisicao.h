#ifndef REQUISICAO_H_INCLUDED
#define REQUISICAO_H_INCLUDED

#include "Pessoa.h"
//#include "Livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int dia;
    int mes;
    int ano;
}DATA_Req;

typedef struct
{
    int ID;
  //  ptPESSOA *Pessoa;
  //  LIVRO *Livro;
    DATA_Req *Data_Requisicao;
}REQUISICAO;

typedef struct elementoR{
    REQUISICAO *requisicao;
    struct elementoR *proximo;
} ElementoR, *ptElementoR;

typedef struct {
    int num_Requisicoes;
    ElementoR *Inicio;
}ListaRequisicoes, *ptListaR;


//REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L);
ListaRequisicoes *criarListaR();
ElementoR *criarElementoR(REQUISICAO *R);
void MostrarRequisicao(REQUISICAO *P);
void DestruirRequisicao(REQUISICAO *P);



//void ListarPessoasSemRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //lista de pessoas sem requisições
//void ListarPessoasComRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //lista de pessoas com requisiçao
//char* SobrenomeMaisUsadoNasRequisicoes(REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //sobrenome mais usado nas requisiçoes
//numero de pessoas do distrito x, com o nome/apelido y

//devolver livro requisitado
//listar livros requisitados
#endif // REQUISICAO_H_INCLUDED

