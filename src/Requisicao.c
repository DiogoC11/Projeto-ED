#include <stdbool.h>
#include <time.h>
#include "Requisicao.h"
#include "Uteis.h"


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
    printf("Nome da Pessoa = %s (ID: %s)\n", R->Pessoa->NOME, R->Pessoa->ID);
    printf("Nome do Livro = %s (ISBN: %s)\n", R->Livro->NOME, R->Livro->ISBN);
    if(R->Entregue) {
        printf("Entregue = Sim\n");
    }else {
        printf("Entregue = Nao\n");
    }
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
void DevolverLivro(Lista_Chaves_L *bookList, ListaRequisicoes *ListaRequisicao, char *ISBN, char *ID) {
    if (!bookList || !ListaRequisicao || !ISBN) {
        printf("Parâmetros inválidos.\n");
        return;
    }

    // Encontrar o livro na lista de livros e marcar como disponível
    NO_CHAVE_L *categoriaLivro = bookList->Inicio;
    while (categoriaLivro != NULL) {
        ElementoL *elementoLivro = categoriaLivro->DADOS->Inicio;
        while (elementoLivro != NULL) {
            LIVRO *livro = elementoLivro->livro;
            if (strcmp(livro->ISBN, ISBN) == 0) {
                // Encontrar e remover a requisição correspondente na lista de requisições
                ElementoR *atualReq = ListaRequisicao->Inicio;
                while (atualReq != NULL) {
                    if (strcmp(atualReq->requisicao->Livro->ISBN, ISBN) == 0 && strcmp(atualReq->requisicao->Pessoa->ID,ID) == 0 ) {
                        // Liberar a memória associada à requisição
                        atualReq->requisicao->Entregue = 1;
                        livro->Requisitado = 0;
                        ListaRequisicao->num_Requisicoes--;
                        printf("O livro com ISBN %s foi devolvido e a requisição dada como entregue.\n", ISBN);
                        return;
                    }
                    atualReq = atualReq->proximo;
                }

                printf("\nErro: Requisição com o livro de ISBN %s não encontrada.\n", ISBN);
                return;
            }
            elementoLivro = elementoLivro->proximo;
        }
        categoriaLivro = categoriaLivro->Prox;
    }

    printf("Livro com ISBN %s não encontrado.\n", ISBN);
    return;
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
        if(!atual->requisicao->Entregue) {
            MostrarLivro(atual->requisicao->Livro);
        }
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

REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L){
    REQUISICAO *R = (REQUISICAO *)malloc(sizeof(REQUISICAO));
    if (R == NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA REQUISICAO\n");
        return NULL;
    }
    R->ID = _id;

    R->Pessoa = (PESSOA *)malloc(sizeof(PESSOA));
    if (R->Pessoa== NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA PESSOA\n");
        free(R->Pessoa);
        free(R);
        return NULL;
    }
    R->Pessoa = P;

    R->Livro = (LIVRO *)malloc(sizeof(LIVRO));
    if (R->Pessoa== NULL) {
        printf("\nERRO AO ALOCAR MEMORIA PARA LIVRO\n");
        free(R->Livro);
        free(R->Pessoa);
        free(R);
        return NULL;
    }
    R->Livro = L;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    R->Data_Requisicao = (data *)malloc(sizeof(data));
    R->Data_Requisicao->dia = tm.tm_mday;
    R->Data_Requisicao->mes = tm.tm_mon + 1;
    R->Data_Requisicao->ano = tm.tm_year + 1900;

    R->Entregue = 0;

    return R;
}

//TESTAR

// Função para adicionar uma requisição a uma pessoa//
REQUISICAO *AdicionarRequisicao(Lista_Chaves_P *listaChavesPessoa, Lista_Chaves_L *listaChavesLivro, ListaRequisicoes *listaRequisicoes) {
    char ID[10];
    char isbn[14];
    PESSOA *pessoa = NULL;
    LIVRO *livro = NULL;
    // Pedir NIF da pessoa
    do {
        printf("Digite o ID da pessoa: ");
        scanf("%s", ID);
        limparBuffer();
        // encontrar pessoa pelo NIF inserido
        pessoa = buscarPessoaPorID(listaChavesPessoa, ID);
        if (pessoa == NULL) {
            printf("Pessoa com ID: %s nao encontrada.\n", ID);
        }
    }while(pessoa == NULL);
    printf("Pessoa encontrada: %s \n", pessoa->NOME);

    // Pedir ISBN do livro
    do {
        printf("Digite o ISBN do livro: ");
        scanf("%s", isbn);
        // encontrar livro pelo ISBN inserido
        livro = PesquisarLivroPorISBN(listaChavesLivro, isbn);
        if (livro == NULL || !livro->Disponivel || livro->Requisitado) {
            printf("\nErro: Livro com ISBN %s nao encontrado ou indisponivel ou já foi requisitado.\n", isbn);
        }
    }while(livro == NULL);
    printf("Livro encontrado: %s\n", livro->NOME);

    return CriarRequisicao(listaRequisicoes->num_Requisicoes + 1, pessoa, livro);
}


