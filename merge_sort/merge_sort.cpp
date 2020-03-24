/*
UFPB - CENTRO DE INFORMÁTICA

Disciplina: Ordenação e Recuperação de Dados
Aluno: André Gomes Passos
Matrícula: 20190171426

PROGRAMA: QUICK SORT IMPLEMENTADO COM VETOR
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void print_vetor(int v[], int tamanho) {
    for (int i = 0; i < tamanho; i++)
        cout << v[i] << ' ';
    cout << endl;
}

void junta(int esq[], int tam_e, int dir[], int tam_d, int a[]) {
    int e = 0, d = 0, k = 0;

    while (e < tam_e && d < tam_d) {
        if (esq[e] < dir[d]) {
            a[k] = esq[e];
            e++;
        } else {
            a[k] = dir[d];
            d++;
        }
        k++;
    }
    for (;e < tam_e; k++, e++)
        a[k] = esq[e];
	for(;d < tam_d; k++, d++)
        a[k] = dir[d];
}

void merge_sort(int *a, int len_a) {
    int meio, i;

    if (len_a < 2)
        return;

    meio = len_a/2;
    int esq[meio];
    int dir[len_a - meio];

    for (int i = 0; i < meio; i++)
        esq[i] = a[i];
    for (int i = meio; i < len_a; i++)
        dir[i - meio] = a[i];

    merge_sort(esq, meio);
    merge_sort(dir, len_a - meio);
    junta(esq, meio, dir, len_a - meio, a);
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
        cout << "Lista Original: ";
        print_vetor(v, 20);

        merge_sort(v, 20);

        cout << "Lista Ordenada: ";
        print_vetor(v, 20);

        cout << endl << "Deseja executar o programa novamente?(S/N) ";
        cin >> resposta;
    }

    return (0);
}
