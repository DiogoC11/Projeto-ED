#ifndef REQUISICAO_H_INCLUDED
#define REQUISICAO_H_INCLUDED

#include "Pessoa.h"
#include "Biblioteca.h"
#include "Livro.h"
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
    ptPESSOA *Pessoa;
    LIVRO *Livro;
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


ListaRequisicoes *criarListaR();
ElementoR *criarElementoR(REQUISICAO *R);
void MostrarRequisicao(REQUISICAO *P);
void DestruirRequisicao(REQUISICAO *P);
int countPeopleFromDistrictWithName(Lista_Chaves_P *peopleList, char *districtX, char *nameY);
void returnRequestedBook(Lista_Chaves_L *bookList, char *ISBN);
void listRequestedBooks(Lista_Chaves_L *bookList);
REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L, Lista_Chaves_L *C);

//devolver livro requisitado
//listar livros requisitados
#endif // REQUISICAO_H_INCLUDED

