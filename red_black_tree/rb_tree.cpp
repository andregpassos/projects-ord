/*
UFPB - CENTRO DE INFORMÁTICA

Disciplina: Ordenação e Recuperação de Dados
Aluno: André Gomes Passos
Matrícula: 20190171426

PROGRAMA: RED-BLACK TREE DINAMICA PREENCHIDA POR INTEIROS ALEATÓRIOS

Credits to: geeksforgeeks.org
*/

#include "gen_aleat_vector.h"
#include <fstream>
#include <queue>
using namespace std;
#define MAX 10000000 // max value = 10.000.000 (ten millions)

enum Color {RED, BLACK};

struct Node
{
	int key;
	bool color;
	Node *left, *right, *parent;

	// Constructor
	Node(int key)
	{
	this->key = key;
	left = right = parent = NULL;
	this->color = RED;
	}
};

// Class to represent Red-Black Tree
class RBTree
{
private:
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixViolation(Node *&, Node *&);
public:
	// Constructor
	RBTree() { root = NULL; }
	void insert(const int &n);
	void inOrder(Node *root, bool screen);
	void levelOrder(Node *root, bool screen);
	Node* getRoot();
	Node* search_key(int key, Node* n);
};

Node* RBTree::getRoot() {
    return root;
}

// A recursive function to do level order traversal
void RBTree::inOrder(Node *root, bool screen)
{
	if (root == NULL)
		return;

    if (screen) {
        inOrder(root->left, true);
        cout << root->key << " ";
        inOrder(root->right, true);
    } else {
        ofstream in_order;
        in_order.open("in_order.txt", ios::app);
        inOrder(root->left, false);
        in_order << root->key << endl;
        inOrder(root->right, false);
    }
}

