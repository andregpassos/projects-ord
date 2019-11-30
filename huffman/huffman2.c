#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "fila_pmin.h"

//tipo byte (como eh unsigned char, vai de 0 a 255);
typedef unsigned char byte;
unsigned int arvHuffman[257] = {0};

typedef struct noHuffman {
    byte chave;
    unsigned int freq;
    struct noHuffman *esq;
    struct noHuffman *dir;
} noHuffman;

//conta a quantidade de vezes que cada byte é lido e armazena num vetor de frequencias.
void contFrequencia(const char *arquivoLeitura, unsigned int vetorFrequencia[]) {
	byte c;

    FILE *leitura;

    leitura = fopen(arquivoLeitura, "rb");

    //soma +1 naquela posicao do vetor de frequencia cada vez que ela for lida novamente.
    while (!feof(leitura))
    {
        c = getc(leitura);
        vetorFrequencia[c]++;
    }

    fclose(leitura);
}

unsigned int buildHuffTree(unsigned int vetorFrequencia[]) {
    noHuffman *no;

    for (int i = 1; i < 257; i++)
    {
        if (vetorFrequencia[i]) //se houve ocorrencia do byte
        {
            //aloca memoria para o no
            if ((no = (noHuffman*)malloc(sizeof(noHuffman))) == NULL)
                return NULL;

            //no->esq = heap_extract_min()
        }
    }
}


int main (int argc, char* argv[]) {
        unsigned int vetorFrequencia[256] = {0};

        if (argc < 3) {
            printf("\tALGORITMO DE HUFFMAN\n\n");
            printf("Uso: nome_do_arquivo.extensao [opcoes]\n\n");
            printf("opcoes:\n    -f    Exibe o vetor de frequencias\n");
            printf("\nExemplo: ./huffman arquivo.extensao -f\n\n");
        } else {
            contFrequencia(argv[1], vetorFrequencia);
        }

        if (!strcmp("-f", argv[2])) {


            printf("vetorFrequencia = {");
            for (int i = 0; i < 255; i++)
                printf("%i, ", vetorFrequencia[i]);
            printf("%i}\n\n", vetorFrequencia[255]);
        }
	return 0;
}
