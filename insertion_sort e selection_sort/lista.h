#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Aluno: André Gomes Passos - 20190171426

/////////////////////////////////////////////////////////////////////////////////////
///////////////PROGRAMA PARA CRIACAO E MANIPULACAO DE LISTA DINÂMICA/////////////////
////////////////////////////////////////////////////////////////////////////////////

//STRUCT CAIXA
//Struct utilizada para guardar cada elemento da lista.
//Guarda 1 elemento da lista e o ponteiro para a proxima caixa.

typedef struct caixa{
    int valor;
    unsigned int pos;
    struct caixa *prox;
}caixa;

//FUNCAO CRIAR LISTA
//Inicia uma lista vazia.

void criar(caixa **lista) {
    *lista = 0;
}

//FUNCAO VER SE É VAZIA
//Retorna true se a lista é vazia. Caso contrário, false.
bool listaVazia(caixa *lista) {
    if (lista == 0) return true;
    return false;
}

//FUNCAO ATUALIZA POSICAO
//Atualiza a posicao (chave) de todos os elementos da lista

void atualizaPos(caixa **lista) {
    caixa *aux = *lista;

    for (int i = 0; aux != 0; i++) {
        aux->pos = i;
        aux = aux->prox;
    }
}

//FUNCAO INSERCAO NO FIM
//Insere um elemento no fim da lista.

void inserirFim(caixa **lista, int valor){
    caixa *novo, *aux2;

    //alocacao dinamica para aux
    novo = (caixa*)malloc(sizeof(caixa));

    //se o malloc nao conseguir alocar (falta de espaco na memoria)
    //vai direto pro return e repassa a mesma lista que foi passada como parametro.
    if(novo != 0) {
        //cria-se uma caixa com o valor passado na funcao
        //e com o ponteiro prox aterrado (0).
        novo->valor = valor;
        novo->prox = 0;

        //condicao de insercao para lista vazia e lista semi-preenchida.
        if (listaVazia(*lista)) {
            novo->pos = 0;
            *lista = novo;
        } else {
            //auxiliar utilizado para percorrer a lista inteira
            aux2 = *lista;
            //laco para percorrer a lista inteira
            while (aux2->prox != 0) {
                aux2 = aux2->prox;
            }
            //conexao do ultimo elemento da lista com o novo elemento (novo),
            //que foi inserido no fim da lista.
            novo->pos = aux2->pos +1;
            aux2->prox = novo;
        }
    }
}

//FUNCAO INSERCAO NO INICIO
//Insere um elemento no inicio da lista.

void inserirInicio(caixa **lista, int valor){
    caixa *novo;

    novo = (caixa*)malloc(sizeof(caixa));

    if(novo != 0) {
        novo->valor = valor; //ate aqui, mesma logica do inserir no fim.

        //se a lista tiver vazia, aterra o *prox do novo e manda a lista apontar para o novo.
        //Se nao, primeiramente, o *prox aponta para o que a lista está apontando (primeiro elemento),
        //depois manda a lista apontar para o novo.
        if (listaVazia(*lista)) {
            novo->pos = 0;
            *lista = novo;
        } else {
            novo->prox = *lista;
            *lista = novo;
        }
    }
    atualizaPos(lista);
}

//FUNCAO REMOCAO DO FIM
//Remove o elemento que esta no fim da lista.

void removerFim(caixa **lista) {
    caixa *aux, *aux2;

    if (!listaVazia(*lista)) {
        aux = *lista;

        //garante que, ao remover o ultimo elemento, a lista nao fique "no limbo".
        if ((*lista)->prox == 0) {
            free(aux);
            *lista = 0;
        } else {
            //percorre toda a lista, guardando o ultimo elemento (aux) e o anterior (aux2).
            for (aux == *lista; aux->prox != 0; aux = aux->prox) {
                aux2 = aux;
            }

            //remove o ultimo elemento.
            free(aux);
            //aterra o penultimo elemento (que é o novo ultimo).
            aux2->prox = 0;
        }
    }
}

//FUNCAO REMOCAO DO INICIO
//Remove o elemento que esta no inicio da lista.

void removerInicio(caixa **lista) {
    caixa *aux;

    if (!listaVazia(*lista)) {
        if ((*lista)->prox == 0) {
            free(aux);
            *lista = 0;
        }
        //a lista passa a apontar para o proximo (segundo elemento)
        //e o elemento anterior é liberado da memoria, por meio do aux.
        else {
            aux = *lista;
            *lista = (*lista)->prox;
            free(aux);
        }
    }
    atualizaPos(lista);
}

//FUNCAO LISTAR
//Exibe todos os elementos da lista.

void listar(caixa *lista) {
    caixa *aux;
    aux = lista;

    if (listaVazia(lista)) printf("lista vazia!\n");
    //se a lista nao estiver vazia, imprime todos os elementos da mesma.
    else {
        printf("lista = {");
        //percorre toda a lista, imprimindo ate o penultimo elemento.
        for (aux == lista; aux->prox != 0; aux = aux->prox) {
            printf("%i, ", aux->valor);
        }
        //imprime o ultimo elemento e pula uma linha.
        printf("%i}\n", aux->valor);
    }
}

//FUNCAO LIMPAR
//Remove todos os elementos da lista.

void limpar(caixa **lista) {
    if (!listaVazia(*lista)) {
        //percorre toda a lista, removendo ate o penultimo elemento.
        while ((*lista)->prox) removerFim(lista);
        //remove o ultimo elemento
        removerInicio(lista);
    }
}

//FUNCAO INVERTER
//recebe como parametro a lista1, inverte seus elementos, guardando na lista2
//depois limpa a lista1 e retorna a lista2

struct caixa* inverter(caixa* lista1) {
    caixa *lista2;
    criar(&lista2);

    while (!listaVazia(lista1)) {
        //insere o primeiro elemento da lista1 no inicio da lista2
        //depois remove o elemento do inicio da lista1
        inserirInicio(&lista2, lista1->valor);
        removerInicio(&lista1);
    }

    return lista2;
}
