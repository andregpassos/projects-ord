#include <stdio.h>
#include <stdlib.h>
#define MAX 100001

int tamanho_heap = 0;

void max_heapify(long int arvore[], int i) {
    int l, r, maior, temp;

    l = 2*i; //ESQUERDO(i)
    r = 2*i + 1; //DIREITO(i)

    //se o filho da esquerda for maior, guarda sua posicao no maior.
    if (l <= tamanho_heap && arvore[l] > arvore[i])
        maior = l;
    else //se nao, a posicao do maior eh o proprio i.
        maior = i;
    //se o filho da direita for maior, guarda sua posicao no maior.
    if (r <= tamanho_heap && arvore[r] > arvore[maior])
        maior = r;

    //se o maior nao for o proprio i, troca arvore[i] <-> arvore[maior] e executa o recursivo.
    if (maior != i) {
        temp = arvore[i];
        arvore[i] = arvore[maior];
        arvore[maior] = temp;

        max_heapify(arvore, maior);
    }
}

void build_max_heap(long int arvore[]){
    //comeca dos pais (nao faz as folhas)
    for (int i = tamanho_heap/2; i >= 1; i--)
        max_heapify(arvore, i);
}

void heap_sort(long int arvore[]) {
    int temp, comprimento = tamanho_heap;

    build_max_heap(arvore);
    for (int i = comprimento; i > 1; i--) {
        //troca o valor da ultima posicao com a raiz
        temp = arvore[i];
        arvore[i] = arvore[1];
        arvore[1] = temp;

        //reduz o tamanho do heap e joga novamente o maior valor pra raiz
        tamanho_heap = tamanho_heap -1;
        max_heapify(arvore, 1);
    }
}

int main() {
    long int vetor[MAX];
    int resp;

    printf("Digite 0 para ler o vetor padrao, ou outro numero para ler um arquivo.\n>");
    scanf("%d", &resp);
    printf("\n");

    if (!resp) {
        long int arvore[] = {6,8,9,7,16,10,14};
        //posicao 0 do vetor indica o tamanho do heap.
        //heap binario comeca da posicao 1.
        tamanho_heap = arvore[0];

        printf("Heap binario desordenado:\n\n");

        for (int i = 1; i <= arvore[0]; i++)
            printf("A[%d] = %d\n", i, arvore[i]);

        printf("\n");

        heap_sort(arvore);

        printf("Heap binario apos ordenacao por heapsort:\n\n");

        for (int i = 1; i <= arvore[0]; i++)
            printf("A[%d] = %d\n", i, arvore[i]);
    } else {
        FILE *arq;
        ///////////// LEITURA DE ARQUIVO /////////////////
        arq = fopen("num.100000.1.in", "rt");
            if (arq == NULL)  // Se houve erro na abertura
            {
                printf("Problemas na abertura do arquivo\n");
                return -1;
            }

            long int i = 0, numero;

            while (!feof(arq)) //verifica se esta no final do arquivo - feof
            {
                fscanf(arq, "%ld", &numero); //le a linha atual
                vetor[i] = numero;
                i++;
            }
        fclose(arq);
        /////////////////////////////////////////////////
        tamanho_heap = vetor[0];

        heap_sort(vetor);

        printf("Heap binario apos ordenacao por heapsort:\n\n");

        for (long int i = 1; i <= vetor[0]; i++)
            printf("A[%d] = %d\n", i, vetor[i]);
    }

    return 0;
}
