

#include "Pessoa.h"

/** \brief Permite Alocar e inicializar uma estrutura Pessoa
 *
 * \param _id int
 * \param _nome char*
 * \param _categoria char*
 * \return PESSOA*
 *
 */


PESSOA *CriarPessoa(int _id, char *_nome, char *_categoria)
{
    PESSOA *P = (PESSOA *)malloc(sizeof(PESSOA));
    P->NOME = (char *)malloc((strlen(_nome) + 1)*sizeof(char));
    strcpy(P->NOME, _nome);
    P->CATEGORIA = (char *)malloc((strlen(_categoria) + 1)*sizeof(char));
    strcpy(P->CATEGORIA, _categoria);
    P->ID = _id == 0 ? GerarID() : _id;
    return P;
}
void MostrarPessoa(PESSOA *P)
{
    printf("\tPESSOA: ID: %d [%s] [%s]\n", P->ID, P->NOME, P->CATEGORIA);
}
void DestruirPessoa(PESSOA *P)
{
    free (P->NOME);
    free (P->CATEGORIA);
    free (P);
}

int GerarID() {
    static int baseID = 100000000;  // Come�a com um n�mero de 9 d�gitos.
    int sum = 0, id = baseID;
    int tempID = id;

    while (tempID > 0) {
        sum += tempID % 10;
        tempID /= 10;
    }

    // Calcula o d�gito de controle necess�rio para fazer a soma um m�ltiplo de 10.
    int lastDigit = 10 - (sum % 10);
    if (lastDigit == 10) lastDigit = 0;

    id += lastDigit;  // Adiciona o d�gito de controle ao final do ID.
    baseID++;  // Incrementa a base para o pr�ximo ID.

    return id;
}
