#include <stdbool.h>
#include "Requisicao.h"


REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L)
{
    REQUISICAO *Req = (REQUISICAO *)malloc(sizeof(REQUISICAO));
    Req->ID = _id;
    Req->Ptr_Req = P;
    Req->Ptr_Livro = L;
    return Req;
}
void MostrarRequisicao(REQUISICAO *R)
{
    printf("REQ ID = %d\n", R->ID);
    MostrarPessoa(R->Ptr_Req);
    MostrarLivro(R->Ptr_Livro);
}
void DestruirRequisicao(REQUISICAO *R)
{
    //free (R->Ptr_Livro); //OH Pá se tirares o comentario vais ter problemas!!!!
    //free (R->Ptr_Req); //OH Pá se tirares o comentario vais ter problemas!!!!
    free (R);
}



REQUISICAO* PesquisarRequisitantePorNome(char* nome, REQUISICAO** listaRequisicoes, int tamanhoLista) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(listaRequisicoes[i]->Ptr_Req->NOME, nome) == 0) {
            return listaRequisicoes[i];
        }
    }
    return NULL; //se nao encontrar nng com o nome especifico vai retornar NULL
}


//Funcao para ver todas as requisiçoes de algum requisitante
void ListarRequisicoesPorRequisitante(PESSOA* requisitante, REQUISICAO** listaRequisicoes, int tamanhoLista) {
    printf("Requisicões do requisitante %s:\n", requisitante->NOME);
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaRequisicoes[i]->Ptr_Req == requisitante) {
            MostrarRequisicao(listaRequisicoes[i]);
        }
    }
}

//Funcão para ver se a pessoa tem alguma requisiçao ou nao
bool PessoaTemRequisicao(PESSOA* pessoa, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    for (int i = 0; i < tamanhoListaRequisicoes; i++) {
        if (listaRequisicoes[i]->Ptr_Req == pessoa) {
            return true; // se essa pessoa tiver alguma requisição retorna true
        }
    }
    return false; // senao retorna false
}


// Listar pessoas SEM requisição
void ListarPessoasSemRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    printf("Pessoas sem nenhuma requisicao:\n");

    for (int i = 0; i < tamanhoListaPessoas; i++) {
        if (!PessoaTemRequisicao(listaPessoas[i], listaRequisicoes, tamanhoListaRequisicoes)) {
            MostrarPessoa(listaPessoas[i]);
        }
    }
}

//Listar pessoas COM requisições
void ListarPessoasComRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    printf("Pessoas com alguma requisicao:\n");

    for (int i = 0; i < tamanhoListaPessoas; i++) {
        if (PessoaTemRequisicao(listaPessoas[i], listaRequisicoes, tamanhoListaRequisicoes)) {
            MostrarPessoa(listaPessoas[i]);
        }
    }
}


//  Determinar a idade máxima de todos os requisitantes;
