/*
UFPB - CENTRO DE INFORMÁTICA

Disciplina: Ordenação e Recuperação de Dados
Aluno: André Gomes Passos
Matrícula: 20190171426

PROGRAMA: INSERTION SORT IMPLEMENTADO COM LIST
*/

#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>
using namespace std;

int main() {
    char resposta = 's';

    while(resposta == 's' || resposta == 'S') {
        list<int> lista1, lista2;
        list<int>::iterator it, it2, pos_menor;

        system("cls"); //limpar tela no windows
        cout << "PROGRAMA QUE REALIZA O INSERTION SORT NUMA LISTA DE NUMEROS INTEIROS ALEATORIOS\n\n";
        srand(time(NULL)); //seed para rand() baseada no relogio do SO

        //inicializa a lista1 com valores aleatorios
        for (int i = 0; i < 20; i++) lista1.push_back(rand()%100);

        //imprime todos os valores da lista original
        cout << "Lista Original:";
        for (it = lista1.begin(); it!=lista1.end(); ++it)
            cout << ' ' << *it;
        cout << '\n';

        lista2.push_back(100); //necessario para que todos os valores entrem na lista
                               //e para que a lista2 nao esteja vazia no segundo for

        //loop que vai jogando os valores da lista1 na lista2 e, antes de jogar,
        //verifica em qual posicao ele deve entrar
        for (it = lista1.begin(); it!=lista1.end(); ++it) {
            for (it2 = lista2.begin(); it2!=lista2.end(); ++it2) {
                if (*it2 > *it) {
                    lista2.insert(it2, *it); //insere em it2 o conteudo apontado por *it
                                             //e 'afasta' o resto dos elementos pra frente
                    break;
                }
            }
        }
        lista2.remove(100); //como o 100 nao faz parte da lista original, ele é
                            //removido apos a ordenacao

        cout << "Lista Ordenada:";
        for (it = lista2.begin(); it!=lista2.end(); ++it)
            cout << ' ' << *it;
        cout << endl << endl;

        cout << "Deseja executar o programa novamente?(S/N) ";
        cin >> resposta;
    }

    return 0;
}
