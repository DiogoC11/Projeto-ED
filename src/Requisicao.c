#include <stdbool.h>
#include <time.h>
#include "Requisicao.h"


REQUISICAO *CriarRequisicao(int _id, PESSOA *P, LIVRO *L)
{
    REQUISICAO *Req = (REQUISICAO *)malloc(sizeof(REQUISICAO));
    Req->ID = _id;
    Req->Ptr_Req = P;
    Req->Ptr_Livro = L;
    return Req;
}
void MostrarRequisicao(REQUISICAO *R)
{
    printf("REQ ID = %d\n", R->ID);
    MostrarPessoa(R->Ptr_Req);
    MostrarLivro(R->Ptr_Livro);
}
void DestruirRequisicao(REQUISICAO *R)
{
    //free (R->Ptr_Livro); //OH Pá se tirares o comentario vais ter problemas!!!!
    //free (R->Ptr_Req); //OH Pá se tirares o comentario vais ter problemas!!!!
    free (R);
}



REQUISICAO* PesquisarRequisitantePorNome(char* nome, REQUISICAO** listaRequisicoes, int tamanhoLista) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(listaRequisicoes[i]->Ptr_Req->NOME, nome) == 0) {
            return listaRequisicoes[i];
        }
    }
    return NULL; //se nao encontrar nng com o nome especifico vai retornar NULL
}


//Funcao para ver todas as requisiçoes de algum requisitante
void ListarRequisicoesPorRequisitante(PESSOA* requisitante, REQUISICAO** listaRequisicoes, int tamanhoLista) {
    printf("Requisicões do requisitante %s:\n", requisitante->NOME);
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaRequisicoes[i]->Ptr_Req == requisitante) {
            MostrarRequisicao(listaRequisicoes[i]);
        }
    }
}

//Funcão para ver se a pessoa tem alguma requisiçao ou nao
bool PessoaTemRequisicao(PESSOA* pessoa, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    for (int i = 0; i < tamanhoListaRequisicoes; i++) {
        if (listaRequisicoes[i]->Ptr_Req == pessoa) {
            return true; // se essa pessoa tiver alguma requisição retorna true
        }
    }
    return false; // senao retorna false
}


// Listar pessoas SEM requisição
void ListarPessoasSemRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    printf("Pessoas sem nenhuma requisicao:\n");

    for (int i = 0; i < tamanhoListaPessoas; i++) {
        if (!PessoaTemRequisicao(listaPessoas[i], listaRequisicoes, tamanhoListaRequisicoes)) {
            MostrarPessoa(listaPessoas[i]);
        }
    }
}

//Listar pessoas COM requisições
void ListarPessoasComRequisicao(PESSOA** listaPessoas, int tamanhoListaPessoas, REQUISICAO** listaRequisicoes, int tamanhoListaRequisicoes) {
    printf("Pessoas com alguma requisicao:\n");

    for (int i = 0; i < tamanhoListaPessoas; i++) {
        if (PessoaTemRequisicao(listaPessoas[i], listaRequisicoes, tamanhoListaRequisicoes)) {
            MostrarPessoa(listaPessoas[i]);
        }
    }
}


