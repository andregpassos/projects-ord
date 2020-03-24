/*
GERADOR DE VETOR DE INTEIROS ALEATÓRIO
@author André Gomes Passos
@version 24/03/2020

Credits to: Thomás Augusto Gouveia Chaves
*/

#include <iostream>
#include <vector>
#include <algorithm> // random_shuffle
#include <time.h>
using namespace std;


vector<int> gen_alt_vec(int numb_of_elem) {
    vector<int> seed_vector(numb_of_elem*10, 0);
    vector<int> rand_vector(numb_of_elem, 0);

    for (int i = 0; i < numb_of_elem*10; i++)
        seed_vector[i] = i;

    srand(time(NULL)); // seed para random_shuffle(), baseada no clock so SO
    cout << endl << "Gerando vetor aleatorio ..." << endl;
    // pega valores no intervalo [0, numb_of_elem*10) e os embaralha randomicamente,
    // armazendando-os em 'seed_vector'
    random_shuffle(seed_vector.begin(), seed_vector.end());

    // pega os 10% inicial do 'seed_vector' e joga no 'rand_vector'
    for (int i = 0; i < numb_of_elem; i++)
        rand_vector[i] = seed_vector[i];

    return rand_vector;
}
