/*
UFPB - CENTRO DE INFORMÁTICA

Disciplina: Ordenação e Recuperação de Dados
Aluno: André Gomes Passos
Matrícula: 20190171426

PROGRAMA: QUICK SORT IMPLEMENTADO COM VETOR
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

//troca a posicao de 2 inteiros
void troca(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

//organiza os menores elementos à esquerda do pivor
//e os maiores elementos à direita do pivor
int separa(int v[], int low, int high) {
    int piv_pos, pivot = v[high], i = low -1;

    for (int j = low; j < high; j++) {
        if (v[j] < pivot) {
            i++;
            troca(&(v[j]), &(v[i]));
        }
    }
    troca(&(v[i +1]), &(v[high]));
    piv_pos = i +1;

    return piv_pos;
}

//usa a recursividade para dividir o vetor em partes
//e ordena-lo, aumentando a performance
void quick_sort(int v[], int low, int high) {
    if (low < high) {
        int piv_pos = separa(v, low, high);

        quick_sort(v, low, piv_pos -1); //quick_sort(left)
        quick_sort(v, piv_pos +1, high); //quick_sort(right)
    }
}

void imprime_vetor (int v[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        cout << ' ' << v[i];
    cout << endl;
}

int main() {
char resposta = 's';

    while(resposta == 's' || resposta == 'S') {
        int v[20];

        system("cls"); //limpar tela no windows
        cout << "PROGRAMA QUE REALIZA O QUICK SORT NUM VETOR DE NUMEROS INTEIROS ALEATORIOS\n\n";
        srand(time(NULL)); //seed para rand() baseada no relogio do SO

        //inicializa a lista1 com valores aleatorios
        for (int i = 0; i < 20; i++) v[i] = rand()%100;

        //imprime todos os valores da lista original
        cout << "Lista Original:";
        imprime_vetor(v, 20);

        quick_sort(v, 0, 19);

        cout << "Lista Ordenada:";
        imprime_vetor(v, 20);

        cout << endl << "Deseja executar o programa novamente?(S/N) ";
        cin >> resposta;
    }

    return (0);
}
