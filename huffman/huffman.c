#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tipo byte (como eh unsigned char, vai de 0 a 255);
typedef unsigned char byte;

typedef struct noDeHuffman {
    byte chave;
    unsigned int freq;
    struct noDeHuffman *esq;
    struct noDeHuffman *dir;
} noDeHuffman;

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


int main (int argc, char* argv[]) {
        unsigned int vetorFrequencia[256] = {0};

        if (argc < 3) {
            printf("\tALGORITMO DE HUFFMAN\n\n");
            printf("Uso: nome_do_arquivo.extensao [opcoes]\n\n");
            printf("opcoes:\n    -f    Exibe o vetor de frequencias\n");
            printf("\nExemplo: ./huffman arquivo.extensao -f\n\n");
        }

        if (!strcmp("-f", argv[2])) {
            contFrequencia(argv[1], vetorFrequencia);

            printf("vetorFrequencia = {");
            for (int i = 0; i < 255; i++)
                printf("%i, ", vetorFrequencia[i]);
            printf("%i}\n\n", vetorFrequencia[255]);
        }
	return 0;
}
