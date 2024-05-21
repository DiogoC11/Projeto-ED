
#include <stdio.h>
#include <stdlib.h>
#include "src/Biblioteca.h"

extern int LerInteiro(char *txt);

// Protótipos das funções
void menuLivro(Lista_Chaves_L *listaChavesLivro);
void menuPessoa(Lista_Chaves_P *listaChavesPessoa);
void menuGeral(Lista_Chaves_L *listaChavesLivro, Lista_Chaves_P *listaChavesPessoa);

int main() {
    printf("Projeto-Biblioteca-Versao-Base!\n");
    Lista_Chaves_L *listaChavesLivro = CriarListaChaves();
    Lista_Chaves_P *listaChavesPessoa = criarListaChave();
    menuGeral(listaChavesLivro, listaChavesPessoa);
    printf("\nA sair da biblioteca...");
/*
    // Liberar memória alocada para a lista de livros
    ElementoL *e = listaLivros->Inicio;
    while (e != NULL) {
        ElementoL *prox = e->proximo;
        DestruirLivro(e->livro);
        free(e);
        e = prox;
    }
    free(listaLivros);
*/
    return EXIT_SUCCESS; // ou EXIT_FAILURE
}

// Menu de operações de livros
void menuLivro(Lista_Chaves_L *listaChavesLivro){
    int opLivro,confirm;
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
                LIVRO *novoLivro = PedirDadosLivro(listaChavesLivro);
                MostrarLivro(novoLivro);
                confirm = LerInteiro("\nDeseja adicionar o livro? (1-Sim, 0-Nao) ");
                if(confirm == 1) {
                    ElementoL *novoElemento = criar_elementoL(novoLivro);
                    AdicionarLivro(novoElemento, listaChavesLivro);
                }else{
                    printf("Livro nao adicionado.\n");
                    free(novoLivro);
                }
                break;
            }
            case 2: {
                // Listar Livros
                ListarLivros( listaChavesLivro);
                break;
                break;
            }
            case 3: {
                // Pesquisar Livro por ISBN
                int ISBN;
                printf("Digite o ISBN do livro a pesquisar: ");
                scanf("%d", ISBN);
                LIVRO *livroEncontrado = PesquisarLivroPorISBN( listaChavesLivro, ISBN);
                if (livroEncontrado != NULL) {
                    MostrarLivro(livroEncontrado);
                } else {
                    printf("Livro com ISBN %s nao encontrado.\n", ISBN);
                }
                break;
            }
            case 4: {
                // Encontrar Livro Mais Recente
                LIVRO *livroMaisRecente = LivroMaisRecente(listaChavesLivro);
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
                int ISBN;
                printf("Digite o ISBN do livro a destruir: ");
                scanf("%d", ISBN);
                LIVRO *livroDestruir = PesquisarLivroPorISBN(listaChavesLivro, ISBN);
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
}

// Menu de operações de pessoas
void menuPessoa(Lista_Chaves_P *listaChavesPessoa) {
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
                ElementoP *novoElemento = criarElementoP(novaPessoa);
                AdicionarPessoa(listaChavesPessoa , novoElemento);
                break;
            }
            case 2: {
                //Pesquisar pessoa pelo nome
                char nome[50];
                printf("Digite o nome da Pessoa a pesquisar: ");
                scanf("%49s", nome);
                PESSOA *PessoaEncontrada = PesquisarPesssoaPorNome(listaChavesPessoa, nome);
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
                            OrganizarPorNome(listaChavesPessoa,opPessoa);
                            break;
                        }
                        case 2:{
                            OrganizarPorNome(listaChavesPessoa,opPessoa);
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
void menuGeral(Lista_Chaves_L *ListaChavesLivros, Lista_Chaves_P *ListaChavesPessoas) {
    int opGeral;
    do {
        printf("\n--- Menu Geral ---\n");
        printf("1- Operacoes de Livro\n");
        printf("2- Operacoes de Pessoas\n");
        printf("0- Sair\n");
        opGeral = LerInteiro("Qual a opcao? ");

        switch (opGeral) {
            case 1: {
                // Menu de Operações de Livro
                menuLivro(ListaChavesLivros);
                break;
            }
            case 2: {
                // Menu de Operações de Pessoa
                menuPessoa(ListaChavesPessoas);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao inválida. Tente novamente.\n");
                break;
        }
    } while (opGeral != 0);
}