// Utility function to do level order traversal
void RBTree::levelOrder(Node *root, bool screen)
{
	if (root == NULL)
		return;

	std::queue<Node *> q;
	q.push(root);

	while (!q.empty())
	{
		Node *temp = q.front();
		if (screen)
            cout << temp->key << " ";
        else {
            ofstream level_order;
            level_order.open("level_order.txt", ios::app);
            level_order << temp->key << endl;
        }
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED))
	{

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/* Case : A
			Parent of pt is left child of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left)
		{

			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			The uncle of pt is also red
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else
			{
				/* Case : 2
				pt is right child of its parent
				Left-rotation required */
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is left child of its parent
				Right-rotation required */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		Parent of pt is right child of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color == RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is right child of its parent
				Left-rotation required */
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

/* A utility function to insert a new node with given key
in BST */
Node* BSTInsert(Node* root, Node *pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
	return pt;

	/* Otherwise, recur down the tree */
	if (pt->key < root->key)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->key > root->key)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

// Function to insert a new node with given key
void RBTree::insert(const int &key)
{
	Node *pt = new Node(key);

	// Do a normal BST insert
	root = BSTInsert(root, pt);

	// fix Red Black Tree violations
	fixViolation(root, pt);
}

Node* RBTree::search_key(int key, Node* n){
    if(n == NULL || key == n->key)
    	return n;
    if(key > n->key)
        return search_key(key, n->right);
    if(key < n->key)
        return search_key(key, n->left);
}

int main()
{
    char resposta = 's';

    while(resposta == 's' || resposta == 'S') {
        system("cls");
        char tela_ou_arq;
        unsigned int n_ints;
        char resp;
        cout << "PROGRAMA PARA INSERCAO EM ARVORES VERMELHO-PRETO (RB TREE) UTILIZANDO NUMEROS INTEIROS ALEATORIOS\n\n";

        RBTree tree;

        cout << "Quantidade de inteiros a ser inserida na arvore (ate 10 milhoes): ";
        cin >> n_ints;

        if (n_ints > MAX) {
            n_ints = MAX;
            cout << "Quantidade de inteiros lida = 10.000.000!\n\n";
        }

        // gerando valores aleatorios e guardando em 'rand_vector'
        vector<int> rand_vector = gen_alt_vec(n_ints);

        // inserindo valores de 'rand_vector' na arvore
        cout << "Inserindo numeros aleatorios na arvore ..." << endl;
        for (int i = 0; i < n_ints; i++)
            tree.insert(rand_vector[i]);

        cout << "Deseja imprimir os valores da arvore?(S/N) ";
        cin >> resp;

        if (resp == 's' || resp == 'S') {
            cout << endl << "Digite 't' para imprimir na tela ou 'a' para imprimir no arquivo" << endl;

            bool volta = true;
            // loop para tratamento de erro de usuario
            while (volta) {
                cin >> tela_ou_arq;

                // impressao dos valores na tela (prompt)
                if (tela_ou_arq == 't' || tela_ou_arq == 'T') {
                    cout << "\n> Valores da arvore em ordem crescente:" << endl;
                    tree.inOrder(tree.getRoot(), true);
                    cout << "\n> Valores da arvore em ordem de nivel (da raiz ate as folhas):" << endl;
                    tree.levelOrder(tree.getRoot(), true);
                    volta = false;
                }
                // impressao dos valores num arquivo do tipo 'txt'
                else if (tela_ou_arq == 'a' || tela_ou_arq == 'A') {
                    remove("in_order.txt");
                    remove("level_order.txt");
                    cout << "\t> Escrevendo nos arquivos de saida ...\n\n";
                    ofstream out1("in_order.txt");
                    ofstream out2("level_order.txt");
                    out1 << n_ints << endl;
                    out2 << n_ints << endl;
                    cout << "\t> Gerando 'in_order.txt' ...\n";
                    //cout << tree.getRoot()->key << endl << tree.getRoot()->color <<endl;
                    tree.inOrder(tree.getRoot(), false);
                    cout << "\t>'in_order.txt' criado com sucesso!\n";
                    cout << "\t> Gerando 'level_order.txt' ...\n";
                    //cout << tree.getRoot()->key << endl << tree.getRoot()->color <<endl;
                    tree.levelOrder(tree.getRoot(), false);
                    cout << "\t>'level_order.txt' criado com sucesso!\n";
                    volta = false;
                }
                else {
                    cout << "\nDigite 'a' ou 't'!\n";
                }
            }
        }

        resp = 's';
        while(resp == 's' || resp == 'S') {
            int chave;
            string cor;
            cout << "\nInforme uma chave a ser buscada na arvore (valor inteiro):\n\n";
            cin >> chave;

            // busca o nó referente à chave fornecida pelo usuario e o armazena em 'no'
            Node *no = tree.search_key(chave, tree.getRoot());

            if (no == NULL)
                cout << "Chave nao encontrada!\n";
            else {
                cout << "Informacoes do no buscado:" << endl << endl;
                cout << "-> No buscado:" << endl;
                cout << "\t-> Chave: " << no->key << endl;
                if (no->color == 1)
                    cor = "preto";
                else
                    cor = "vermelho";
                cout << "\t-> Cor: " << cor << endl;
                if (no->right) {
                    cout << "-> No da direita:" << endl;
                    cout << "\t-> Chave: " << no->right->key << endl;
                    if (no->right->color == 1)
                        cor = "preto";
                    else
                        cor = "vermelho";
                    cout << "\t-> Cor: " << cor << endl;
                } else {
                    cout << "-> No da direita nao existe!" << endl;
                }
                if (no->left) {
                    cout << "-> No da esquerda:" << endl;
                    cout << "\t-> Chave: " << no->left->key << endl;
                    if (no->left->color == 1)
                        cor = "preto";
                    else
                        cor = "vermelho";
                    cout << "\t-> Cor: " << cor << endl;
                } else {
                    cout << "-> No da esquerda nao existe!" << endl;
                }
                if (no->parent) {
                    cout << "-> No pai:" << endl;
                    cout << "\t-> Chave: " << no->parent->key << endl;
                    if (no->parent->color == 1)
                        cor = "preto";
                    else
                        cor = "vermelho";
                    cout << "\t-> Cor: " << cor << endl;

                    if (no->parent->right == no)
                        cout << "-> Esse eh o filho a direita do pai" << endl;
                    else if (no->parent->left == no)
                        cout << "-> Esse eh o filho a esquerda do pai" << endl;
                } else {
                    cout << "-> Esse eh o no raiz!" << endl;
                }
            }
            cout << "Deseja buscar outra chave na arvore?(S/N) ";
            cin >> resp;
        }

        cout << endl << "Deseja executar o programa novamente?(S/N) ";
        cin >> resposta;
    }

	return 0;
}
