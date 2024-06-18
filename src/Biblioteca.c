

#include "Biblioteca.h"
#include <stdio.h>
#include "Livro.h"
/*
void escreverLivroNoFicheiro(FILE *ficheiro, LIVRO *livro) {
    ficheiro = fopen("livros.txt", "a");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    // Escrever no ficheiro na mesma linha separado por ;
    fprintf(ficheiro, "%s;%s;%s;%d;%s;%d\n", livro->ISBN, livro->NOME, livro->AREA, livro->anoPublicacao, livro->Autor, livro->Disponivel);
}
LIVRO *LivroMaisRequisitadoBiblioteca(BIBLIOTECA *B)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    // Aqui o teu codigo

    fclose(F_Logs);
    return NULL;
}
char *ApelidoMaisComum(BIBLIOTECA *B)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    // Aqui o teu codigo

    fclose(F_Logs);
    return NULL;
}
char *AreaMaisComum(BIBLIOTECA *B)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    // Aqui o teu codigo

    fclose(F_Logs);
    return NULL;
}
int AddRequisitante(BIBLIOTECA *B, PESSOA *X)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    // Aqui o teu codigo

    fclose(F_Logs);
    return EXIT_SUCCESS;
}
PESSOA *PesquisarRequisitante(BIBLIOTECA *B, int cod)
{
    FILE *F_Logs = fopen(B->FICHEIRO_LOGS, "a");
    time_t now = time(NULL) ;
    fprintf(F_Logs, "Entrei em %s na data %s\n", __FUNCTION__, ctime(&now));

    // Aqui o teu codigo

    fclose(F_Logs);
    return NULL;
}
 */


