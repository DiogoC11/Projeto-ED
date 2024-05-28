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
    //free (R->Ptr_Livro); //OH P� se tirares o comentario vais ter problemas!!!!
    //free (R->Ptr_Req); //OH P� se tirares o comentario vais ter problemas!!!!
    free (R);
}


//Func�o para ver se a pessoa tem alguma requisi�ao ou nao
bool PessoaTemRequisicao(PESSOA* pessoa, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    for (int i = 0; i < tamanhoListaRequisicoes; i++) {
       /* if (listaRequisicoes[i]->Pessoa == pessoa) {
            return true; // se essa pessoa tiver alguma requisi��o retorna true
        }*/
    }
    return false; // senao retorna false
}

// Fun��o para mostrar o n�mero de pessoas do distrito X com nome/sobrenome Y
int ContarPessoas(Lista_Chaves_P *peopleList, char *districtX, char *nameY) {
    int count = 0;
    NO_CHAVE_P *current = peopleList->Inicio;
    while (current != NULL) {
        ElementoP *personElement = current->DADOS->Inicio;
        while (personElement != NULL) {
            PESSOA *person = personElement->pessoa;
            char districtID[10];
            sprintf(districtID, "%d", person->freguesia->ID_DIST);
            if (strcmp(districtID, districtX) == 0 &&
                (strcmp(person->PrimeiroNome, nameY) == 0 || strcmp(person->UltimoNome, nameY) == 0)) {
                count++;
            }
            personElement = personElement->proximo;
        }
        current = current->Prox;
    }
    return count;
}

// Fun��o para devolver um livro solicitado
int DevolverLivro(Lista_Chaves_L *bookList, ListaRequisicoes *reqList, char *ISBN) {
    if (!bookList || !reqList || !ISBN) {
        printf("Par�metros inv�lidos.\n");
        return 0;
    }

    // Encontrar o livro na lista de livros e marcar como dispon�vel
    NO_CHAVE_L *categoriaLivro = bookList->Inicio;
    while (categoriaLivro != NULL) {
        ElementoL *elementoLivro = categoriaLivro->DADOS->Inicio;
        while (elementoLivro != NULL) {
            LIVRO *livro = elementoLivro->livro;
            if (strcmp(livro->ISBN, ISBN) == 0) {
                livro->Disponivel = 1;

                // Encontrar e remover a requisi��o correspondente na lista de requisi��es
                ElementoR *proximo = NULL;
                ElementoR *atualReq = reqList->Inicio;
                while (atualReq != NULL) {
                    if (strcmp(atualReq->requisicao->Livro->ISBN, ISBN) == 0) {
                        if (proximo == NULL) {
                            reqList->Inicio = atualReq->proximo;
                        } else {
                            proximo->proximo = atualReq->proximo;
                        }

                        // Liberar a mem�ria associada � requisi��o
                        free(atualReq->requisicao->Data_Requisicao);
                        free(atualReq->requisicao);
                        free(atualReq);

                        reqList->num_Requisicoes--;

                        printf("O livro com ISBN %s foi devolvido e a requisi��o removida.\n", ISBN);
                        return 1;
                    }
                    proximo = atualReq;
                    atualReq = atualReq->proximo;
                }

                printf("Requisi��o para o livro com ISBN %s n�o encontrada.\n", ISBN);
                return 0;
            }
            elementoLivro = elementoLivro->proximo;
        }
        categoriaLivro = categoriaLivro->Prox;
    }

    printf("Livro com ISBN %s n�o encontrado.\n", ISBN);
    return 0;
}

// Fun��o para listar livros solicitados
void listaLivrosRequisitados(ListaRequisicoes *listaRequisicoes) {
    if (!listaRequisicoes || listaRequisicoes->num_Requisicoes == 0) {
        printf("N�o h� requisi��es.\n");
        return;
    }
    ElementoR *atual = listaRequisicoes->Inicio;
    printf("\nLivros Requisitados: \n");
    while (atual != NULL) {
        MostrarLivro(atual->requisicao->Livro);
        atual = atual->proximo;
    }
}

// Fun��o procurar no_chave_l por isbn
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