// Função para libertar a memória alocada para a lista de requisições///
void LibertarListaRequisicoes(ListaRequisicoes *lista) {
    if (!lista) return;

    ElementoR *atual = lista->Inicio;
    while (atual != NULL) {
        ElementoR *proximo = atual->proximo;

        // libertar a memória associada à requisição
        DestruirRequisicao(atual->requisicao);

        // libertar o elemento atual
        free(atual);

        // Avançar para o próximo elemento
        atual = proximo;
    }

    // libertar a estrutura da lista
    free(lista);
}


void MostrarRequisicoesPorID(ListaRequisicoes *listaRequisicoes, Lista_Chaves_P *listaChavesPessoa, char *ID) {
    if (listaRequisicoes == NULL || listaChavesPessoa == NULL || ID == NULL) {
        printf("Listas ou NIF inválido(s).\n");
        return;
    }

    PESSOA *pessoa = NULL;
    NO_CHAVE_P *chavePessoa = listaChavesPessoa->Inicio;
    while (chavePessoa != NULL) {
        ElementoP *elementoPessoa = chavePessoa->DADOS->Inicio;
        while(elementoPessoa != NULL){
            if (strcmp(elementoPessoa->pessoa->ID, ID) == 0) {
                pessoa = elementoPessoa->pessoa;
                break;
            }
            elementoPessoa = elementoPessoa->proximo;
        }
        chavePessoa = chavePessoa->Prox;
    }
    if (pessoa == NULL) {
        printf("\nErro: Pessoa com ID %s não encontrada.\n", ID);
        return;
    }

    printf("\nRequisições de %s (ID: %s):\n", pessoa->NOME, pessoa->ID);
    ElementoR *atual = listaRequisicoes->Inicio;
    int a = 1;
    while (atual != NULL) {
        if (strcmp(atual->requisicao->Pessoa->ID, ID) == 0) {
            printf(" Requisição %d:\n",a);
            printf(" Livro: %s\n", atual->requisicao->Livro->NOME);
            printf(" Data de Requisição: %d/%d/%d\n", atual->requisicao->Data_Requisicao->dia, atual->requisicao->Data_Requisicao->mes, atual->requisicao->Data_Requisicao->ano);
        }
        a++;
        atual = atual->proximo;
    }
}

void InserirRequisicaoNaLista(ptListaR listaRequisicoes, ElementoR *elemento, Lista_Chaves_L *listaLivros) {
    LIVRO *livro = NULL;
    if (listaRequisicoes == NULL || elemento == NULL) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }

    if (listaRequisicoes->Inicio == NULL) {
        listaRequisicoes->Inicio = elemento;
    } else {
        ElementoR *atual = listaRequisicoes->Inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = elemento;
    }

    livro = PesquisarLivroPorISBN(listaLivros, elemento->requisicao->Livro->ISBN);
    if(livro == NULL) {
        printf("\nERROR: Livro nao encontrado\n");
        return;
    }
    livro->Requisitado = 1;
    livro->quant_requisicaoL ++;
    ProcurarNoChavePorLivro(livro, listaLivros)->quant_requisicaoN++;
    listaRequisicoes->num_Requisicoes++;
    printf("\nRequisição adicionada com sucesso!\n");
}

void LiberarRequisicao(REQUISICAO *R){
    free(R->Data_Requisicao);
    free(R->Livro);
    free(R->Pessoa);
    free(R);
}

//Listar pessoa sem requisicao
void ListarPessoasSemRequisicoes(Lista_Chaves_P *listaChavesPessoa, ListaRequisicoes *listaRequisicoes){
    int encontrou = 0;

    NO_CHAVE_P *chaveAtual = listaChavesPessoa->Inicio;
    while (chaveAtual != NULL) {
        ElementoP *elementoPAtual = chaveAtual->DADOS->Inicio;
        while (elementoPAtual != NULL) {
            ElementoR *elementoRAtual = listaRequisicoes->Inicio;
            while (elementoRAtual != NULL) {
                if (strcmp(elementoRAtual->requisicao->Pessoa->ID, elementoPAtual->pessoa->ID) == 0) {
                    encontrou = 1;
                }
                elementoRAtual = elementoRAtual->proximo;
            }
            if (!encontrou) {
                MostrarPessoa(elementoPAtual->pessoa);
            }
            elementoPAtual = elementoPAtual->proximo;
        }
        chaveAtual = chaveAtual->Prox;
    }

}

// Listar pessoa com requisição
void ListarPessoasComRequisicao(Lista_Chaves_P *listaChavesPessoa, ListaRequisicoes *listaRequisicoes) {
    int encontrou = 0;

    NO_CHAVE_P *chaveAtual = listaChavesPessoa->Inicio;
    while (chaveAtual != NULL) {
        ElementoP *elementoPAtual = chaveAtual->DADOS->Inicio;
        while(elementoPAtual != NULL) {
            ElementoR *elementoRAtual = listaRequisicoes->Inicio;
            while (elementoRAtual != NULL) {
                if (strcmp(elementoRAtual->requisicao->Pessoa->ID, elementoPAtual->pessoa->ID) == 0) {
                    encontrou = 1;
                }
                elementoRAtual = elementoRAtual->proximo;
            }
            if(encontrou) {
                MostrarPessoa(elementoPAtual->pessoa);
            }
            elementoPAtual = elementoPAtual->proximo;
        }
        chaveAtual = chaveAtual->Prox;
    }

    if (!encontrou) {
        printf("Nenhuma pessoa com requisições encontrada.\n");
    }
}