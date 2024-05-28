#include <stdbool.h>
#include <time.h>
#include "Requisicao.h"
#include "Pessoa.h"


ListaRequisicoes *criarListaR(){
    ListaRequisicoes *L = (ListaRequisicoes *)malloc(sizeof(ListaRequisicoes));
    if(!L) return NULL;
    L->num_Requisicoes = 0;
    L->Inicio = NULL;
    return L;
}

ElementoR *criarElementoR(REQUISICAO *R){
    ElementoR *e = (ElementoR *)malloc(sizeof(ElementoR));
    if(!e) return NULL;
    e->requisicao = R;
    e->proximo = NULL;
    return e;
}
void MostrarRequisicao(REQUISICAO *R)
{
    printf("REQ ID = %d\n", R->ID);
    //MostrarPessoa(R->Pessoa);
    //MostrarLivro(R->Livro);
}
void DestruirRequisicao(REQUISICAO *R)
{
    //free (R->Ptr_Livro); //OH Pá se tirares o comentario vais ter problemas!!!!
    //free (R->Ptr_Req); //OH Pá se tirares o comentario vais ter problemas!!!!
    free (R);
}


//Funcão para ver se a pessoa tem alguma requisiçao ou nao
bool PessoaTemRequisicao(PESSOA* pessoa, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    for (int i = 0; i < tamanhoListaRequisicoes; i++) {
       /* if (listaRequisicoes[i]->Pessoa == pessoa) {
            return true; // se essa pessoa tiver alguma requisição retorna true
        }*/
    }
    return false; // senao retorna false
}

// Função para devolver um livro solicitado
int DevolverLivro(Lista_Chaves_L *bookList, ListaRequisicoes *reqList, char *ISBN) {
    if (!bookList || !reqList || !ISBN) {
        printf("Parâmetros inválidos.\n");
        return 0;
    }

    // Encontrar o livro na lista de livros e marcar como disponível
    NO_CHAVE_L *categoriaLivro = bookList->Inicio;
    while (categoriaLivro != NULL) {
        ElementoL *elementoLivro = categoriaLivro->DADOS->Inicio;
        while (elementoLivro != NULL) {
            LIVRO *livro = elementoLivro->livro;
            if (strcmp(livro->ISBN, ISBN) == 0) {
                livro->Disponivel = 1;

                // Encontrar e remover a requisição correspondente na lista de requisições
                ElementoR *proximo = NULL;
                ElementoR *atualReq = reqList->Inicio;
                while (atualReq != NULL) {
                    if (strcmp(atualReq->requisicao->Livro->ISBN, ISBN) == 0) {
                        if (proximo == NULL) {
                            reqList->Inicio = atualReq->proximo;
                        } else {
                            proximo->proximo = atualReq->proximo;
                        }

                        // Liberar a memória associada à requisição
                        free(atualReq->requisicao->Data_Requisicao);
                        free(atualReq->requisicao);
                        free(atualReq);

                        reqList->num_Requisicoes--;

                        printf("O livro com ISBN %s foi devolvido e a requisição removida.\n", ISBN);
                        return 1;
                    }
                    proximo = atualReq;
                    atualReq = atualReq->proximo;
                }

                printf("Requisição com o livro de ISBN %s não encontrada.\n", ISBN);
                return 0;
            }
            elementoLivro = elementoLivro->proximo;
        }
        categoriaLivro = categoriaLivro->Prox;
    }

    printf("Livro com ISBN %s não encontrado.\n", ISBN);
    return 0;
}

// Função para listar livros solicitados
void ListarLivrosRequisitados(ListaRequisicoes *listaRequisicoes) {
    if (!listaRequisicoes || listaRequisicoes->num_Requisicoes == 0) {
        printf("Não há requisições.\n");
        return;
    }
    ElementoR *atual = listaRequisicoes->Inicio;
    printf("\nLivros Requisitados: \n");
    while (atual != NULL) {
        MostrarLivro(atual->requisicao->Livro);
        atual = atual->proximo;
    }
}

// Função procurar no_chave_l por isbn
NO_CHAVE_L *searchNO_CHAVE_L(Lista_Chaves_L *L, char *isbn) {
    NO_CHAVE_L *current = L->Inicio;
    while (current != NULL) {
        ElementoL *bookElement = current->DADOS->Inicio;
        while (bookElement != NULL) {
            LIVRO *book = bookElement->livro;
            if (strcmp(book->ISBN, isbn) == 0) {
                return current;
            }
            bookElement = bookElement->proximo;
        }
        current = current->Prox;
    }
    return NULL;
}

REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L, Lista_Chaves_L *C){
    REQUISICAO *R = (REQUISICAO *)malloc(sizeof(REQUISICAO));
    if(!R) return NULL;
    R->ID = _id;
    //R->Pessoa = (ptPESSOA *) P;
    //R->Livro = L;
    L->quant_requisicaoL += 1;
    NO_CHAVE_L *myBook = searchNO_CHAVE_L(C, L->ISBN);
    myBook->quant_requisicaoN += 1;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    R->Data_Requisicao = (data *)malloc(sizeof(data));
    R->Data_Requisicao->dia = tm.tm_mday;
    R->Data_Requisicao->mes = tm.tm_mon + 1;
    R->Data_Requisicao->ano = tm.tm_year + 1900;

    return R;
}

void MostrarRequisicoesPorNIF(ListaRequisicoes *listaRequisicoes, Lista_Chaves_P *listaChavesPessoa, char *NIF) {
    if (listaRequisicoes == NULL || listaChavesPessoa == NULL || NIF == NULL) {
        printf("Listas ou NIF inválido(s).\n");
        return;
    }

    PESSOA *pessoa = NULL;
    NO_CHAVE_P *chavePessoa = listaChavesPessoa->Inicio;
    while (chavePessoa != NULL) {
        ElementoP *elementoPessoa = chavePessoa->DADOS->Inicio;
        while(elementoPessoa != NULL){
            if (strcmp(elementoPessoa->pessoa->NIF, NIF) == 0) {
                pessoa = elementoPessoa->pessoa;
                break;
            }
            elementoPessoa = elementoPessoa->proximo;
        }
        chavePessoa = chavePessoa->Prox;
    }
    if (pessoa == NULL) {
        printf("Pessoa com NIF %s não encontrada.\n", NIF);
        return;
    }

    printf("Requisições de %s (NIF: %s):\n", pessoa->NOME, NIF);
    ElementoR *atual = listaRequisicoes->Inicio;
    int a = 1;
    while (atual != NULL) {
        if (strcmp(atual->requisicao->Pessoa->NIF, NIF) == 0) {
            printf("Requisição %d:\n",a);
            printf("Livro: %s\n", atual->requisicao->Livro->NOME);
            printf("Data de Requisição: %d/%d/%d\n", atual->requisicao->Data_Requisicao->dia, atual->requisicao->Data_Requisicao->mes, atual->requisicao->Data_Requisicao->ano);
        }
        a++;
        atual = atual->proximo;
    }
}