#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "fila_pmin.h"

//tipo byte (como eh unsigned char, vai de 0 a 255);
typedef unsigned char byte;
unsigned int arvHuffman[257] = {0};

typedef struct noDeHuffman {
    byte chave;
    unsigned int freq;
    struct noDeHuffman *esq, *dir;
} noDeHuffman;

//conta a quantidade de vezes que cada byte é lido e armazena num vetor de frequencias.
int contFrequencia(const char *arquivoLeitura, unsigned int vetorFrequencia[]) {
	byte c;

    FILE *leitura;

    leitura = fopen(arquivoLeitura, "rb");

    if (leitura == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo.\n");
        return -1;
    }

    //soma +1 naquela posicao do vetor de frequencia cada vez que ela for lida novamente.
    while (!feof(leitura))
    {
        c = getc(leitura);
        vetorFrequencia[c]++;
    }

    fclose(leitura);
}

unsigned int buildHuffTree(unsigned int vetorFrequencia[]) {
    noDeHuffman *no;
    arvHuffman[0] = 255;

    for (int i = 0; i < 256; i++)
        arvHuffman[i+1] = vetorFrequencia[i];

    //build_min_heap(arvHuffman);

    for (int i = 1; i <256; i++) {
        if (vetorFrequencia[i]) //se houve ocorrencia do byte
        {
            //aloca memoria para o no
            if ((no = (noDeHuffman*)malloc(sizeof(noDeHuffman))) == NULL)
                return 5;

            //no->esq = heap_extract_min()
        }
    }
}

int main (int argc, char* argv[]) {
        unsigned int vetorFrequencia[255] = {0};

        if (argc < 3) {
            printf("\t\tALGORITMO DE HUFFMAN\n\n");
            printf("Uso: nome_do_arquivo.extensao [opcoes]\n\n");
            printf("opcoes:\n\t-f    Exibe o vetor de frequencias\n");
            printf("\nExemplo:\n\n\tLinux   ->  ./huffman arquivo.extensao -f\n");
            printf("\tWindows ->  huffman arquivo.extensao -f\n\n");
        }

        else if (!strcmp("-f", argv[2])) {
            if (contFrequencia(argv[1], vetorFrequencia) != -1) { //verifica se foi possivel abrir o arquivo
                printf("\nvetor de frequencia = {");
                for (int i = 0; i < 254; i++)
                    printf("%i, ", vetorFrequencia[i]);
                printf("%i}\n\n", vetorFrequencia[254]);
            }
        }
	return 0;
}
