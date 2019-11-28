#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tipo byte (como eh unsigned char, vai de 0 a 255);
typedef unsigned char byte;

//conta a quantidade de vezes que cada byte é lido e armazena num vetor de frequencias.
void contFrequencia(const char *arquivoEntrada, unsigned int vetorFrequencia[]) {
	byte c;

    FILE *arquivo = fopen(arquivoEntrada, "rb");
	//fread usada para ler de byte a byte
	//soma +1 naquela posicao do vetor de frequencia
	//cada vez que ela for lida novamente.

	//for (int i = 0; i < 256; i++) vetorFrequencia[i] = i; //TESTE

    while (fread(&c, 1, 1, arquivo))
    {
        vetorFrequencia[(byte) c]++;
    }

    fclose(arquivo);
}


int main (int argc, char* argv[]) {
        unsigned int vetorFrequencia[256] = {0};

        if (argc < 3) {
            printf("\tALGORITMO DE HUFFMAN\n\n");
            printf("Uso: nome_do_arquivo.extensao [opcoes]\n\n");
            printf("opcoes:\n    -f    Exibe o vetor de frequencias\n");
            printf("\nExemplo: ./huffman arquivo.extensao -f\n\n");
        }

        printf("Vetor de frequencias antes de chamar o metodo:\n");
        printf("vetorF = { ");

        for (int i = 0; i < 256; i++)
            printf("%i, ", vetorFrequencia[i]);
        printf("}\n\n");

        if (!strcmp("-f", argv[2])) {
            contFrequencia(argv[1], vetorFrequencia);
        }

        printf("Vetor de frequencias apos chamar o metodo:\n");
        printf("vetorF = { ");

        for (int i = 0; i < 256; i++)
            printf("%i, ", vetorFrequencia[i]);
        printf("}\n\n");
}
