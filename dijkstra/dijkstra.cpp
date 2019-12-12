#include <iostream>
#include <climits>
#include <fstream>
#include <stdlib.h>
using namespace std;

//retorna o menor vertice atual (se ele nao foi visitado)
int findMinVert(int* distancia, bool* visitado, int n) {
    int minVert = -1;
    //verifica se o próximo vertice é menor que o menor vértice atual
    for (int i = 0; i < n; i++) {
        if(!visitado[i] && (minVert == -1 || distancia[i] < distancia[minVert])) {
            minVert = i;
        }
    }
    return minVert;
}

void dijkstra(int** arestas, int n){
    int* distancia = new int[n];
    bool* visitado = new bool[n];

    //INITIALIZE-SINGLE-SOURCE(G,s)
    //Inicializando as distancias (pos[0] = 0, demais posicoes = inf)
    for (int i = 0; i < n; i++) {
        distancia[i] = INT_MAX;
        visitado[i] = false;
    }
    distancia[0] = 0;

    //RELAX(u,v,w)
    //atribuindo a menor distancia a cada vertice
    for (int i = 0; i < n - 1; i++) {
        int minVert = findMinVert(distancia, visitado, n);
        //vertice atual recebe a flag de 'visitado'
        visitado[minVert] = true;
        for (int j = 0; j < n; j++) {
            //percorre toda os vertices da matriz
            if (arestas[minVert][j] != 0 && !visitado[j]) {
                //'dist' vai somando os caminhos
                int dist = distancia[minVert] + arestas[minVert][j];
                //se o caminho atual (soma dos caminhos) = 'dist'
                //for menor que a distancia atual do vertice distancia[j] <-> dist
                if (dist < distancia[j]) {
                    distancia[j] = dist;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i << " " << distancia[i] << endl;
    }
    delete [] visitado;
    delete [] distancia;

}

int main() {
    int n, a;
    char caminho[20];

    cout << "\t\tALGORITMO DE DIJKSTRA\n\n";
    cout << "Nome do arquivo> ";
    cin >> caminho;

    ////////////////////////LEITURA DE ARQUIVO///////////////////////////
    ifstream txtFile;
    txtFile.open(caminho);

    if (!txtFile) {
        cout << "Nao foi possivel abrir o arquivo" << endl;
        exit(-1);
    }

    txtFile >> n; //guardando o primeiro valor do arquivo em 'n'

    //calculo do numero de arestas 'a'
    a = (n-1)*n*0.5;

    //criando matriz n x n zerada (n qualquer)
    int** arestas = new int*[n];
    for (int i = 0; i < n; i++) {
        arestas[i] = new int[n];
        for (int j = 0; j < n; j++) {
            arestas[i][j] = 0;
        }
    }

    int peso[a]; //vetor de pesos com tamanho 'a'

    //guardando os pesos
    for (int i = 0; i < a; i++) {
        txtFile >> peso[i];
    }
    txtFile.close();
    //////////////////////////////////////////////////////////////////

    //atribuindo os pesos a matriz de adjacencia
    int pos = 0;
    for (int i = 0; i < a; i++) {
        for (int j = i+1; j < n; j++) {
            arestas[i][j] = peso[pos];
            arestas[j][i] = peso[pos];
            pos++;
        }
    }

    /*//TESTE: imprimindo matriz de adjacencia
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arestas[i][j] << " ";
        }
        cout << endl;
    }*/

    cout << endl << "Distancias" << endl;
    dijkstra(arestas, n);

    for (int i = 0; i < n; i++) {
        delete [] arestas[i];
    }
    delete [] arestas;

    return 0;
}
