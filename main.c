
#include <stdio.h>
#include <stdlib.h>
#include "src/Biblioteca.h"

extern int LerInteiro(char *txt);

// Prot�tipos das fun��es
void menuLivro(ListaLivro *listaLivros);
void menuPessoa(ListaPessoa *listaPessoa);
void menuGeral(ListaLivro *listaLivros, ListaPessoa *listaPessoa);

int main() {
    printf("Projeto-Biblioteca-Versao-Base!\n");
    ListaLivro *listaLivros = criarListaL();
    ListaPessoa *listaPessoa = criarListaP();
    menuGeral(listaLivros, listaPessoa);
    printf("\nA sair da biblioteca...");

    // Liberar mem�ria alocada para a lista de livros
    ElementoL *e = listaLivros->Inicio;
    while (e != NULL) {
        ElementoL *prox = e->proximo;
        DestruirLivro(e->livro);
        free(e);
        e = prox;
    }
    free(listaLivros);

    return EXIT_SUCCESS; // ou EXIT_FAILURE
}

// Menu de opera��es de livros
void menuLivro(ListaLivro *listaLivros) {
    int opLivro;
    do {
        printf("\n--- Menu de Operacoes de Livros ---\n");
        printf("1- Adicionar Livro\n");
        printf("2- Listar Livros\n");
        printf("3- Pesquisar Livro por ISBN\n");
        printf("4- Encontrar Livro Mais Recente\n");
        printf("5- Destruir Livro\n");
        printf("0- Voltar\n");
        opLivro = LerInteiro("Qual a opcao? ");

        switch (opLivro) {
            case 1: {
                // Adicionar Livro
                LIVRO *novoLivro = PedirDadosLivro((Lista_Chaves_L *) listaLivros);
                MostrarLivro(novoLivro);
                ElementoL *novoElemento = criar_elementoL(novoLivro);
                AdicionarLivro((ElementoL *) listaLivros, (Lista_Chaves_L *) novoElemento);
                break;
            }
            case 2: {
                // Listar Livros
                ListarLivros((Lista_Chaves_L *) listaLivros);
                break;
                break;
            }
            case 3: {
                // Pesquisar Livro por ISBN
                char ISBN[50];
                printf("Digite o ISBN do livro a pesquisar: ");
                scanf("%49s", ISBN);
                LIVRO *livroEncontrado = PesquisarLivroPorISBN((Lista_Chaves_L *) listaLivros, ISBN);
                if (livroEncontrado != NULL) {
                    MostrarLivro(livroEncontrado);
                } else {
                    printf("Livro com ISBN %s nao encontrado.\n", ISBN);
                }
                break;
            }
            case 4: {
                // Encontrar Livro Mais Recente
                LIVRO *livroMaisRecente = LivroMaisRecente((Lista_Chaves_L *) listaLivros);
                if (livroMaisRecente != NULL) {
                    printf("Livro mais recente:\n");
                    MostrarLivro(livroMaisRecente);
                } else {
                    printf("Nenhum livro disponivel.\n");
                }
                break;
            }
            case 5: {
                //Destruir Livro
                char ISBN[50];
                printf("Digite o ISBN do livro a destruir: ");
                scanf("%49s", ISBN);
                LIVRO *livroDestruir = PesquisarLivroPorISBN((Lista_Chaves_L *) listaLivros, ISBN);
                if (livroDestruir != NULL) {
                    livroDestruir->Disponivel = 1;
                    printf("O livro de ISBN %s nao est� mais disponivel.",ISBN);
                } else {
                    printf("Nenhum livro dispon�vel.\n");
                }
                break;
            }
            case 0:
                printf("Voltando para o menu geral...\n");
                break;
            default:
                printf("Opcao nao implementada\n");
                break;
        }
    } while (opLivro != 0);
}

// Menu de opera��es de pessoas
void menuPessoa(ListaPessoa *listaPessoa) {
    int opPessoa;
    do {
        printf("\n--- Menu de Operacoes de Pessoa ---\n");
        printf("1- Adicionar Pessoa\n");
        printf("2- Pesquisar Pessoa por Nome\n");
        printf("3- Listar Pessoas\n");
        printf("0- Voltar\n");
        opPessoa = LerInteiro("Qual a opcao? ");

        switch (opPessoa) {
            case 1: {
                //Adicionar Pessoa
                PESSOA *novaPessoa = PedirDadosPessoa();
                MostrarPessoa(novaPessoa);
                ElementoP *novoElemento = criar_elementoP(novaPessoa);
                AdicionarPessoa((Lista_Chaves_P *) listaPessoa, novoElemento);
                break;
            }
            case 2: {
                //Pesquisar pessoa pelo nome
                char nome[50];
                printf("Digite o nome da Pessoa a pesquisar: ");
                scanf("%49s", nome);
                PESSOA *PessoaEncontrada = PesquisarPesssoaPorNome((Lista_Chaves_P *) listaPessoa, nome);
                if (PessoaEncontrada != NULL) {
                    MostrarPessoa(PessoaEncontrada);
                } else {
                    printf("Pessoa com Nome %s nao encontrado.\n", nome);
                }
                break;
            }
            case 3: {
                opPessoa = 0;
                printf("\nComo deseja organizar a lista: \n");
                printf("1- Primeiro Nome\n");
                printf("2- Ultimo Nome\n");
                printf("3- ID Freguesia\n");
                printf("0- Voltar\n");
                opPessoa = LerInteiro("Qual a opcao? ");
                do{
                    switch (opPessoa) {
                        case 1: {
                            OrganizarPorNome(listaPessoa,opPessoa);
                            break;
                        }
                        case 2:{
                            OrganizarPorNome(listaPessoa,opPessoa);
                            break;
                        }
                        case 3:{
                            //organizar por id freguesia
                            break;
                        }
                        case 0: {
                            printf("Voltando para o menu Pessoas...\n");
                            break;
                        }
                        default: {
                            printf("Opcao nao implementada\n");
                            break;
                        }
                    }
                }while(opPessoa != 0);
                break;
            }
            case 0:
                printf("Voltando para o menu geral...\n");
                break;
            default:
                printf("Opcao nao implementada\n");
                break;
        }
    } while (opPessoa != 0);
}

// Menu geral
void menuGeral(ListaLivro *listaLivros, ListaPessoa *listaPessoa) {
    int opGeral;
    do {
        printf("\n--- Menu Geral ---\n");
        printf("1- Operacoes de Livro\n");
        printf("2- Operacoes de Pessoas\n");
        printf("0- Sair\n");
        opGeral = LerInteiro("Qual a opcao? ");

        switch (opGeral) {
            case 1: {
                // Menu de Opera��es de Livro
                menuLivro(listaLivros);
                break;
            }
            case 2: {
                // Menu de Opera��es de Pessoa
                menuPessoa(listaPessoa);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao inv�lida. Tente novamente.\n");
                break;
        }
    } while (opGeral != 0);
}
