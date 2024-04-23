#include <stdio.h>
#include <stdlib.h>

#include "src/Lista.h"
#include "src/Hashing.h"
#include "src/Biblioteca.h"



extern int LerInteiro(char *txt);
//-----------------------------------------
/*void Exemplo_Hashing()
{
    HASHING *Has = CriarHashing();
    PESSOA *X = CriarPessoa(1234, "Jose", "CAT-A");
    AddHashing(Has, X);
    X = CriarPessoa(567, "Pedro", "CAT-A");
    AddHashing(Has, X);
    X = CriarPessoa(456, "Luis", "CAT-A");
    AddHashing(Has, X);
    X = CriarPessoa(56, "Miguel", "CAT-B");
    AddHashing(Has, X);
    X = CriarPessoa(5690, "James Bond", "CAT-Z");
    AddHashing(Has, X);
    ShowHashing(Has);

LIVRO *PedirDadosLivro();
*/
int Menu() {
    printf("\n1- Adicionar Livro\n");
    printf("2- Listar Livros\n");
    printf("3- Pesquisar Livro por ISBN\n");
    printf("4- Encontrar Livro Mais Recente\n");
    printf("5- Destruir Livro\n");
    printf("0- Voltar\n");
    int op;
    op = LerInteiro("Qual a opção? ");
    return op;
}

int MenuGeral() {
    printf("\n--- Menu Geral ---\n");
    printf("1- Operacoes de Livro\n");
    printf("0- Sair\n");
    int op;
    op = LerInteiro("Qual a opcao? ");
    return op;
}

int main() {
    printf("Projeto-Biblioteca-Versao-Base!\n");
    ListaLivro *listaLivros = criarLista();
    int OP;
    do {
        OP = MenuGeral();
        switch(OP) {
            case 1: {
                // Menu de Operações de Livro
                int opLivro;
                do {
                    opLivro = Menu();
                    switch(opLivro) {
                        case 1: {
                            // Adicionar Livro
                            LIVRO *novoLivro = PedirDadosLivro();
                            Elemento *novoElemento = criar_elemento(novoLivro);
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
                                printf("Livro com ISBN %s não encontrado.\n", ISBN);
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
                                printf("Nenhum livro disponível.\n");
                            }
                            break;
                        }
                        case 5: {
                            // Destruir Livro
                            // Implemente conforme necessário
                            break;
                        }
                        case 0:
                            printf("Voltando para o menu geral...\n");
                            break;
                        default:
                            printf("Opcao não implementada\n");
                            break;
                    }
                } while (opLivro != 0);
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
    Elemento *e = listaLivros->Inicio;
    while (e != NULL) {
        Elemento *prox = e->proximo;
        DestruirLivro(e->livro);
        free(e);
        e = prox;
    }
    free(listaLivros);

    return EXIT_SUCCESS; // ou EXIT_FAILURE
}
