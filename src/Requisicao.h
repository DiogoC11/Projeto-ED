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


REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L);
void MostrarRequisicao(REQUISICAO *P);
void DestruirRequisicao(REQUISICAO *P);
REQUISICAO* PesquisarRequisitantePorNome(char* nome, REQUISICAO** listaRequisicoes, int tamanhoLista); //pesquisar requisitante pelo nome

//listar requisitantes com filtro(1- nome,2-apelido,3-freguisia)

//idade maxima de todos os requisitantes
//idade media de todos os requisitantes
//numero de pessoas cuja a idade superior a x
//idade com mais requisitantes

void ListarRequisicoesPorRequisitante(PESSOA* requisitante, REQUISICAO** listaRequisicoes, int tamanhoLista); //lista requisiçoes de um requisitante
void ListarPessoasSemRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //lista de pessoas sem requisições
void ListarPessoasComRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes); //lista de pessoas com requisiçao

//sobrenome mais usado nas requisiçoes
//numero de pessoas do distrito x, com o nome/apelido y

#endif // REQUISICAO_H_INCLUDED

