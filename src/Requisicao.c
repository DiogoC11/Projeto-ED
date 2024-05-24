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



// Funções 24/05 || test me
// Função para mostrar o número de pessoas do distrito X com nome/sobrenome Y
int countPeopleFromDistrictWithName(Lista_Chaves_P *peopleList, char *districtX, char *nameY) {
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

// Função para devolver um livro solicitado
void returnRequestedBook(Lista_Chaves_L *bookList, char *ISBN) {
    NO_CHAVE_L *current = bookList->Inicio;
    while (current != NULL) {
        ElementoL *bookElement = current->DADOS->Inicio;
        while (bookElement != NULL) {
            LIVRO *book = bookElement->livro;
            if (strcmp(book->ISBN, ISBN) == 0) {
                book->Disponivel = 1;
                printf("O livro com ISBN %s foi devolvido.\n", ISBN);
                return;
            }
            bookElement = bookElement->proximo;
        }
        current = current->Prox;
    }
    printf("Livro com ISBN %s não encontrado.\n", ISBN);
}

// Função para listar livros solicitados
void listRequestedBooks(Lista_Chaves_L *bookList) {
    NO_CHAVE_L *current = bookList->Inicio;
    while (current != NULL) {
        ElementoL *bookElement = current->DADOS->Inicio;
        while (bookElement != NULL) {
            LIVRO *book = bookElement->livro;
            if (book->Disponivel == 0) {
                MostrarLivro(book);
            }
            bookElement = bookElement->proximo;
        }
        current = current->Prox;
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
    R->Data_Requisicao = (DATA_Req *)malloc(sizeof(DATA_Req));
    if(!R->Data_Requisicao) return NULL;
    return R;
}