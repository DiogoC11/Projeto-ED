#include <stdio.h>
#include <stdlib.h>

#include "Lista.h"
#include "Hashing.h"
#include "Biblioteca.h"

extern int LerInteiro(char *txt);
//-----------------------------------------
void Exemplo_Hashing()
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
}
int Menu()
{
    printf("1- Load\n");
    printf("2- Show\n");
    printf("3- Nome mais Comum\n");
    printf("0-Sair\n");
    int op;
    op = LerInteiro("Qual a o opcao? ");
    return op;
}

int main()
{
    printf("Projecto-Biblioteca-Versao-Base!\n");
    //Exemplo_Hashing();
    BIBLIOTECA *Bib;
    Bib = CriarBiblioteca("Biblioteca-ESTGV", "log.txt");
    int OP;
    do
    {
        OP = Menu();
        switch(OP)
        {
            case 1: LoadFicheiroBiblioteca(Bib); break;
            case 2: ShowBiblioteca(Bib); break;
            default:
                printf("Opcao nao implementada\n"); break;
        }

    }while (OP != 0);
    DestruirBiblioteca(Bib);
    return EXIT_SUCCESS; // ou EXIT_FAILURE
}
