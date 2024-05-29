

#include <stdio.h>
#include <stdlib.h>
#include "src/Biblioteca.h"
#include "src/Uteis.h"

// Menu de operações de livros
void menuLivro(Lista_Chaves_L *listaChavesLivro){
    int opLivro,confirm;
    do {
        printf("\n--- Menu de Operacoes de Livros ---\n");
        printf("1- Adicionar Livro\n");
        printf("2- Listar Livros\n");
        printf("3- Encontrar area com mais livros\n");
        printf("4- Pesquisar Livro por ISBN\n");
        printf("5- Encontrar Livro Mais Recente\n");
        printf("6- Encontrar Livro Mais Requisitado\n");
        printf("7- Encontrar Area Mais Requisitada\n");
        printf("8- Destruir Livro\n");
        printf("0- Voltar\n");
        opLivro = LerInteiro("Qual a opcao? ");

        //ola
        switch (opLivro) {
            case 1: {
                // Adicionar Livro
                LIVRO *novoLivro = PedirDadosLivro(listaChavesLivro);
                MostrarLivro(novoLivro);
                confirm = LerInteiro("\nDeseja adicionar o livro? (1-Sim, 0-Nao) ");
                if(confirm == 1) {
                    ElementoL *novoElemento = criar_elementoL(novoLivro);
                    AdicionarLivro(novoElemento, listaChavesLivro);
                    //free(novoElemento);
                }else{
                    printf("\nLivro nao foi adicionado.\n");

                    free(novoLivro);
                }
                break;
            }
            case 2: {
                // Listar Livros
                ListarLivros( listaChavesLivro);
                break;
            }
            case 3:{
                //Encontrar area com mais livros
                NO_CHAVE_L *areaMaisLivros = AreaMaisLivros(listaChavesLivro);
                printf("\nArea com mais livros: %s (numero de livros: %d)\n",areaMaisLivros->categoria, areaMaisLivros->DADOS->num_Livros);
            }
            case 4: {
                // Pesquisar Livro por ISBN
                char ISBN[14];
                do {
                    printf("\nISBN: ");
                    scanf("%s", ISBN);
                    limparBuffer();
                    if (strlen(ISBN) != 13) {
                        printf("\nErro: O ISBN tem de ter 13 digitos.(%d)\n", strlen(ISBN));
                    }
                } while ( strlen(ISBN) != 13 );
                LIVRO *livroEncontrado = PesquisarLivroPorISBN( listaChavesLivro, ISBN);
                if (livroEncontrado != NULL) {
                    MostrarLivro(livroEncontrado);
                } else {
                    printf("\nErro: Livro com ISBN %s nao encontrado.\n", ISBN);
                }
                break;
            }
            case 5: {
                // Encontrar Livro Mais Recente
                LIVRO *livroMaisRecente = LivroMaisRecente(listaChavesLivro);
                if (livroMaisRecente != NULL) {
                    printf("\nLivro mais recente:\n");
                    MostrarLivro(livroMaisRecente);
                } else {
                    printf("\nErro: Nenhum livro disponivel.\n");
                }
                break;
            }
            case 6:{
                // Encontrar Livro Mais Requisitado
                LIVRO *livroMaisRequisitado = LivroMaisRequisitado(listaChavesLivro);
                if(livroMaisRequisitado != NULL){
                    printf("\nLivro mais requisitado:\n");
                    MostrarLivro(livroMaisRequisitado);
                }else{
                    printf("\nNao existe livros requisitados.\n");
                }

                break;
            }
            case 7:{
                // Encontrar Area Mais Requisitada
                NO_CHAVE_L *areaMaisRequisitada = AreaMaisRequisitada(listaChavesLivro);
                if(areaMaisRequisitada != NULL){
                    printf("\nArea mais requisitada: %s\n (numero de requisicoes: %d)\n", areaMaisRequisitada->categoria, areaMaisRequisitada->quant_requisicaoN);
                }else{
                    printf("\nNao existe livros requisitados\n");
                }
            }
            case 8: {
                //Destruir Livro
                char ISBN[14];
                do {
                    printf("\nInsira o ISBN do livro: ");
                    scanf("%s", ISBN);
                    limparBuffer();
                    if (strlen(ISBN) != 13) {
                        printf("\nErro: O ISBN tem de ter 13 digitos.(%d)\n", strlen(ISBN));
                    }
                } while ( strlen(ISBN) != 13);
                LIVRO *livroDestruir = PesquisarLivroPorISBN(listaChavesLivro, (char *) ISBN);
                if (livroDestruir != NULL) {
                    MostrarLivro(livroDestruir);
                    do {
                        confirm = LerInteiro("\nDeseja destruir o livro? (1-Sim, 0-Nao) ");
                        if (confirm == 1) {
                            livroDestruir->Disponivel = 1;
                            printf("O livro de ISBN %s foi destruido.", ISBN);
                        }else if (confirm == 0) {
                            printf("Livro nao foi destruido.\n");
                        }
                    }while(confirm != 0 && confirm != 1);
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

// Menu de operações de pessoas/
void menuPessoa(Lista_Chaves_P *listaChavesPessoa, Lista_D *D, Lista_C *C, Lista_F *F, ListaRequisicoes *listaRequisicoes){
    int opPessoa;
    do {
        printf("\n--- Menu de Operacoes de Pessoa ---\n");
        printf("1 - Adicionar Pessoa\n");
        printf("2 - Pesquisar Pessoa por Nome\n");
        printf("3 - Listar Pessoas\n");
        printf("4 - Determinar idade maxima de todos os requisitantes\n");
        printf("5 - Determinar idade media de todos os requisitantes\n");
        printf("6 - Determinar numero de pessoas com idade superior a X\n");
        printf("7 - Determinar idade com mais requisitantes\n");
        printf("8 - Mostrar requisicoes de um requisitante\n");
        printf("9 - Listar pessoas sem requisicoes\n");
        printf("10 - Listar pessoas com requisicoes\n");
        printf("11 - Sobrenome mais usado pelos requisitantes\n");
        printf("12 - Determinar numero de pessoas de um Distrito/Concelho pelo nome/apelido\n");
        printf("0 - Voltar\n");
        opPessoa = LerInteiro("Qual a opcao? ");

        switch (opPessoa) {
            case 1: {
                //Adicionar Pessoa
                PESSOA *novaPessoa = PedirDadosPessoa(listaChavesPessoa, D, C, F);
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
                ListaPessoa *listaPessoas;
                int opOrganizarPessoa = 0;
                do {
                    printf("\nComo deseja organizar a lista: \n");
                    printf("1- Primeiro Nome\n");
                    printf("2- Ultimo Nome\n");
                    printf("3- ID Freguesia\n");
                    printf("0- Voltar\n");
                    opOrganizarPessoa = LerInteiro("Qual a opcao? ");

                    switch (opOrganizarPessoa) {
                        case 1: {
                            ListaOrganizada(listaChavesPessoa, 1); // Ordenar por primeiro nome
                            break;
                        }
                        case 2: {
                            ListaOrganizada(listaChavesPessoa, 2); // Ordenar por último nome
                            break;
                        }
                        case 3: {
                            ListaOrganizada(listaChavesPessoa, 3); // Ordenar por ID de freguesia
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
                    for(int i = 0; i < listaPessoas->num_Pessoas; i++){
                        MostrarPessoa(listaPessoas->Inicio->pessoa);
                    }
                } while (opOrganizarPessoa != 0);
                break;
            }
            case 4: {
                int idadeMaxima = CalcularIdadeMaxima(listaChavesPessoa);
                printf("A idade maxima de todos os requisitantes e: %d anos\n", idadeMaxima);
                break;
            }
            case 5: {
                //  idade média
                float idadeMedia = CalcularIdadeMedia(listaChavesPessoa);
                printf("A idade media de todos os requisitantes e: %.2f anos\n", idadeMedia);
                break;
            }
            case 6: {
                // contar pessoas com idade superior a X
                int idadeLimite = LerInteiro("Digite a idade limite: ");
                int numPessoas = ContarPessoasComIdadeSuperiorA(listaChavesPessoa, idadeLimite);
                printf("O numero de pessoas com idade superior a %d anos e: %d\n", idadeLimite, numPessoas);
                break;

            }
            case 7: {
                //  idade com mais requisitantes
                int idadeMaisRequisitada = IdadeComMaisRequisitantes(listaChavesPessoa);
                if (idadeMaisRequisitada != -1) {
                    printf("A idade com mais requisitantes e: %d anos\n", idadeMaisRequisitada);
                } else {
                    printf("Nenhuma idade encontrada.\n");
                }
                break;
            }
            case 8:{
                char *NIF;
                do{
                    printf("\nNIF: ");
                    scanf("%s", NIF);
                    limparBuffer();
                    if (strlen(NIF) != 9) {
                        printf("\nErro: O NIF tem de ter 9 digitos.(%d)\n", strlen(NIF));
                    } else if (PesquisarPessoaPorNIF(listaChavesPessoa,NIF) == NULL) {
                        printf("\nErro: O NIF inserido nao existe.\n");
                    }
                }while(strlen(NIF) != 9 || PesquisarPessoaPorNIF(listaChavesPessoa,NIF) == NULL);
                MostrarRequisicoesPorNIF(listaRequisicoes, listaChavesPessoa, NIF);
                break;
            }
            case 9: {
                ListarPessoasSemRequisicoes(listaChavesPessoa);
                break;
            }
            case 10: {
                ListarPessoasComRequisicao(listaChavesPessoa);
                break;
            }
            case 11: {
                char* sobrenomeMaisUsado = SobrenomeMaisUsado(listaChavesPessoa);
                if (sobrenomeMaisUsado != NULL) {
                    printf("O sobrenome mais comum nas requisições e: %s\n", sobrenomeMaisUsado);
                } else {
                    printf("Nenhuma requisição encontrada.\n");
                }
                break;
            }
            case 12: {
                char *nome = "", *apelido = "", op;
                int id_dist, id_conc = 0,id;
                do{
                    ListarDistritos(D);
                    printf("\nEscolha um Distrito: ");
                    scanf("%d", &id_dist);
                    limparBuffer();
                    if(ProcurarDistritoPorID(D, id_dist) == NULL){
                        printf("\nErro: Distrito nao encontrado.\n");
                    }
                }while(ProcurarDistritoPorID(D, id_dist) == NULL);
                do{
                    MostraConcelhosDistrito(id_dist, D);
                    printf("\nEscolha um Concelho (0 - pesquisar so por Distrito): ");
                    scanf("%d", &id_conc);
                    limparBuffer();
                    if(id_conc != 0) {
                        if (ProcurarConcelhoPorID(C, id_conc, id_dist) == NULL) {
                            printf("\nErro: Concelho nao encontrado.\n");
                        }
                    }
                }while(id_conc != 0 && ProcurarConcelhoPorID(C, id_conc, id_dist) == NULL);
                //pedir nome/apelido
                do {
                    printf("Pretende procurar por nome ou apelido? (1-Nome, 2-Apelido): ");
                    scanf("%d", &op);
                    limparBuffer();
                    if(op != 1 && op != 2){
                        printf("\nErro: Opcao invalida.\n");
                    }
                }while(op != 1 && op != 2);
                if(op == 1) {
                    printf("Insira o nome: ");
                    scanf("%s", nome);
                }else{
                    printf("Insira o apelido: ");
                    scanf("%s", apelido);
                }
                ContarPessoasDeUmLocal(listaChavesPessoa, id_dist, id_conc, nome, apelido);
                break;
            }
            case 0: {
                printf("Voltando para o menu geral...\n");
                break;
            }
            default: {
                printf("Opcao nao implementada\n");
                break;
            }
        }
    } while (opPessoa != 0);
}

//Menu Requisiçoes///
void menuRequisicoes(Lista_Chaves_P *ListaPessoas, ListaRequisicoes *listaRequisicoes, Lista_Chaves_L *listaChavesLivros){
    int opRequisicao, id_dist, id_conc,id;
    char *isbn, *nome;
    do {
        printf("\n--- Menu Requisicoes ---\n");
        printf("1- Fazer Requisicao\n");
        printf("2- Devolver Livro\n");
        printf("3- Listar Livros requisitados\n");
        printf("0- Sair\n");
        opRequisicao = LerInteiro("Qual a opcao? ");

        switch (opRequisicao) {
            case 1:
                //adicionar requisicao
                //TESTE
                AdicionarRequisicao(ListaPessoas, listaChavesLivros, listaRequisicoes);
                break;
            case 2:
                do {
                    printf("\nISBN: ");
                    scanf("%s", isbn);
                    limparBuffer();
                    if (strlen(isbn) != 13) {
                        printf("\nErro: O ISBN tem de ter 13 digitos.(%d)\n", strlen(isbn));
                    } else if (PesquisarLivroPorISBN(listaChavesLivros, isbn) == NULL) {
                        printf("\nErro: O ISBN inserido nao existe.\n");
                    }
                } while ( strlen(isbn) != 13 || PesquisarLivroPorISBN(listaChavesLivros, isbn) != NULL);
                DevolverLivro(listaChavesLivros, listaRequisicoes, isbn);
                break;
            case 3:
                ListarLivrosRequisitados(listaRequisicoes);
                break;
            case 0:
                printf("A voltar...\n");
                break;
            default:
                printf("Erro: Opcao nao implementada.\n");
                break;
        }
    } while (opRequisicao != 0);
}

// Menu geral
void menuGeral(Lista_Chaves_L *ListaChavesLivros, Lista_Chaves_P *ListaChavesPessoas, ListaRequisicoes *ListaRequisicoes, Lista_D *D, Lista_C *C, Lista_F *F) {
    int opGeral;
    do {
        printf("\n--- Menu Geral ---\n");
        printf("1- Operacoes de Livro\n");
        printf("2- Operacoes de Pessoas\n");
        printf("3- Operacoes de Requisicoes\n");
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
                menuPessoa(ListaChavesPessoas, D, C, F, ListaRequisicoes);
                break;
            }
            case 3:
                menuRequisicoes(ListaChavesPessoas, ListaRequisicoes, ListaChavesLivros);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao inválida. Tente novamente.\n");
                break;
        }
    } while (opGeral != 0);
}

int main() {
    printf("Projeto-Biblioteca-Versao-Base!\n");

    // Criar listas para livros e pessoas
    Lista_Chaves_L *listaChavesLivro = CriarListaChaves();
    Lista_Chaves_P *listaChavesPessoa = criarListaChave();
    ListaRequisicoes *listaRequisicoes = criarListaR();

    Lista_F *ListaF= LerTXT();
    Lista_C *ListaC= LerTXTConc();
    Lista_D *listaD = LerTXTDist();
    //ListarConcelhosPorDistrito(listaDistritos,ListaC, 2);
    //ListarDistritosPorID(listaDistritos, 10);
    associa_concelhos_a_distritos(listaD, ListaC);
    //MostraConcelhosDistrito(5,listaD);
    associa_freguesias_a_concelhos(ListaC, ListaF);
    //MostraFreguesiasConcelho(2, ListaC, 5);
    //ListarFreguesias(ListaF);

    // Executar o menu geral
    menuGeral(listaChavesLivro, listaChavesPessoa, listaRequisicoes, listaD, ListaC, ListaF);

    printf("\nA sair da biblioteca...\n");

    // Liberar memória alocada para as listas de livros e pessoas
    //LiberarListaChaves_L(listaChavesLivro);
    LiberarListaChaves_P(listaChavesPessoa);

    //TESTE
    LibertarListaRequisicoes(listaRequisicoes);

    return EXIT_SUCCESS; // ou EXIT_FAILURE
}
