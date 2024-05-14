#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Livro.h"
#include "Pessoa.h"

void escreverLivroNoFicheiro(FILE *ficheiro, LIVRO *livro);

#endif // BIBLIOTECA_H_INCLUDED
