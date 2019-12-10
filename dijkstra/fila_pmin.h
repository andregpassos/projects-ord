#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100001
#define INF 2147483647

int tamanho_heap = 0;

//joga o menor pra raiz e executa o recursivo
void min_heapify(int arvore[], int i) {
    int l, r, menor, temp;

    l = 2*i; //ESQUERDO(i)
    r = 2*i + 1; //DIREITO(i)

    //se o filho da esquerda for menor, guarda sua posicao no menor.
    if (l <= tamanho_heap && arvore[l] < arvore[i])
        menor = l;
    else //se nao, a posicao do menor eh o proprio i.
        menor = i;
    //se o filho da direita for menor, guarda sua posicao no menor.
    if (r <= tamanho_heap && arvore[r] < arvore[menor])
        menor = r;

    //se o menor nao for o proprio i, troca arvore[i] <-> arvore[menor] e executa o recursivo.
    if (menor != i) {
        temp = arvore[i];
        arvore[i] = arvore[menor];
        arvore[menor] = temp;

        min_heapify(arvore, menor);
    }
}

void build_min_heap(int arvore[]){
    //comeca dos pais (nao faz as folhas)
    for (int i = tamanho_heap/2; i >= 1; i--)
        min_heapify(arvore, i);
}

int heap_minimun(int arvore[]){
    return arvore[1];
}

int heap_extract_min (int arvore[]){
    if (tamanho_heap < 1) {
        printf("\nheap underflow\n");
        return -1;
    }

    int min = arvore[1];

    arvore[1] = arvore[tamanho_heap];
    --tamanho_heap;
    min_heapify(arvore, 1);

    return min;
}

int heap_decrease_key (int arvore[], int i, int chave) {
    if (chave >= arvore[i]) {
        printf("\nNada a ser feito!\n");
        return -1;
    }

    //troca o valor de arvore[i] pelo valor da chave.
    arvore[i] = chave;

    int temp;

    //para tornar a fila novamente de prioridade minima
    //vai subindo ate a raiz verificando se precisa trocar o valor...
    while (i > 1) {
        if (arvore[i/2] > arvore[i]) {  //i/2 = pai(i)
            temp = arvore[i];
            arvore[i] = arvore[i/2];
            arvore[i/2] = temp;
        }
        i = i/2;
    }
}

//aumenta o tamanho da fila e insere um novo elemento
int min_insert_key (int arvore[], int chave) {
    ++tamanho_heap;
    arvore[tamanho_heap] = INF;
    heap_decrease_key(arvore, tamanho_heap, chave);
}
