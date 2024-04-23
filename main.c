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

    DestruirHashing(Has);
}*/
int Menu()
{
    printf("1- Adicionar Livro\n");
    printf("2- Listar Livros\n");
    printf("3- Pesquisar Livro por ISBN\n");
    printf("4- Encontrar Livro Mais Recente\n");
    printf("5- Destruir Livro\n");
    printf("0- Sair\n");
    int op;
    op = LerInteiro("Qual a opcao? ");
    return op;
}

int main()
{

    printf("Projecto-Biblioteca-Versao-Base!\n");
    //Exemplo_Hashing();
    ListaLivro *listaLivros = criarLista(); // Criar a lista de livros
    int OP;
    do
    {
        OP = Menu();
        switch(OP)
        {
            case 1: {
                LIVRO *novoLivro = PedirDadosLivro();
                Elemento *novoElemento = criar_elemento(novoLivro);
                MostrarLivro(novoLivro);
                AdicionarLivro(listaLivros,novoElemento);
            }
                break;
            case 2: {
                ListarLivros(listaLivros);
                break;
            }
            case 3: {
                char ISBN [20];
                printf("Digite o ISBN do livro a pesquisar: ");
                scanf("%19s", ISBN);
                LIVRO *livroEncontrado = PesquisarLivroPorISBN((LIVRO *) listaLivros->Inicio, listaLivros->num_Livros, ISBN);
                if (livroEncontrado != NULL) {
                    MostrarLivro(livroEncontrado);
                } else {
                    printf("Livro com ISBN %s nao encontrado.\n", ISBN);
                }
                break;
            }
            case 4: {
                LIVRO *livroMaisRecente = LivroMaisRecente(listaLivros);
                if (livroMaisRecente != NULL) {
                    printf("Livro mais recente:\n");
                    MostrarLivro(livroMaisRecente);
                } else {
                    printf("Nenhum livro disponível.\n");
                }
                break;
            }
            case 5:{

            }
            default:
                printf("Opção não implementada\n");
                break;
        }

    } while (OP != 0);
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