//  Determinar a idade máxima de todos os requisitantes;
int CalcularIdadeMaxima(PESSOA** listaPessoas, int tamanhoListaPessoas) {
    time_t t = time(NULL); // retorna o tempo atual
    struct tm today = *localtime(&t); // isto converte o tempo atual numa estrutura tm que representa a data e hora do local atual
    int idadeMaxima = 0;

    for (int i = 0; i < tamanhoListaPessoas; i++) {
        DATANASC *dataNascimento = listaPessoas[i]->dataNascimento; // ver data de nasc da pessoa atual
        int anos = today.tm_year + 1900 - dataNascimento->ano; // calcular idade

        // ver se a pessoa ja fez anos nesse ano
        if (today.tm_mon + 1 < dataNascimento->mes || (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
            anos--; // se o mes de nasc for depois do mes atual / o mesmo mes mas o dia de nasc depois entao ainda tem -1 ano
        }
        if (anos > idadeMaxima) {
            idadeMaxima = anos;
        }
    }
    return idadeMaxima;
}


//idade media de todos os requisitantes
float CalcularIdadeMedia(PESSOA** listaPessoas, int tamanhoListaPessoas) {
    int totalIdades = 0;
    time_t t = time(NULL); // obter tempo atual
    struct tm today = *localtime(&t); // isto converte o tempo atual numa estrutura tm que representa a data e hora do local atual

    for (int i = 0; i < tamanhoListaPessoas; i++) {
        DATANASC *dataNascimento = listaPessoas[i]->dataNascimento; // ver data de nasc da pessoa atual

        int anos = today.tm_year + 1900 - dataNascimento->ano; // calcular idade

        // ver se a pessoa ja fez anos nesse ano
        if (today.tm_mon + 1 < dataNascimento->mes || (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
            anos--; // se o mes de nasc for depois do mes atual / o mesmo mes mas o dia de nasc depois entao ainda tem -1 ano
        }

        totalIdades += anos;
    }

    // calcular a media
    float idadeMedia = (float)totalIdades / tamanhoListaPessoas;
    return idadeMedia;
}

// idade com mais requisitantes
int IdadeComMaisRequisitantes(PESSOA** listaPessoas, int tamanhoListaPessoas) {
    int contadorIdades[100] = {0}; // array para contar pessoas por cada idade (até 100 anos de idade)

    // contar nr de pessoas de cada idade
    for (int i = 0; i < tamanhoListaPessoas; i++) {
        DATANASC *dataNascimento = listaPessoas[i]->dataNascimento; // ver data de nasc da pessoa atual
        time_t t = time(NULL); // obter tempo atual
        struct tm today = *localtime(&t); // isto converte o tempo atual numa estrutura tm que representa a data e hora do local atual

        int idade = today.tm_year + 1900 - dataNascimento->ano; // calcular idade

        // ver se a pessoa ja fez anos nesse ano
        if (today.tm_mon + 1 < dataNascimento->mes || (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
            idade--; // se o mes de nasc for depois do mes atual / o mesmo mes mas o dia de nasc depois entao ainda tem -1 ano
        }

        // adicionar pessoa de x idade
        contadorIdades[idade]++;
    }

    int idadeComMaisRequisitantes = 0; // idade com mais requisitantes.
    int maxContador = 0; // número máximo de pessoas de uma idade específica.

    // encontrar a idade com mais requisitantes.
    for (int i = 0; i < 100; i++) {
        // se a idade I for > do que o max atual, ent o max vai passar a ser a idade I
        // logo a idade com mais requisitantes tambem vai ser a idade I
        if (contadorIdades[i] > maxContador) {
            maxContador = contadorIdades[i];
            idadeComMaisRequisitantes = i;
        }
    }

    return idadeComMaisRequisitantes;
}

// numero de pessoas cuja a idade superior a x
int NumeroPessoasIdadeSuperiorX(PESSOA** listaPessoas, int tamanhoListaPessoas, int x) {
    int numeroPessoas = 0;

    time_t t = time(NULL); // obter tempo atual
    struct tm today = *localtime(&t); // isto converte o tempo atual numa estrutura tm que representa a data e hora do local atual

    // contar pessoas com idade superior a x.
    for (int i = 0; i < tamanhoListaPessoas; i++) {
        DATANASC *dataNascimento = listaPessoas[i]->dataNascimento; // ver data de nasc da pessoa atual

        int idade = today.tm_year + 1900 - dataNascimento->ano; // calcular idade

        // ver se a pessoa ja fez anos nesse ano
        if (today.tm_mon + 1 < dataNascimento->mes || (today.tm_mon + 1 == dataNascimento->mes && today.tm_mday < dataNascimento->dia)) {
            idade--; // se o mes de nasc for depois do mes atual / o mesmo mes mas o dia de nasc depois entao ainda tem -1 ano
        }

        // ver se idade da pessoa é maior que x
        if (idade > x) {
            numeroPessoas++; // se for entao adicionar mais uma pessoa
        }
    }

    return numeroPessoas;
}
