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

//obtem o código começando no nó, utilizando o byte salvo em 'c', preenchendo 'buffer', desde o bucket 'tamanho'
bool procuraByte(noDeHuffman *no, byte c, char *buffer, int tamanho) {

    // Caso base da recursão:
    // Se o nó for folha e o seu valor for o buscado, colocar o caractere terminal no buffer e encerrar
    if (!(no->esq || no->dir) && no->chave == c)
    {
        buffer[tamanho] = '\0';
        return true;
    }
    else
    {
        bool encontrado = false;

        // Se existir um nó à esquerda
        if (no->esq)
        {
            // Adicione '0' no bucket do buffer correspondente ao 'tamanho' nodeAtual
            buffer[tamanho] = '0';

            // fazer recursão no nó esquerdo
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

noDeHuffman *BuildHuffmanTree(unsigned *vetorFreq) {
    // Lista com topo apontando pra NULL e com campo 'elementos' valendo 0;
    lista l = {NULL, 0};

    // Popula usando a array 'vetorFreq' (que contém as frequências) uma lista encadeada de nós.
    // Cada nó contém uma árvore.
    for (int i = 0; i < 256; i++)
    {
        if (vetorFreq[i]) // Se existe ocorrência do byte
        {
            // Insere na lista 'l' um nó referente ao byte i e sua respectiva frequência (guardada em vetorFreq[i]).
            // Faz os nós esquerdo e direito das árvores apontarem para NULL;
            inserirLista(novoNoDeLista(novoNoDeHuffman(i, vetorFreq[i], NULL, NULL)), &l);
        }
    }

    while (l.elementos > 1) // Enquanto o número de elementos da lista for maior que 1
    {
        // Nó esquerdo chama a função popMinLista() que vai na lista e pega a árvore fixada no primeiro nó
        // (que é a que contém a menor frequência)
        noDeHuffman *nodeEsquerdo = popMinLista(&l);

        // Pega o outro nó que tem menor frequência
        noDeHuffman *nodeDireito = popMinLista(&l);

        // Preenche com '#' o campo de caractere do nó da árvore.
        // Preenche o campo 'frequência' com a soma das frequências de 'nodeEsquerdo' e 'nodeDireito'.
        // Aponta o nó esquerdo para nodeEsquerdo e o nó direito para nodeDireito
        noDeHuffman *soma = novoNoDeHuffman('#', nodeEsquerdo->freq + nodeDireito->freq, nodeEsquerdo, nodeDireito);

        // Reinsere o nó 'soma' na lista l
        inserirLista(novoNoDeLista(soma), &l);
    }

    return popMinLista(&l);
}

void FreeHuffmanTree(noDeHuffman *n) {
    // Caso base da recursão, enquanto o nó não for NULL
    if (!n) return;
    else
    {
        noDeHuffman *esquerda = n->esq;
        noDeHuffman *direita = n->dir;
        free(n);
        FreeHuffmanTree(esquerda);
        FreeHuffmanTree(direita);
    }
}

int geraBit(FILE *entrada, int posicao, byte *aux ) {
    // É hora de ler um bit?
    (posicao % 8 == 0) ? fread(aux, 1, 1, entrada) : NULL == NULL ;

    // Exclamação dupla converte para '1' (inteiro) se não for 0. Caso contrário, deixa como está (0)
    // Joga '1' na casa binária 'posicao' e vê se "bate" com o byte salvo em *aux do momento
    // Isso é usado para percorrer a árvore (esquerda e direita)
    return !!((*aux) & (1 << (posicao % 8)));
}

void Comprimir(const char *arquivoEntrada, const char *arquivoSaida) {

    unsigned vetorFreq[256] = {0};

    // Abre arquivo do parâmetro arquivoEntrada no modo leitura de binário
    FILE *entrada = fopen(arquivoEntrada, "rb");
    if (entrada == NULL)    erroArquivo();

    // Abre arquivo do parâmetro arquivoSaida no modo escrita de binário
    FILE *saida = fopen(arquivoSaida, "wb");
    if (entrada == NULL)    erroArquivo();

    contFrequencia(entrada, vetorFreq);

    // Populando a árvore com a lista de frequência de bytes
    noDeHuffman *raiz = BuildHuffmanTree(vetorFreq);

    // Grava a lista de frequência nos primeiros 256 bytes do arquivo
    fwrite(vetorFreq, 256, sizeof(vetorFreq[0]), saida);

    // Move o ponteiro do stream 'saida' para a posição posterior ao tamanho de um unsigned int
    // É aqui que posteriormente será salvo o valor da variável 'tamanho'
    fseek(saida, sizeof(unsigned int), SEEK_CUR);

    byte c;
    unsigned tamanho = 0;
    byte aux = 0;

    while (fread(&c, 1, 1, entrada) >= 1)
    {

        // Cria um buffer vazio
        char buffer[1024] = {0};

        // Busca o código começando no nó 'raiz', utilizando o byte salvo em 'c', preenchendo 'buffer', desde o bucket deste último
        procuraByte(raiz, c, buffer, 0);

        // Laço que percorre o buffer
        for (char *i = buffer; *i; i++)
        {
            // Se o caractere na posição nodeAtual for '1'
            if (*i == '1')
            {
                // 2 elevado ao resto da divisão de 'tamanho' por 8
                // que é o mesmo que jogar um '1' na posição denotada por 'tamanho % 8'
                //aux = aux + pow(2, tamanho % 8);
                aux = aux | (1 << (tamanho % 8));
            }

            tamanho++;

            // Já formou um byte, é hora de escrevê-lo no arquivo
            if (tamanho % 8 == 0)
            {
                fwrite(&aux, 1, 1, saida);
                // Zera a variável auxiliar
                aux = 0;
            }
        }
    }

    // Escreve no arquivo o que sobrou
    fwrite(&aux, 1, 1, saida);

    // Move o ponteiro do stream para 256 vezes o tamanho de um unsigned int, a partir do início dele (SEEK_SET)
    fseek(saida, 256 * sizeof(unsigned int), SEEK_SET);

    // Salva o valor da variável 'tamanho' no arquivo saida
    fwrite(&tamanho, 1, sizeof(unsigned), saida);

    // Calcula tamanho dos arquivos
    fseek(entrada, 0L, SEEK_END);
    double tamanhoEntrada = ftell(entrada);

    fseek(saida, 0L, SEEK_END);
    double tamanhoSaida = ftell(saida);

    FreeHuffmanTree(raiz);

    printf("Arquivo de entrada: %s (%g bytes)\n", arquivoEntrada, tamanhoEntrada/1000);
    printf("Arquivo de saida: %s (%g bytes)\n", arquivoSaida, tamanhoSaida/1000);

    fclose(entrada);
    fclose(saida);

}

void Descomprimir(const char *arquivoEntrada, const char *arquivoSaida) {
    unsigned vetorFreq[256] = {0};

    // Abre arquivo do parâmetro arquivoEntrada no modo leitura de binário
    FILE *entrada = fopen(arquivoEntrada, "rb");
    if (entrada == NULL)    erroArquivo();

    // Abre arquivo do parâmetro arquivoSaida no modo escrita de binário
    FILE *saida = fopen(arquivoSaida, "wb");
    if (saida == NULL)      erroArquivo();

    // Lê a lista de frequência que encontra-se nos primeiros 256 bytes do arquivo
    fread(vetorFreq, 256, sizeof(vetorFreq[0]), entrada);

    // Constrói árvore
    noDeHuffman *raiz = BuildHuffmanTree(vetorFreq);

    // Lê o valor dessa posição do stream para dentro da variável tamanho
    unsigned tamanho;
    fread(&tamanho, 1, sizeof(tamanho), entrada);

    unsigned posicao = 0;
    byte aux = 0;

    // Enquanto a posicao for menor que tamanho
    while (posicao < tamanho)
    {
        // Salvando o noDeHuffman que encontramos
        noDeHuffman *nodeAtual = raiz;

        // Enquanto nodeAtual não for folha
        while ( nodeAtual->esq || nodeAtual->dir )
        {
            nodeAtual = geraBit(entrada, posicao++, &aux) ? nodeAtual->dir : nodeAtual->esq;
        }

        fwrite(&(nodeAtual->chave), 1, 1, saida);
    }

    FreeHuffmanTree(raiz);

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
    // Caso os parâmetros informados sejam insuficientes
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
    else if (!strcmp("-d", argv[1]))
    {
        if (strstr(argv[2], ".huff"))
        {
            Descomprimir(argv[2], argv[3]);
        }
        else
        {
            printf("O arquivo a ser descomprimido deve ter extensao '.huff'\n");
            printf("Exemplo: \n\t huffman descomprimir.huff -d descomprimido.extensao\n");
            return 0;
        }
    }
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
