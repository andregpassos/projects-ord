/*
UFPB - CENTRO DE INFORMÁTICA

Disciplina: Ordenação e Recuperação de Dados
Aluno: André Gomes Passos
Matrícula: 20190171426

PROGRAMA: RADIX SORT IMPLEMENTADO COM ARRAY
*/

#include <iostream>
#include <string>
using namespace std;

void print_arr(int arr[], int length) {
    cout << '{';
    for (int i = 0; i < length -1; i++)
        cout << arr[i] << ", ";
    cout << arr[length -1] << '}' << endl;
}

int find_digits(int arr[], int length) {
	int maior = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] > maior) {
			maior = arr[i];
		}
	}

	string numero = to_string(maior);
	return numero.length();
}

void counting_sort_digit(int in_arr[], int length, int base) {
    int maior = in_arr[0]%base;
    for (int i = 1; i < length; i++)
        if (in_arr[i]%base > maior)
            maior = in_arr[i]%base;

    int range = maior;
    int out_arr[length];
    int count_arr[range +1] = {0};
    int pos_cont, pos_out_arr;

    // preencher o count array
    for (int i = 0; i < length; i++) {
		pos_cont = in_arr[i]%base;
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
        pos_cont = in_arr[i]%base;
        pos_out_arr = count_arr[pos_cont];
        out_arr[pos_out_arr] = in_arr[i];
        count_arr[pos_cont]++;
	}

	for (int i = 0; i < length; i++)
        in_arr[i] = out_arr[i];
}

void radix_sort(int arr[], int length) {
    int digits = find_digits(arr, length);

	int base = 10;
	for (int i = 0; i < digits; i++) {
		counting_sort_digit(arr, length, base);
		base = base*10;
	}
}

int main() {
    int arr[6] = {53,89,150,36,633,233};

    print_arr(arr, 6);
    radix_sort(arr, 6);
    print_arr(arr, 6);

    return(0);
}
