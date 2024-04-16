#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *NOME;
    int ID;
    char *CATEGORIA;
}PESSOA;

PESSOA *CriarPessoa(int _id, char *_nome, char *_categoria);
void MostrarPessoa(PESSOA *P);
void DestruirPessoa(PESSOA *P);
//criar uma requisição de um livro
//devolver livro requisitado
//listar livros requisitados

#endif // PESSOA_H_INCLUDED
