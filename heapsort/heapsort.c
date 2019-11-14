#include <stdio.h>
#include <stdlib.h>
#define MAX 100001

int tamanho_heap = 0;

void max_heapify(int arvore[], int i) {
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

void build_max_heap(int arvore[]){
    //comeca dos pais (nao faz as folhas)
    for (int i = tamanho_heap/2; i >= 1; i--)
        max_heapify(arvore, i);
}

void heap_sort(int arvore[]) {
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

//para ordenar numeros maiores que 2 bilhoes
void max_heapify_db(double arvore[], int i) {
    int l, r, maior;
    double temp;

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

        max_heapify_db(arvore, maior);
    }
}

//para ordenar numeros maiores que 2 bilhoes
void build_max_heap_db(double arvore[]){
    //comeca dos pais (nao faz as folhas)
    for (int i = tamanho_heap/2; i >= 1; i--)
        max_heapify_db(arvore, i);
}

//para ordenar numeros maiores que 2 bilhoes
void heap_sort_db(double arvore[]) {
    int comprimento = tamanho_heap;
    double temp;

    build_max_heap_db(arvore);
    for (int i = comprimento; i > 1; i--) {
        //troca o valor da ultima posicao com a raiz
        temp = arvore[i];
        arvore[i] = arvore[1];
        arvore[1] = temp;

        //reduz o tamanho do heap e joga novamente o maior valor pra raiz
        tamanho_heap = tamanho_heap -1;
        max_heapify_db(arvore, 1);
    }
}

int main() {
    int vetor[MAX];
    int resp;
    double vetor_db[MAX]; //para numeros maiores que 2 bilhoes

    printf("Digite 0 para ler o vetor padrao, ou outro numero para ler um arquivo.\n>");
    scanf("%d", &resp);
    printf("\n");

    if (!resp) {
        int arvore[] = {6,8,9,7,16,10,14};
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
        FILE *arq, *escrita;
        char resposta2[15];
        int n_terminou_de_ler = 1, k = 0, num_gigantes = 0;

        printf("\nQual arquivo voce deseja ler?\n");
        printf("'couting.txt'\n");
        printf("'num.1000.1.in'\n");
        printf("'num.1000.2.in'\n");
        printf("'num.1000.3.in'\n");
        printf("'num.1000.4.in'\n");
        printf("'num.10000.1.in'\n");
        printf("'num.10000.2.in'\n");
        printf("'num.10000.3.in'\n");
        printf("'num.10000.4.in'\n");
        printf("'num.100000.1.in'\n");
        printf("'num.100000.2.in'\n");
        printf("'num.100000.3.in'\n");
        printf("'num.100000.4.in'\n>");
        scanf("%s", &resposta2);

        while (n_terminou_de_ler) {
            if (resposta2[k] != '\0') {
                if (resposta2[k] == '4')
                    num_gigantes = 1;
            } else
                n_terminou_de_ler = 0;
            k++;
        }

        ///////////// LEITURA DE ARQUIVO /////////////////
        arq = fopen(resposta2, "rt");
            if (arq == NULL)  // Se houve erro na abertura
            {
                printf("Problemas na abertura do arquivo.\n");
                return -1;
            }

            char *result, Linha[100];
            int i = 0;

            if (!num_gigantes) {
                int numero;

                while (!feof(arq)) //verifica se esta no final do arquivo - feof
                {
                    //armazena linha a linha do arquivo num vetor de inteiros
                    result = fgets(Linha, 100, arq);
                    if (result){ //verifica se foi possivel ler a linha
                        numero = atoi(Linha);
                        vetor[i] = numero;
                    }
                    i++;
                }
            } else {
                double num_gig;

                while (!feof(arq)) //verifica se esta no final do arquivo - feof
                {
                    //armazena linha a linha do arquivo num vetor de doubles
                    result = fgets(Linha, 100, arq);
                    if (result){ //verifica se foi possivel ler a linha
                        num_gig = atof(Linha);
                        vetor_db[i] = num_gig;
                    }
                    i++;
                }
            }

        fclose(arq);
        /////////////////////////////////////////////////
        if (!num_gigantes) {
            tamanho_heap = vetor[0]; //a primeira linha do arquivo eh o tamanho da heap
            heap_sort(vetor);
        } else {
            tamanho_heap = (int) vetor_db[0];
            heap_sort_db(vetor_db);
        }

        char resposta[4];

        do {
            printf("\nDeseja imprimir na tela, ou gravar no arquivo 'resposta.txt'? (tela/arq)\n");
            scanf("%s", &resposta);

            if (strcmp (resposta, "tela") && strcmp (resposta, "arq"))
                printf("\nresposta invalida!\n");
        }while (strcmp (resposta, "tela") && strcmp (resposta, "arq"));

        // MENSAGEM NO TERMINAL
        if (!strcmp (resposta, "tela")) {
            printf("Heap binario apos ordenacao por heapsort:\n\n");

            if (!num_gigantes) {
                for (int i = 1; i <= vetor[0]; i++)
                        printf("%d ", vetor[i]);
            } else {
                for (int i = 1; i <= vetor_db[0]; i++)
                        printf("%.f ", vetor_db[i]);
            }
        } else {

            //////////////////////ESCRITA DE ARQUIVO///////////////////
            escrita = fopen("resposta.txt", "w");
                if (escrita == NULL)  // Se houve erro na abertura
                {
                    printf("Problemas na abertura do arquivo\n");
                    return -1;
                }

                if (!num_gigantes) {
                    fprintf(escrita, "%d\n", vetor[0]);

                    for (int i = 1; i <= vetor[0]; i++)
                        fprintf(escrita, "%d\n", vetor[i]);
                } else {
                    fprintf(escrita, "%.f\n", vetor_db[0]);

                    for (int i = 1; i <= vetor_db[0]; i++)
                        fprintf(escrita, "%.f\n", vetor_db[i]);
                }

            fclose(escrita);
            //////////////////////////////////////////////////////////
            printf("\nArquivo 'reposta.txt' gravado com sucesso!\n");
        }
    }

    return 0;
}
