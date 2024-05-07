#include <stdio.h>
#include <stdlib.h>

#include "src/Hashing.h"
#include "src/Biblioteca.h"

extern int LerInteiro(char *txt);

int MenuLivro() {
    printf("\n--- Menu de Operacoes de Livros ---\n");
    printf("1- Adicionar Livro\n");
    printf("2- Listar Livros\n");
    printf("3- Pesquisar Livro por ISBN\n");
    printf("4- Encontrar Livro Mais Recente\n");
    printf("5- Destruir Livro\n");
    printf("0- Voltar\n");
    int op;
    op = LerInteiro("Qual a opcao? ");
    return op;
}
int MenuPessoa() {
    printf("\n--- Menu de Operacoes de Pessoa ---\n");
    printf("1- Adicionar Pessoa\n");
    printf("2- Pesquisar Pessoa por Nome\n");
    printf("3- Listar Pessoas\n");
    printf("0- Voltar\n");
    int op;
    op = LerInteiro("Qual a opcao? ");
    return op;
}

int MenuGeral() {
    printf("\n--- Menu Geral ---\n");
    printf("1- Operacoes de Livro\n");
    printf("2- Operacoes de Pessoas\n");
    printf("0- Sair\n");
    int op;
    op = LerInteiro("Qual a opcao? ");
    return op;
}

int main() {
    printf("Projeto-Biblioteca-Versao-Base!\n");
    ListaLivro *listaLivros = criarListaL();
    ListaPessoa *listaPessoa = criarListaP();
    int OP;
    do {
        OP = MenuGeral();
        switch(OP) {
            case 1: {
                // Menu de Operações de Livro
                int opLivro;
                do {
                    opLivro = MenuLivro();
                    switch(opLivro) {
                        case 1: {
                            // Adicionar Livro
                            LIVRO *novoLivro = PedirDadosLivro(listaLivros);
                            MostrarLivro(novoLivro);
                            ElementoL *novoElemento = criar_elementoL(novoLivro);
                            AdicionarLivro(listaLivros, novoElemento);
                            break;
                        }
                        case 2: {
                            // Listar Livros
                            ListarLivros(listaLivros);
                            break;
                        }
                        case 3: {
                            // Pesquisar Livro por ISBN
                            char ISBN[50];
                            printf("Digite o ISBN do livro a pesquisar: ");
                            scanf("%49s", ISBN);
                            LIVRO *livroEncontrado = PesquisarLivroPorISBN(listaLivros, ISBN);
                            if (livroEncontrado != NULL) {
                                MostrarLivro(livroEncontrado);
                            } else {
                                printf("Livro com ISBN %s nao encontrado.\n", ISBN);
                            }
                            break;
                        }
                        case 4: {
                            // Encontrar Livro Mais Recente
                            LIVRO *livroMaisRecente = LivroMaisRecente(listaLivros);
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
                            LIVRO *livroDestruir = PesquisarLivroPorISBN(listaLivros, ISBN);
                            if (livroDestruir != NULL) {
                                livroDestruir->Disponivel = 1;
                                printf("O livro de ISBN %s nao está mais disponivel.",ISBN);
                            } else {
                                printf("Nenhum livro disponível.\n");
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
                break;
            }
            case 2: {
                int opPessoa;
                do {
                    opPessoa=MenuPessoa();
                    switch (opPessoa) {
                        case 1: {
                            PESSOA *novaPessoa = PedirDadosPessoa();
                            MostrarPessoa(novaPessoa);
                            ElementoP *novoElemento = criar_elementoP(novaPessoa);
                            AdicionarPessoa(listaPessoa, novoElemento);
                            break;
                        }
                        case 2: {
                            // Outra operação com Pessoa
                            // Implemente o que deseja fazer com a pessoa aqui.
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
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao inválida. Tente novamente.\n");
        }

    } while (OP != 0);
    printf("\nA sair da biblioteca...");
    // Liberar memória alocada para a lista de livros
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

int main() {
    printf("Projeto-Biblioteca-Versao-Base!\n");
    ListaLivro *listaLivros = criarListaL();
    ListaPessoa *listaPessoa = criarListaP();
    int OP;
    do {
        OP = MenuGeral();
        switch(OP) {
            case 1: {
                // Menu de Operações de Livro
                int opLivro;
                do {
                    opLivro = MenuLivro();
                    switch(opLivro) {
                        case 1: {
                            // Adicionar Livro
                            LIVRO *novoLivro = PedirDadosLivro(listaLivros);
                            MostrarLivro(novoLivro);
                            ElementoL *novoElemento = criar_elementoL(novoLivro);
                            AdicionarLivro(listaLivros, novoElemento);
                            break;
                        }
                        case 2: {
                            // Listar Livros
                            ListarLivros(listaLivros);
                            break;
                        }
                        case 3: {
                            // Pesquisar Livro por ISBN
                            char ISBN[50];
                            printf("Digite o ISBN do livro a pesquisar: ");
                            scanf("%49s", ISBN);
                            LIVRO *livroEncontrado = PesquisarLivroPorISBN(listaLivros, ISBN);
                            if (livroEncontrado != NULL) {
                                MostrarLivro(livroEncontrado);
                            } else {
                                printf("Livro com ISBN %s nao encontrado.\n", ISBN);
                            }
                            break;
                        }
                        case 4: {
                            // Encontrar Livro Mais Recente
                            LIVRO *livroMaisRecente = LivroMaisRecente(listaLivros);
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
                            LIVRO *livroDestruir = PesquisarLivroPorISBN(listaLivros, ISBN);
                            if (livroDestruir != NULL) {
                                livroDestruir->Disponivel = 1;
                                printf("O livro de ISBN %s nao está mais disponivel.",ISBN);
                            } else {
                                printf("Nenhum livro disponível.\n");
                            }
                            break;
                        }
                        case 3:{
                            opPessoa =0;
                            printf("\nComo deseja organizar a lista: \n");
                            printf("1- Primeiro Nome\n");
                            printf("2- Ultimo Nome\n");
                            printf("3- ID Freguesia\n");
                        }
                        case 0:
                            printf("Voltando para o menu geral...\n");
                            break;
                        default:
                            printf("Opcao nao implementada\n");
                            break;
                    }
                } while (opLivro != 0);
                break;
            }
            case 2: {
                int opPessoa;
                do {
                    opPessoa=MenuPessoa();
                    switch (opPessoa) {
                        case 1: {
                            //Adicionar Pessoa
                            PESSOA *novaPessoa = PedirDadosPessoa();
                            MostrarPessoa(novaPessoa);
                            ElementoP *novoElemento = criar_elementoP(novaPessoa);
                            AdicionarPessoa(listaPessoa, novoElemento);
                            break;
                        }
                        case 2: {
                            //Pesquisar pessoa pelo nome
                            char nome[50];
                            printf("Digite o nome da Pessoa a pesquisar: ");
                            scanf("%49s", nome);
                            PESSOA *PessoaEncontrada = PesquisarPesssoaPorNome(listaPessoa, nome);
                            if (PessoaEncontrada != NULL) {
                                MostrarPessoa(PessoaEncontrada);
                            } else {
                                printf("Pessoa com Nome %s nao encontrado.\n", nome);
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
                } while (opPessoa != 0);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao inválida. Tente novamente.\n");
        }

    } while (OP != 0);
    printf("\nA sair da biblioteca...");
    // Liberar memória alocada para a lista de livros
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