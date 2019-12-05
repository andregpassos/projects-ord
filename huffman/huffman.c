#include "funcoesAux.h"
#include <string.h>
#include <stdbool.h>

//conta a quantidade de vezes que cada byte é lido e armazena num vetor de frequencias.
void contFrequencia(FILE *arquivo, unsigned int vetorFreq[]) {
    byte chave;

    while (!feof(arquivo))
    {
        chave = getc(arquivo);
        vetorFreq[chave]++;
    }
    rewind(arquivo); //volta pro inicio do arquivo
}

//pega o código começando no nó e procura o byte, preenchendo o buffer de acordo com o tamanho
bool procuraByte(noDeHuffman *no, byte c, char *buffer, int tamanho) {

    //se o nó for a folha e o seu valor for buscado, colocar o caractere terminal no buffer e encerrar
    if (!(no->esq || no->dir) && no->chave == c)
    {
        buffer[tamanho] = '\0';
        return true;
    }
    else
    {
        bool encontrado = false;

        if (no->esq)
        {
            //adicione '0' no bucket do buffer correspondente ao 'tamanho' noAtual
            buffer[tamanho] = '0';

            //fazer recursão no nó esquerdo
            encontrado = procuraByte(no->esq, c, buffer, tamanho + 1);
        }

        if (!encontrado && no->dir)
        {
            buffer[tamanho] = '1';
            encontrado = procuraByte(no->dir, c, buffer, tamanho + 1);
        }
        if (!encontrado)
        {
            buffer[tamanho] = '\0';
        }
        return encontrado;
    }

}

//constroi a arvore de Huffman
noDeHuffman *buildHuffTree(unsigned *vetorFreq) {
    lista l = {NULL, 0};

    for (int i = 0; i < 256; i++)
    {
        if (vetorFreq[i]) //se existe a ocorrência do byte
            inserirLista(novoNoDeLista(novoNoDeHuffman(i, vetorFreq[i], NULL, NULL)), &l);
    }

    while (l.elementos > 1) //enquanto o número de elementos da lista for maior que 1
    {
        noDeHuffman *noEsquerdo = popLista(&l); //coloca o nó esquerdo
        noDeHuffman *noDireito = popLista(&l); //coloca o nó direito

        //coloca o nó da soma
        noDeHuffman *soma = novoNoDeHuffman('#', noEsquerdo->freq + noDireito->freq, noEsquerdo, noDireito);

        //insere o nó da soma na lista
        inserirLista(novoNoDeLista(soma), &l);
    }

    return popLista(&l);
}

//libera a arvore de Huffman da memória
void freeHuffTree(noDeHuffman *n) {
    //se o nó não for NULL, continua a recursão
    if (!n) return;
    else
    {
        noDeHuffman *esquerda = n->esq;
        noDeHuffman *direita = n->dir;
        free(n);
        freeHuffTree(esquerda);
        freeHuffTree(direita);
    }
}

//geracao de bits para a descompressao
int geraBit(FILE *entrada, int posicao, byte *aux ) {
    //é hora de ler um bit?
    (posicao % 8 == 0) ? fread(aux, 1, 1, entrada) : NULL == NULL ;

    //exclamação dupla converte para '1' (inteiro) se não for 0. Caso contrário, deixa como está (0)
    //joga '1' na casa binária 'posicao' e vê se "bate" com o byte salvo em *aux do momento
    //isso é usado para percorrer a árvore (esquerda e direita)
    return !!((*aux) & (1 << (posicao % 8)));
}

void Comprimir(const char *arquivoEntrada, const char *arquivoSaida) {

    unsigned vetorFreq[256] = {0};

    //abre o arquivo de entrada no modo de leitura binario "rb"
    FILE *entrada = fopen(arquivoEntrada, "rb");
    if (entrada == NULL)    erroArquivo();

    //abre o arquivo de saida no modo de escrita binario "wb"
    FILE *saida = fopen(arquivoSaida, "wb");
    if (entrada == NULL)    erroArquivo();

    contFrequencia(entrada, vetorFreq);

    //populando a árvore com a lista de frequência de bytes
    noDeHuffman *raiz = buildHuffTree(vetorFreq);

    //grava a lista de frequência nos primeiros 256 bytes do arquivo
    fwrite(vetorFreq, 256, sizeof(vetorFreq[0]), saida);

    //move o ponteiro do stream 'saida' para a posição posterior ao tamanho de um unsigned int
    //é aqui que posteriormente será salvo o valor da variável 'tamanho'
    fseek(saida, sizeof(unsigned int), SEEK_CUR);

    byte c;
    unsigned tamanho = 0;
    byte aux = 0;

    while (fread(&c, 1, 1, entrada) >= 1)
    {

        //cria um buffer vazio
        char buffer[1024] = {0};

        //busca o código começando no nó 'raiz', utilizando o byte salvo em 'c', preenchendo 'buffer', desde o bucket deste último
        procuraByte(raiz, c, buffer, 0);

        //percorre o buffer
        for (char *i = buffer; *i; i++)
        {
            //se o caractere na posição do nó atual for '1'
            if (*i == '1')
            {
                //2 elevado ao resto da divisão de 'tamanho' por 8
                //que é o mesmo que jogar um '1' na posição denotada por 'tamanho % 8'
                aux = aux | (1 << (tamanho % 8));
            }

            tamanho++;

            //já formou um byte, é hora de escrevê-lo no arquivo
            if (tamanho % 8 == 0)
            {
                fwrite(&aux, 1, 1, saida);
                //zera a variável auxiliar
                aux = 0;
            }
        }
    }

    //escreve no arquivo o que sobrou
    fwrite(&aux, 1, 1, saida);

    //move o ponteiro do stream para 256 vezes o tamanho de um unsigned int, a partir do início dele (SEEK_SET)
    fseek(saida, 256 * sizeof(unsigned int), SEEK_SET);

    //salva o valor da variável 'tamanho' no arquivo saida
    fwrite(&tamanho, 1, sizeof(unsigned), saida);

    //calcula tamanho dos arquivos
    fseek(entrada, 0L, SEEK_END);
    double tamanhoEntrada = ftell(entrada);

    fseek(saida, 0L, SEEK_END);
    double tamanhoSaida = ftell(saida);

    freeHuffTree(raiz);

    printf("Arquivo de entrada: %s (%g bytes)\n", arquivoEntrada, tamanhoEntrada/1000);
    printf("Arquivo de saida: %s (%g bytes)\n", arquivoSaida, tamanhoSaida/1000);

    fclose(entrada);
    fclose(saida);

}

