#include <iostream>
#include <climits>
#include <fstream>
#include <stdlib.h>
using namespace std;

int findMinVert(int *distancia, bool *visitado, int n) {
    //implementar com prioridade minima

    int minVert = -1;
    for (int i = 0; i < n; i++) {
        if(!visitado[i] && (minVert = -1 || distancia[i] < distancia[minVert])) {
            minVert = i;
        }
    }
    return minVert;
}

void dijkstra (int **matriz, int n) {
    int *distancia = new int[n];
    bool *visitado = new bool[n];

    distancia[0] = 0;
    visitado[0] = false;
    for (int i = 1; i < n; i++) {
        distancia[i] = INT_MAX;
        visitado[i] = false;
    }

    for (int i = 0; i < n-1; i++) {
        int minVert = findMinVert(distancia, visitado, n);
        visitado[minVert] = true;
        for (int j = 0; j < n; j++) {
            if (matriz[minVert][j] != 0 && !visitado[j]) {
                int dist = distancia[minVert] + matriz[minVert][j];
                if (dist < distancia[j]) {
                    distancia[j] = dist;
                }
            }
        }
    }

    for (int i = 0; i < n; i++){
        cout << i << " " << distancia[i] << endl;
    }
    delete [] visitado;
    delete [] distancia;

}

int main() {
    int n;
    char caminho[20], buffer[10];

    cin >> caminho;

    ifstream txtFile;
    txtFile.open(caminho);

    if (!txtFile) {
        cout << "Nao foi possivel abrir o arquivo" << endl;
        exit(-1);
    }

    txtFile >> n; //guardando o primeiro valor do arquivo em 'n'

    //calculo do numero de arestas 'a'
    int a = (n-1)*n*0.5;

    //criando matriz n x n zerada (n qualquer)
    int **matriz = new int *[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int [n];

        for (int j = 0; j < n; j ++) {
                matriz[i][j] = 0;
        }
    }

    int peso[a]; //vetor de pesos com tamanho 'a'

    //guardando os pesos
    for (int i = 0; i < a; i++) {
        txtFile >> peso[i];
    }

    txtFile.close();

    //atribuindo os pesos a matriz de adjacencia
    int pos = 0;
    for (int i = 0; i < a; i++) {
        for (int j = i+1; j < n; j++) {
            matriz[i][j] = peso[pos];
            matriz[j][i] = peso[pos];
            pos++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    //dijkstra(matriz, n);


    return 0;
}
