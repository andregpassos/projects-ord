/*

UFPB - CENTRO DE INFORMÁTICA

Disciplina: Ordenação e Recuperação de Dados
Aluno: André Gomes Passos
Matrícula: 20190171426

PROGRAMA: SELECTION SORT IMPLEMENTADO COM VETOR
*/

#include <stdio.h>
#include <stdlib.h> //para usar rand(), srand() e system()
#include <time.h> //para usar time()

int main()
{
    int vetor[20], pos, aux;
    char resposta = 's';

    while(resposta == 's' || resposta == 'S') {
        system("cls"); //limpar tela no windows
        printf("PROGRAMA QUE REALIZA O SELECTION SORT NUM VETOR DE NUMEROS INTEIROS ALEATORIOS\n\n\n");
        //seed para garantir valores aleatorios a cada nova execucao (baseado no relogio do SO)
        srand(time(NULL));

        //inicializa o vetor com valores aleatorios entre 0 e 512
        for (int i = 0; i < 20; i++) {
            vetor[i] = rand()%512;
        }

        //imprime o vetor original
        printf("Vetor Original = {");
        for (int i = 0; i < 19; i++) {
            printf("%d, ", vetor[i]);
        }
        printf("%d}\n\n", vetor[19]); //imprime o ultimo valor

        //vai encontrando o menor valor e jogando pro inicio
        for (int j = 0; j < 20; j++) {
            int menor = 512; //inicializa o menor como 512 (nesse caso serve como INF)
            for (int i = j; i < 20; i++) {
                if (vetor[i] < menor) {
                    menor = vetor[i]; //guarda o menor valor atual do vetor em 'menor'
                    pos = i; //guarda a posicao desse menor valor
                }
            }
            aux = vetor[j]; //guarda o valor que sera trocado pelo menor em 'aux'
            vetor[j] = menor; //vetor[j] recebe o valor do menor atual
            vetor[pos] = aux; //elemento da posicao na qual o menor valor estava recebe 'aux'
        }

        //imprime o vetor ordenado
        printf("Vetor Ordenado = {");
        for (int i = 0; i < 19; i++) {
            printf("%d, ", vetor[i]);
        }
        printf("%d}\n\n", vetor[19]); //imprime o ultimo valor

        printf("Deseja executar o programa novamente?(S/N) ");
        scanf("%s", &resposta);
        printf("\n");
    }

    return 0;
}