void Descomprimir(const char *arquivoEntrada, const char *arquivoSaida) {
    unsigned vetorFreq[256] = {0};

    //abre arquivo do parâmetro arquivoEntrada no modo leitura de binário
    FILE *entrada = fopen(arquivoEntrada, "rb");
    if (entrada == NULL)    erroArquivo();

    //abre arquivo do parâmetro arquivoSaida no modo escrita de binário
    FILE *saida = fopen(arquivoSaida, "wb");
    if (saida == NULL)      erroArquivo();

    //lê a lista de frequência que encontra-se nos primeiros 256 bytes do arquivo
    fread(vetorFreq, 256, sizeof(vetorFreq[0]), entrada);

    //constrói árvore
    noDeHuffman *raiz = buildHuffTree(vetorFreq);

    //lê o valor dessa posição do stream para dentro da variável tamanho
    unsigned tamanho;
    fread(&tamanho, 1, sizeof(tamanho), entrada);

    unsigned posicao = 0;
    byte aux = 0;

    //enquanto a posicao for menor que tamanho
    while (posicao < tamanho)
    {
        //salvando o noDeHuffman que encontramos
        noDeHuffman *noAtual = raiz;

        //enquanto noAtual não for folha
        while ( noAtual->esq || noAtual->dir )
        {
            noAtual = geraBit(entrada, posicao++, &aux) ? noAtual->dir : noAtual->esq;
        }

        fwrite(&(noAtual->chave), 1, 1, saida);
    }

    freeHuffTree(raiz);

    fseek(entrada, 0L, SEEK_END);
    double tamanhoEntrada = ftell(entrada);

    fseek(saida, 0L, SEEK_END);
    double tamanhoSaida = ftell(saida);

    printf("Arquivo de entrada: %s (%g bytes)\n", arquivoEntrada, tamanhoEntrada/1000);
    printf("Arquivo de saida: %s (%g bytes)\n", arquivoSaida, tamanhoSaida/1000);

    fclose(saida);
    fclose(entrada);
}


int main(int argc, char *argv[]) {
    //caso os parâmetros nao sejam suficientes
    if (argc < 3)
    {
        printf("\t\tALGORITMO DE HUFFMAN\n\n");
        printf("Uso: nome_do_arquivo.extensao [opcoes]\n\n");
        printf("opcoes:\n\t-f    Exibe o vetor de frequencias\n");
        printf("    \t-c    Comprime um arquivo em outro\n");
        printf("    \t-d    Descomprime um arquivo comprimido\n");
        printf("\nExemplo:\n\n\tLinux   ->  ./huffman arquivo.extensao -f\n");
        printf("\tWindows ->  huffman arquivo.extensao -f\n\n");
        return 0;
    }
    if (!strcmp("-f", argv[2])) {
        unsigned int vetorFreq[255] = {0};

        FILE *arquivo = fopen(argv[1], "rb");
        if(arquivo == NULL)    erroArquivo();

        contFrequencia(arquivo, vetorFreq);

        printf("Vetor de Frequencia = {");
        for (int i = 0; i < 254; i++)
            printf("%i, ", vetorFreq[i]);
        printf("%i}\n", vetorFreq[254]);
    }

    else if (!strcmp("-c", argv[2]))
    {
        if (argv[3]) {
            if (strstr(argv[3], ".huff"))
            {
                Comprimir(argv[1], argv[3]);
            }
            else
            {
                printf("O arquivo comprimido deve ter extensao '.huff'\n");
                printf("Exemplo: \n\t huffman comprimir.extensao -c comprimido.huff\n");
                return 0;
            }
        }
        else {
            printf("Voce nao informou o arquivo de saida.\n");
        }
    }
    else if (!strcmp("-d", argv[2]))
    {
        if (strstr(argv[1], ".huff"))
        {
            Descomprimir(argv[1], argv[3]);
        }
        else
        {
            printf("O arquivo a ser descomprimido deve ter extensao '.huff'\n");
            printf("Exemplo: \n\t huffman descomprimir.huff -d descomprimido.extensao\n");
            return 0;
        }
    }
    //qualquer outro caso que nao seja -f, -c ou -d
    else
    {
        printf("\t\tALGORITMO DE HUFFMAN\n\n");
        printf("Uso: nome_do_arquivo.extensao [opcoes]\n\n");
        printf("opcoes:\n\t-f    Exibe o vetor de frequencias\n");
        printf("    \t-c    Comprime um arquivo em outro\n");
        printf("    \t-d    Descomprime um arquivo comprimido\n");
        printf("\nExemplo:\n\n\tLinux   ->  ./huffman arquivo.extensao -f\n");
        printf("\tWindows ->  huffman arquivo.extensao -f\n\n");
        return 0;
    }

    return 0;
}
