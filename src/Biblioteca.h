#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Livro.h"
#include "Pessoa.h"
#include "Requisicao.h"
#include "Uteis.h"

void GravarXML(Lista_Chaves_L * ListaL, Lista_Chaves_P * ListaP, ListaRequisicoes * ListaR, Lista_D *LD);
void GravarTudoEMCSV(Lista_Chaves_L * ListaL, Lista_Chaves_P * ListaP, ListaRequisicoes * ListaR, Lista_D *LD);
void CalcularTotaldeMemoriaOcupada(ListaRequisicoes *LR,Lista_Chaves_P *LP,Lista_Chaves_L * LL,Lista_D * LD);


/*
BIBLIOTECA *CriarBiblioteca(char *_nome, char *_logs);
void ShowBiblioteca(BIBLIOTECA *B);
void DestruirBiblioteca(BIBLIOTECA *B);
int LoadFicheiroBiblioteca(BIBLIOTECA *B);
int AddLivroBiblioteca(BIBLIOTECA *B, LIVRO *L);
int RemoverLivroBiblioteca(BIBLIOTECA *B, int isbn);
LIVRO *LivroMaisRequisitadoBiblioteca(BIBLIOTECA *B);
char *ApelidoMaisComum(BIBLIOTECA *B);
char *AreaMaisComum(BIBLIOTECA *B);
int AddRequisitante(BIBLIOTECA *B, PESSOA *X);
PESSOA *PesquisarRequisitante(BIBLIOTECA *B, int cod);
 */
#endif // BIBLIOTECA_H_INCLUDED
