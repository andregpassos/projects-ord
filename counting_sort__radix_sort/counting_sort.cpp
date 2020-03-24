/*
UFPB - CENTRO DE INFORMÁTICA

Disciplina: Ordenação e Recuperação de Dados
Aluno: André Gomes Passos
Matrícula: 20190171426

PROGRAMA: COUNTING SORT IMPLEMENTADO COM ARRAY
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void print_arr(int arr[], int length) {
    cout << '{';
    for (int i = 0; i < length -1; i++)
        cout << arr[i] << ", ";
    cout << arr[length -1] << '}';
}

int arr_range(int arr[], int length) {
    int maior = arr[0];
    for (int i = 1; i < length; i++) {
        if (arr[i] > maior)
            maior = arr[i];
    }

    return maior;
}

void counting_sort(int in_arr[], int length, int range) {
    int out_arr[length];
    int count_arr[range +1] = {0};
    int pos_cont, pos_out_arr;

    // preencher o count array
    for (int i = 0; i < length; i++) {
		pos_cont = in_arr[i];
		count_arr[pos_cont]++;
	}
	// soma o proximo com o anterior no count array
	for (int i = 0; i < range; i ++) {
		count_arr[i+1] += count_arr[i];
	}
	// rotacionar para direita todo o count array (array shift right)
	for (int i = range; i > 0; i--) {
		count_arr[i] = count_arr[i-1];
	}
	count_arr[0] = 0;

    // preencher o output array ordenado
	for (int i = 0; i < length; i++) {
        pos_cont = in_arr[i];
        pos_out_arr = count_arr[pos_cont];
        out_arr[pos_out_arr] = in_arr[i];
        count_arr[pos_cont]++;
	}

	for (int i = 0; i < length; i++)
        in_arr[i] = out_arr[i];
}

int main() {
    char resposta = 's';

    while(resposta == 's' || resposta == 'S') {
        system("cls");
        int length;

        cout << "ORDENACAO DE UM ARRAY DE INTEIROS POR COUNTING SORT\n\n\n";
        cout << "Informe o tamanho do array: ";
        cin >> length;
        int arr[length];
        cout << "Digite 1 a 1 os elementos do array." << endl;
        for (int i = 0; i < length; i++)
            cin >> arr[i];

        cout << "Array de entrada: " << endl;
        print_arr(arr, length);
        cout << endl << endl;

        int range = arr_range(arr, length);
        counting_sort(arr, length, range);

        cout << "Array de saida (ordenado): " << endl;
        print_arr(arr, length);
        cout << endl << endl;

        cout << "Deseja executar o programa novamente (s/n)? ";
        cin >> resposta;
    }

    return (0);
}
