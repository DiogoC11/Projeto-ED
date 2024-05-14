#include "Livro.h"
#include "ctype.h"

// Função para encontrar o NO_CHAVE_L por uma KEY
NO_CHAVE_L *encontrarNoChave(NO_CHAVE_L *noChave, char *chave) {
    while (noChave != NULL) {
        if (strcmp(noChave->categoria, chave) == 0) {
            return noChave;
        }
        noChave = noChave->Prox;
    }
    return NULL;
}

LIVRO *CriarLivro(char *_ISBN, char *_nome, char *_area, int _anoPublicacao, char *_autor)
{
    LIVRO *P = (LIVRO *)malloc(sizeof(LIVRO));
    P->NOME = (char *)malloc((strlen(_nome) + 1)*sizeof(char));
    strcpy(P->NOME, _nome);
    P->AREA = (char *)malloc((strlen(_area) + 1)*sizeof(char));
    strcpy(P->AREA, _area);
    P->anoPublicacao = _anoPublicacao;
    P->ISBN = (char *) malloc(strlen(_ISBN + 1)*sizeof(char));
    strcpy(P->ISBN,_ISBN);
    P->Autor = (char *) malloc(strlen(_autor + 1)*sizeof(char));
    strcpy(P->Autor,_autor);
    P->Disponivel = 0;
    return P;
}

LIVRO *PedirDadosLivro(Lista_Chaves_L *C){
    char nome[50], area[50], ISBN[50], autor[50], temp[100];
    int anoPublicacao;
    fflush(stdin);
    printf("\nCriar Livro: ");

    do {
        printf("\nISBN: ");
        fgets(temp, sizeof(temp), stdin);
        sscanf(temp, "%49[^\n]", ISBN);

        if (PesquisarLivroPorISBN(C, ISBN) != NULL) {
            printf("\nErro: O ISBN inserido já existe.\n");
        }
    }while(PesquisarLivroPorISBN(C,ISBN) != NULL);

    printf("\nTitulo do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%[^\n]", nome);

    printf("\nArea do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%[^\n]", area);

    printf("\nAno de Publicacao: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%d", &anoPublicacao);

    printf("\nAutor do Livro: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%49[^\n]", autor);

// Deixar a AREA em maiuscula
    for (int i = 0; i < strlen(area); i++) {
        area[i] = toupper(area[i]);
    }

    return CriarLivro(ISBN, nome, area, anoPublicacao, autor);
}

void MostrarLivro(LIVRO *P)
{
    char disponivel[4];
    if(P->Disponivel ){
        strcpy(disponivel,"NAO");
    }else{
        strcpy(disponivel,"SIM");
    }
    printf("\nLivro: \nISBN: %s\nTitulo: %s \nArea: %s \nAutor: %s \nAno de Publicacao: %d\nDisponivel? %s\n", P->ISBN, P->NOME, P->AREA, P->Autor, P->anoPublicacao,disponivel);
}
void DestruirLivro(LIVRO *P)
{
    free (P->NOME);
    free (P->AREA);
    free(P->ISBN);
    free(P->Autor);
    free (P);
}
ListaLivro *criarListaL(){
    ListaLivro *L = (ListaLivro *) malloc(sizeof (ListaLivro));
    if (!L) return NULL;
    L->num_Livros = 0;
    L->Inicio = NULL;
    return L;
}

ElementoL *criar_elementoL(LIVRO *L){
    ElementoL *e = (ElementoL * ) malloc(sizeof (ElementoL));
    if(!e) return NULL;
    e->livro = L;
    e->proximo = NULL;
    return e;
}

void *AdicionarLivro(ElementoL *E, Lista_Chaves_L *C){
    int a = 0;
    if(!C) return NULL;
    if(!E) return NULL;
    NO_CHAVE_L *Inicio = C->Inicio;
    for(int i = 0; i < C->num_chaves; i++){
        if(Inicio->categoria == E->livro->AREA){
            if(C->Inicio->DADOS->Inicio==0) {
                C->Inicio->DADOS->Inicio = E;
            }else{
                ElementoL  *ultimo = C->Inicio->DADOS->Inicio;
                while (ultimo->proximo != NULL){
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = E;
            }
            a=1;
            C->Inicio->DADOS->num_Livros ++;
        }
        Inicio = Inicio->Prox;
    }
    if(!a){
        AdicionarChave(C,E->livro->AREA);
        C->num_chaves ++;
        C->Inicio->DADOS->Inicio = E;
        C->Inicio->DADOS->num_Livros ++;
    }
    printf("\nLivro adicionado a biblioteca.\n");
}

void ListarLivros(Lista_Chaves_L *C){
    printf("\nLista de Livros:\n");
    NO_CHAVE_L *N = C->Inicio;
    ElementoL *E = C->Inicio->DADOS->Inicio;
    for (int i = 0; i < C->num_chaves; i++){
        for(int j = 0; i < N->DADOS->num_Livros; j++){
            printf("\nLivro: ");
            MostrarLivro(E->livro);
            E = E->proximo;
        }
        N = N->Prox;
    }
}
LIVRO *PesquisarLivroPorISBN(Lista_Chaves_L *C, char *isbn) {
    NO_CHAVE_L *N = C->Inicio;
    ElementoL *E = C->Inicio->DADOS->Inicio;
    for(int i = 0; i < C->num_chaves; i++){
        for (int j = 0; i < N->DADOS->num_Livros; j++) {
            if(strcmp(E->livro->ISBN,isbn) == 0){
                return E->livro;
            }
            E = E->proximo;
        }
        N = N->Prox;
    }

    return NULL;
}
LIVRO *LivroMaisRecente(Lista_Chaves_L * L) {
    if (L->num_chaves == 0) {
        return NULL;
    }
    NO_CHAVE_L *N = L->Inicio;
    LIVRO *maisRecente = N->DADOS->Inicio->livro;
    ElementoL *E = L->Inicio->DADOS->Inicio;
    for(int i = 0; i < L->num_chaves; i++){
        for (int j = 0; i < N->DADOS->num_Livros; j++) {
            if (E->livro->anoPublicacao > maisRecente->anoPublicacao) {
                maisRecente = E->livro;
            }
            E = E->proximo;
        }
        N = N->Prox;
    }
    return maisRecente;
}

void AreaMaisLivros(Lista_Chaves_L *C){
    NO_CHAVE_L *Area = C->Inicio;
    NO_CHAVE_L *Inicio = C->Inicio;
    for(int i = 0; i < C->num_chaves; i++){
        if(Inicio->DADOS->num_Livros > Area->DADOS->num_Livros ){
            Area = Inicio->categoria;
        }
        Inicio = Inicio->Prox;
    }
    printf("A area com mais livros na biblioteca é: %s", Area->categoria);
}

Lista_Chaves_L *CriarListaChaves(){
    Lista_Chaves_L *L = (Lista_Chaves_L *)malloc(sizeof(Lista_Chaves_L));
    L->num_chaves = 0;
    L->Inicio = NULL;
    return L;
}

NO_CHAVE_L *AdicionarChave(Lista_Chaves_L *L, char *categoria)
{
    if (!L) return NULL;
    NO_CHAVE_L *chave = (NO_CHAVE_L *)malloc(sizeof(NO_CHAVE_L));
    strcpy(chave->categoria, categoria);
    chave->DADOS = criarListaL();
    chave->Prox = L->Inicio;
    L->Inicio = chave;
    L->num_chaves ++;
    return L;
}