void GravarXML(Lista_Chaves_L * ListaL, Lista_Chaves_P * ListaP, ListaRequisicoes * ListaR, Lista_D *LD){
    char nome[100];
    printf("Insira o nome do Ficheiro XML: ");
    fgets(nome, sizeof(nome), stdin);
    if (nome[strlen(nome) - 1] == '\n') {
        nome[strlen(nome) - 1] = '\0';
    }
    char caminho[100];
    sprintf(caminho, "../XML/%s.xml", nome);
    FILE *arquivo = fopen(caminho, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de XML.\n");
        EscreverLogs("\nErro ao abrir o arquivo de XML.\n");
        return;
    }

    fprintf(arquivo, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(arquivo, "<Biblioteca>\n");

    // Write Livros
    fprintf(arquivo, "<Livros>\n");
    NO_CHAVE_L *NO_L = ListaL->Inicio;
    while ( NO_L != NULL) {
        ElementoL *L = NO_L->DADOS->Inicio;
        while (L != NULL){
            fprintf(arquivo, " <Livro>\n");
            fprintf(arquivo, "  <ISBN>%s</ISBN>\n", L->livro->ISBN);
            fprintf(arquivo, "  <Nome>%s</Nome>\n", L->livro->NOME);
            fprintf(arquivo, "  <Autor>%s</Autor>\n", L->livro->Autor);
            fprintf(arquivo, "  <Ano>%d</Ano>\n", L->livro->anoPublicacao);
            fprintf(arquivo, "  <Area>%s</Area>\n", L->livro->AREA);
            fprintf(arquivo, "  <nReq>%d</nReq>\n", L->livro->quant_requisicaoL);
            fprintf(arquivo, "  <Disponivel>%d</Disponivel>\n", L->livro->Disponivel);
            fprintf(arquivo, "  <Requisitado>%d</Requisitado>\n", L->livro->Requisitado);
            fprintf(arquivo, " </Livro>\n");
            L = L->proximo;
        }
        NO_L = NO_L->Prox;
    }
    fprintf(arquivo, "</Livros>\n");

    // Write Requisitantes
    fprintf(arquivo, "<Requisitantes>\n");
    NO_CHAVE_P *NO_P = ListaP->Inicio;
    while (NO_P != NULL) {
        ElementoP *P = NO_P->DADOS->Inicio;
        while (P != NULL){
            fprintf(arquivo, " <Requisitante>\n");
            fprintf(arquivo, "  <ID>%s</ID>\n", P->pessoa->ID);
            fprintf(arquivo, "  <Nome>%s</Nome>\n", P->pessoa->NOME);
            fprintf(arquivo, "  <DataNasc>%02d/%02d/%d</DataNasc>\n", P->pessoa->dataNascimento->dia,P->pessoa->dataNascimento->mes, P->pessoa->dataNascimento->ano);
            fprintf(arquivo, "  <Naturalidade>%s</Naturalidade>\n", P->pessoa->freguesia->nome);
            fprintf(arquivo, " </Requisitante>\n");
            P = P->proximo;
        }
        NO_P = NO_P->Prox;
    }
    fprintf(arquivo, "</Requisitantes>\n");

    // Write Requisicoes
    fprintf(arquivo, "<Requisicoes>\n");
    ElementoR *R = ListaR->Inicio;
    while (R != NULL) {
        fprintf(arquivo, " <Requisicao>\n");
        fprintf(arquivo, "  <ID>%d</ID>\n", R->requisicao->ID);
        fprintf(arquivo, "  <Requisitante>%s</Requisitante>\n", R->requisicao->Pessoa->ID);
        fprintf(arquivo, "  <Livro>%s</Livro>\n", R->requisicao->Livro->ISBN);
        fprintf(arquivo, "  <Data>%02d/%02d/%d</Data>\n", R->requisicao->Data_Requisicao->dia, R->requisicao->Data_Requisicao->mes, R->requisicao->Data_Requisicao->ano);
        fprintf(arquivo, "  <Entregue>%d</Entregue>\n", R->requisicao->Entregue);
        fprintf(arquivo, " </Requisicao>\n");
        R = R->proximo;
    }
    fprintf(arquivo, " </Requisicoes>\n");

    // Write Distritos
    fprintf(arquivo, "<Distritos>\n");
    ElementoD *Distrito = LD->Inicio;
    while (Distrito != NULL) {
        fprintf(arquivo, " <Distrito>\n");
        fprintf(arquivo, "  <Nome>%s</Nome>\n", Distrito->Info->nome);
        fprintf(arquivo, "  <ID>%d</ID>\n", Distrito->Info->ID_DIST);
        fprintf(arquivo, "   <Concelhos>\n");

        ElementoC *Concelho = Distrito->Info->Conc->Inicio;
        while (Concelho != NULL) {
            fprintf(arquivo, "    <Concelho>\n");
            fprintf(arquivo, "     <Nome>%s</Nome>\n", Concelho->concelho->nome);
            fprintf(arquivo, "     <ID>%d</ID>\n", Concelho->concelho->ID_CONC);
            fprintf(arquivo, "      <Freguesias>\n");

            ElementoF *Freguesia = Concelho->concelho->freguesias->Inicio;
            while (Freguesia != NULL) {
                fprintf(arquivo, "       <Freguesia>\n");
                fprintf(arquivo, "        <Nome>%s</Nome>\n", Freguesia->freguesia->nome);
                fprintf(arquivo, "        <ID>%s</ID>\n", Freguesia->freguesia->ID);
                fprintf(arquivo, "       </Freguesia>\n");
                Freguesia = Freguesia->prox;
            }

            fprintf(arquivo, "      </Freguesias>\n");
            fprintf(arquivo, "    </Concelho>\n");
            Concelho = Concelho->prox;
        }

        fprintf(arquivo, "   </Concelhos>\n");
        fprintf(arquivo, " </Distrito>\n");
        Distrito = Distrito->Prox;
    }
    fprintf(arquivo, "</Distritos>\n");

    fprintf(arquivo, "</Biblioteca>\n");
    fclose(arquivo);
    EscreverLogs("\nXML Gravado com Sucesso\n");
}


void GravarTudoEMCSV(Lista_Chaves_L * ListaL, Lista_Chaves_P * ListaP, ListaRequisicoes * ListaR, Lista_D *LD){
    FILE *arquivo;

    // Write Livros
    arquivo = fopen("../CSV/Livros.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Livros.csv.\n");
        EscreverLogs("\nErro ao abrir o arquivo Livros.csv.\n");
        return;
    }
    NO_CHAVE_L *P = ListaL->Inicio;
    while (P != NULL) {
        ElementoL *L = P->DADOS->Inicio;
        while (L != NULL){
            fprintf(arquivo, "%s,%s,%s,%d,%s,%d,%d,%d\n", L->livro->ISBN, L->livro->NOME, L->livro->Autor, L->livro->anoPublicacao, L->livro->AREA, L->livro->quant_requisicaoL, L->livro->Disponivel, L->livro->Requisitado);
            L = L->proximo;
        }
        P = P->Prox;
    }
    fclose(arquivo);

    // Write Requisitantes
    arquivo = fopen("../CSV/Requisitantes.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Requisitantes.csv.\n");
        EscreverLogs("\nErro ao abrir o arquivo Requisitantes.csv.\n");
        return;
    }
    NO_CHAVE_P *NO_P = ListaP->Inicio;
    while (NO_P != NULL) {
        ElementoP *Pessoa = NO_P->DADOS->Inicio;
        while (Pessoa != NULL){
            fprintf(arquivo, "%s,%s,%d/%d/%d,%s\n", Pessoa->pessoa->ID, Pessoa->pessoa->NOME, Pessoa->pessoa->dataNascimento->dia, Pessoa->pessoa->dataNascimento->mes, Pessoa->pessoa->dataNascimento->ano, Pessoa->pessoa->freguesia->nome);
            Pessoa = Pessoa->proximo;
        }
        NO_P = NO_P->Prox;
    }
    fclose(arquivo);

    // Write Requisicoes
    arquivo = fopen("../CSV/Requisicoes.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Requisicoes.csv.\n");
        EscreverLogs("Erro ao abrir o arquivo Requisicoes.csv.\n");
        return;
    }
    ElementoR *Requisicao = ListaR->Inicio;
    while (Requisicao != NULL) {
        fprintf(arquivo, "%d,%s,%s,%d/%d/%d,%d\n", Requisicao->requisicao->ID, Requisicao->requisicao->Pessoa->ID, Requisicao->requisicao->Livro->ISBN, Requisicao->requisicao->Data_Requisicao->dia, Requisicao->requisicao->Data_Requisicao->mes, Requisicao->requisicao->Data_Requisicao->ano,Requisicao->requisicao->Entregue);
        Requisicao = Requisicao->proximo;
    }
    fclose(arquivo);

    // Write Distritos
    arquivo = fopen("../CSV/Distritos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo Distritos.csv.\n");
        EscreverLogs("Erro ao abrir o arquivo Distritos.csv.\n");
        return;
    }
    ElementoD *Distrito = LD->Inicio;
    while (Distrito != NULL) {
        fprintf(arquivo, "%s,%d\n", Distrito->Info->nome, Distrito->Info->ID_DIST);
        ElementoC *Concelho = Distrito->Info->Conc->Inicio;
        while (Concelho != NULL) {
            fprintf(arquivo, "%s,%d\n", Concelho->concelho->nome, Concelho->concelho->ID_CONC);
            ElementoF *Freguesia = Concelho->concelho->freguesias->Inicio;
            while (Freguesia != NULL) {
                fprintf(arquivo, "%s,%s\n", Freguesia->freguesia->nome, Freguesia->freguesia->ID);
                Freguesia = Freguesia->prox;
            }
            Concelho = Concelho->prox;
        }
        Distrito = Distrito->Prox;
    }
    fclose(arquivo);

    EscreverLogs("CSV Gravados com Sucesso");
}

