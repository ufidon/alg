#include <iostream>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <string>
#include <sstream>

typedef int index;
typedef std::string keytype;
#define N 4

struct nodetype
{
	keytype key;
	nodetype* left;
	nodetype* right;
};

typedef nodetype* nodepointer;

void zero2d(int n,
	int d[][N + 1]) {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			d[i][j] = 0;
}

template <class T>
void zero2d(
	T d[][N + 1],
	index rlow,
	index rhigh,
	index clow,
	index chigh
) {
	for (int i = rlow; i <= rhigh; i++)
		for (int j = clow; j <= chigh; j++)
			d[i][j] = 0;
}

template <typename T>
void print2d(
	const T d[][N + 1],
	index rlow,
	index rhigh,
	index clow,
	index chigh
) {

	std::cout << std::left;

	for (int i = rlow; i <= rhigh; i++)
	{
		for (int j = clow; j <= chigh; j++)
			std::cout << std::setw(6) << d[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <class T>
void print1d(
	const T d[],
	index rlow,
	index rhigh
) {
	std::cout << std::left;

	for (int i = rlow; i <= rhigh; i++)
		std::cout << std::setw(6) << d[i];
	std::cout << std::endl;
}

double sum(
	const double p[],
	index low,
	index high
) {
	double s = 0.0;
	for (int i = low; i <= high; i++)
	{
		s += p[i];
	}
	return s;
}

// algorithm 3.8 p122
// Determine the node containing a key in a bst, suppose the key is in the tree
bool search(
	nodepointer tree,
	keytype keyin,
	nodepointer& p, // the node contains the key
	int& depth
) {
	bool found = false;

	p = tree;
	depth = 0;
	while ((p != NULL) && !found)
	{
		if (p->key == keyin)
			found = true;
		else if (keyin < p->key)
			p = p->left, depth++;
		else
			p = p->right, depth++;
	}

	return found;
}

// algorithm 3.9 p127
// Determine an optimal bst for a set of keys, each with a given probability fo being the search key
void obst(
	int n, // n keys
	const double p[], // p[1..n], p[i] is the probability of searching for key i
	double& minavg, // average search time for an obst
	index R[][N + 1], // R[1..n+1][0..n], R[i][j] is the index of the key in the root of an obst containing the ith through the jth key
	double A[][N + 1] // A[1..n+1][0..n], solution constructor
) {
	index i, j, k, diagonal;

	for (i = 0; i <= n; i++)
	{
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
	}

	A[n + 1][n] = 0;
	R[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++)
		for (i = 1; i <= n - diagonal; i++)
		{
			j = i + diagonal;

			//  k=i to j, find min( A[i][k-1]+A[k+1][j] ) + sum_{m=i to j}pm

			A[i][j] = A[i][i - 1] + A[i + 1][j];
			R[i][j] = i;
			for (k = i + 1; k <= j; k++) {
				if (A[i][k - 1] + A[k + 1][j] < A[i][j]) {
					A[i][j] = A[i][k - 1] + A[k + 1][j];
					R[i][j] = k; // a value of k that gave the minimum
				}
			}

			A[i][j] += sum(p, i, j);
		}

	minavg = A[1][n];
}

// algorithm 3.10 p129
// build an obst = tree(1,n)
nodepointer tree(
	const keytype Key[], // Key[1..n], n keys in order
	const index R[][N + 1], // R[1..n+1][0..n], R[i][j] is the index of the key in the root of an obst containing the ith through the jth key
	index i,
	index j
) {
	index k;
	nodepointer p;

	k = R[i][j];
	if (k == 0)
		return NULL;
	else
	{
		p = new nodetype;
		p->key = Key[k];
		p->left = tree(Key, R, i, k - 1);
		p->right = tree(Key, R, k + 1, j);
		return p;
	}
}

void showtree(
	nodepointer tree
) {
	if (tree == NULL)
		return;
	else
	{
		std::cout << tree->key;
		if (tree->left || tree->right) {
			std::cout << "(";
			showtree(tree->left);

			if (tree->left && tree->right)
				std::cout << "-";

			showtree(tree->right);
			std::cout << ")";
		}
	}
}

int main()
{
	// example 3.9 p 129
	int n = N;
	// Key[1..n], p[1..n]
	keytype Key[N + 1] = { "", "Don","Isabelle","Ralph","Wally" };
	double p[N + 1] = { 0, 3.0 / 8, 3.0 / 8, 1.0 / 8, 1.0 / 8 };

	// A[1..n+1][0..n], R[1..n+1][0..n]
	double A[N + 2][N + 1];
	index R[N + 2][N + 1];
	zero2d(A, 0, n + 1, 0, n);
	zero2d(R, 0, n + 1, 0, n);

	double minavg = 0.0;

	obst(n, p, minavg, R, A);

	std::cout << "A=" << std::endl;
	print2d(A, 1, n + 1, 0, n);

	std::cout << "R=" << std::endl;
	print2d(R, 1, n + 1, 0, n);

	//build then print the obst
	nodepointer root = tree(Key, R, 1, N);
	showtree(root);

}