#include <stdio.h>
#include "src/Biblioteca.h"
#include "src/Livro.h"
int main() {
    // Crirar livro
    LIVRO *livro = CriarLivro("1234", "O livro", "Aventura", 2021, "Autor");
    // Escrever nos ficheiros
    char *ficheiro = "data/livros.txt";
    escreverLivroNoFicheiro(ficheiro, livro);
    return 0;
}