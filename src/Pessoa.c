#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Pessoa.h"

PESSOA *CriarPessoa(char *_nome, int _ID, int _dia, int _mes, int _ano)
{
    PESSOA *novaPessoa = (PESSOA *)malloc(sizeof(PESSOA));
    if (novaPessoa != NULL)
    {
        novaPessoa->NOME = _nome;
        novaPessoa->ID = _ID;
        novaPessoa->dataNascimento = (DATANASC *)malloc(sizeof(DATANASC));
        novaPessoa->dataNascimento->dia = _dia;
        novaPessoa->dataNascimento->mes = _mes;
        novaPessoa->dataNascimento->ano = _ano;
    }
    return novaPessoa;
}

void MostrarPessoa(PESSOA *P)
{
    printf("\tPESSOA: ID: %d [%s] [%s]\n", P->ID, P->NOME, P->dataNascimento);
}

ptListaP criarListaPessoa() {
    ptListaP novaLista = (ptListaP)malloc(sizeof(ListaPessoa));
    if (novaLista != NULL) {
        novaLista->num_Pessoas = 0;
        novaLista->Inicio = NULL;
    }
    return novaLista;
}

ptElementoP criarElemento(PESSOA *pessoa) {
    ptElementoP novoElemento = (ptElementoP)malloc(sizeof(ElementoP));
    if (novoElemento != NULL) {
        novoElemento->pessoa = pessoa;
        novoElemento->proximo = NULL;
    }
    return novoElemento;
}

// Função para inserir uma pessoa na lista
void inserirPessoa(ptListaP lista, PESSOA *pessoa) {
    ptElementoP novoElemento = criarElemento(pessoa);
    if (novoElemento != NULL) {
        if (lista->Inicio == NULL) {
            lista->Inicio = novoElemento;
        } else {
            ptElementoP temp = lista->Inicio;
            while (temp->proximo != NULL) {
                temp = temp->proximo;
            }
            temp->proximo = novoElemento;
        }
        lista->num_Pessoas++;
    }
}

// Função para criar um novo nó de chave
NO_CHAVE *criarNoChave(char *chave) {
    NO_CHAVE *novoNoChave = (NO_CHAVE *)malloc(sizeof(NO_CHAVE));
    if (novoNoChave != NULL) {
        novoNoChave->KEY = chave;
        novoNoChave->DADOS = criarListaPessoa();
        novoNoChave->Prox = NULL;
    }
    return novoNoChave;
}

// Função para inserir uma pessoa na tabela de hashing
void inserirPessoaHash(NO_CHAVE **tabela, char *chave, PESSOA *pessoa) {
    int indice = chave[0] - 'A'; // Supondo que as chaves sejam letras maiúsculas de A a Z
    NO_CHAVE *atual = tabela[indice];
    if (atual == NULL) {
        tabela[indice] = criarNoChave(chave);
        atual = tabela[indice];
    } else {
        while (atual->Prox != NULL) {
            atual = atual->Prox;
        }
        atual->Prox = criarNoChave(chave);
        atual = atual->Prox;
    }
    inserirPessoa(atual->DADOS, pessoa);
}

// Função percorrer as pessoas a busca se o id é identifco ao parametro
PESSOA *buscarPessoaPorID(ptListaP lista, int id) {
    ptElementoP atual = lista->Inicio;
    while (atual != NULL) {
        if (atual->pessoa->ID == id) {
            return atual->pessoa;
        }
        atual = atual->proximo;
    }
    return NULL;
}

////------------- Percorrer

int verificarIDArquivo(char *idRequisitante) {
    FILE *arquivo = fopen("Requisitantes.txt", "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[100]; // Buffer para armazenar cada linha lida do arquivo

    // Lê cada linha do arquivo até encontrar o fim do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, "\t"); // Divide a linha em tokens usando o caractere de tabulação como delimitador
        if (token != NULL) {
            // O primeiro token é o ID requisitante
            if (strcmp(token, idRequisitante) == 0) {
                fclose(arquivo); // Fecha o arquivo
                return 1; // Retorna verdadeiro se o ID requisitante for encontrado
            }
        }
    }

    fclose(arquivo); // Fecha o arquivo
    return 0; // Retorna falso se o ID requisitante não for encontrado
}
