#include "Biblioteca.h"
#include <stdio.h>
#include "Livro.h"

void escreverLivroNoFicheiro(FILE *ficheiro, LIVRO *livro) {
    ficheiro = fopen("livros.txt", "a");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    // Escrever no ficheiro na mesma linha separado por ;
    fprintf(ficheiro, "%s;%s;%s;%d;%s;%d\n", livro->ISBN, livro->NOME, livro->AREA, livro->anoPublicacao, livro->Autor, livro->Disponivel);
}