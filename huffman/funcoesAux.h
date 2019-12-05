#include <stdio.h>
#include <stdlib.h>

//tipo byte (como eh unsigned char, vai de 0 a 255);
typedef unsigned char byte;

typedef struct noDeHuffman {
    byte chave;
    unsigned int freq;
    struct noDeHuffman *esq, *dir;
} noDeHuffman;

typedef struct noDeLista
{
    noDeHuffman          *no;
    struct noDeLista    *prox;
} noDeLista;

typedef struct lista
{
    noDeLista   *topo;
    int         elementos;
} lista;

noDeLista *novoNoDeLista(noDeHuffman *nArv)
{
    //cria um novo no de lista e aloca na memoria
    noDeLista *novo;
    if ( (novo = malloc(sizeof(*novo))) == NULL ) return NULL;

    //adiciona o noDeHuffman a lista
    novo->no = nArv;

    //prox aponta para null
    novo->prox = NULL;

    return novo;
}

noDeHuffman *novoNoDeHuffman(byte c, int freq, noDeHuffman *esq, noDeHuffman *dir)
{
    // Aloca memória
    noDeHuffman *novo;

    if (!(novo = malloc(sizeof(*novo)))) return NULL;

    // Atribui na árvore os valores passados como parâmetro
    novo->chave = c;
    novo->freq = freq;
    novo->esq = esq;
    novo->dir = dir;

    return novo;
}

//Insere uma novo nó na lista passada como parametro.
void inserirLista(noDeLista *n, lista *lista)
{
    //insere um novo nó no inicio, caso a lista seja vazia
    if (!lista->topo)
    {
        lista->topo = n;
    }
    //se a frequencia do nó 'n' for menor que a frenquencia do nó do topo
    //o prox aponta para o topo anterior e o topo atual passa a ser 'n'
    else if (n->no->freq < lista->topo->no->freq)
    {
        n->prox = lista->topo;
        lista->topo = n;
    }
    else
    {
        //inicia aux e aux2 apontando para o primeiro e segundo elemento da lista, repectivamente.
        noDeLista *aux = lista->topo;
        noDeLista *aux2 = lista->topo->prox;


        //percorre a lista até o final, ou até que a frequência do segundo nó
        //seja maior que a do nó 'n'.
        while (aux2 && (aux2->no->freq <= n->no->freq))
        {
            aux = aux2;
            aux2 = aux->prox;
        }

        //insere o nó na posição certa.
        aux->prox = n;
        n->prox = aux2;
    }

    //incrementa quantidade de elementos
    lista->elementos++;
}

noDeHuffman *popMinLista(lista *lista)
{

    //ponteiro auxilar que aponta para o primeiro nó da lista
    noDeLista *aux = lista->topo;

    //ponteiro auxiliar que aponta para a árvore contida em aux (árvore do primeiro nó da lista)
    noDeHuffman *aux2 = aux->no;

    //aponta o 'topo' da lista para o segundo elemento dela
    lista->topo = aux->prox;

    //libera o ponteiro aux
    free(aux);
    aux = NULL;

    //decrementa a quantidade de elementos
    lista->elementos--;

    return aux2;
}

void erroArquivo()
{
    printf("Arquivo a ser lido nao foi encontrado\n");
    exit(-1);
}
