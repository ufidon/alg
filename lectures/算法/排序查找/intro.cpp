// c++ implementation of the algorithms from the textbook
// Foundations of Algorithms by Richard E. Neopolitan

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

// common dataype and function
typedef int index;
typedef int keytype;
typedef int number;

void copyarray(const keytype src[], keytype dst[], const int size) {
	for (index i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

void printarray(const keytype a[], const int low, const int high) {
	std::cout << std::left;
	std::cout << std::setw(10) << "Index: ";
	for (int i = low; i <= high; i++)
		std::cout << std::setw(6) << i;
	std::cout << std::endl;
	std::cout << std::setw(10) << "Element: ";
	for (int i = low; i <= high; i++)
		std::cout << std::setw(6) << a[i];
	std::cout << std::endl;
}

void printarray(const keytype a[], const int n) {
	std::cout << std::left;
	std::cout << std::setw(10) << "Index: ";
	for (int i = 1; i <= n; i++)
		std::cout << std::setw(6) << i;
	std::cout << std::endl;
	std::cout << std::setw(10) << "Element: ";
	for (int i = 1; i <= n; i++)
		std::cout << std::setw(6) << a[i];
	std::cout << std::endl;
}

// algorithm 1.1 p4
void seqsearch(const int n,
	const keytype S[], // size needs to be n+1
	keytype x,
	index& location) {
	location = 1;
	while (location <= n && S[location] != x)
	{
		location++;
	}
	if (location > n) {
		location = 0;
		std::cout << x << " is not found" << std::endl;
	}
	else
		std::cout << x << " is found at location " << location << std::endl;
}


// alogrithm 1.2 p7
int sum(const int n,
	const number S[]// size needs to be n+1
) {
	index i;
	number result = 0;

	for (i = 1; i <= n; i++)
		result += S[i];

	return result;
}

// algorithm 1.3 p8
void exchangesort(const int n,
	keytype S[] // size needs to be n+1
) {
	index i, j;
	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
		{
			if (S[j] < S[i])
			{
				// exchange S[j], S[i]
				std::swap(S[j], S[i]);
			}
		}
}

// algorithm 1.4 p9
#define N 2

// indexes all start from 1
void matrixmult(const int n,
	const number A[][N + 1],
	const number B[][N + 1],
	number C[][N + 1]
) {
	index i, j, k;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) {
			C[i][j] = 0;
			for (k = 1; k <= n; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
}

void print2d(const int n,
	const number d[][N + 1] // (n+1)x(n+1) square matrix
) {

	std::cout << std::left;

	//print column indexes
	std::cout << std::setw(6) << "i\\j";
	for (int i = 1; i <= n; i++)
		std::cout << std::setw(6) << i;
	std::cout << std::endl;

	for (int i = 1; i <= n; i++)
	{
		std::cout << std::setw(6) << i; // print row indexes
		for (int j = 1; j <= n; j++)
			std::cout << std::setw(6) << d[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// algorithm 1.5 p10

void binsearch(int n,
	const keytype S[], // size needs to be n+1
	keytype x,
	index& location) {
	index low, high, mid;
	low = 1, high = n;
	location = 0;

	while (low <= high && location == 0)
	{
		mid = (low + high) / 2;
		if (x == S[mid]) {
			location = mid;
			std::cout << x << " is found at location " << location << std::endl;
			return;
		}

		else if (x < S[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	std::cout << x << " is not found" << std::endl;
}

// algorithm 1.6 p13
int fib(int n,
	int& terms
) {
	terms++;
	if (n <= 1)
		return n;
	else
		return fib(n - 1, terms) + fib(n - 2, terms);
}

// algorithm 1.7 p16
int fib(int n, 
	int f[] // size needs to be n+1
)
{
	index i;
	f[0] = 0;
	f[1] = 1;
	if (n >= 2) {
		
		for ( i = 2; i <= n; i++)
		{
			f[i] = f[i - 1] + f[i - 2];
		}
	}
	return f[n];
}


int main()
{
	// ----------seqsearch & exchangesort--------------
	//int n = 10, x1 = 7, x2 = 20;
	//int* S = new int[n + 1]{ 0,3,9,8,6,4,10,5,7,11,1 };

	//std::cout << "Test seqsearch, given sequence:\n";
	//printarray(S, 1, n);

	//int loc = 0;
	//seqsearch(n, S, x1, loc);
	//seqsearch(n, S, x2, loc);

	//exchangesort(n, S);
	//std::cout << "Sorted array in increasing order:" << std::endl;
	//printarray(S, 1, n);

	//delete[] S;

	// --------matrixmult-------------
	/*int n = N;
	const number A[N+1][N+1] = {
		{0,0,0},
		{0,2,3},
		{0,4,1}
	};
	const number  B[N + 1][N + 1] = {
		{0,0,0},
		{0,5,7},
		{0,6,8}
	};

	number C[N + 1][N + 1] = {
		{0,0,0},
		{0,5,7},
		{0,6,8}
	};

	matrixmult(n, A, B, C);


	print2d(n, A);
	std::cout << " x \n";
	print2d(n, B);
	std::cout << " = \n";
	print2d(n, C);*/


	//--------binsearch-------------
	//int n = 10, x1 = 7, x2 = 20;
	//int* S = new int[n + 1]{ 0,3,9,8,6,4,10,5,7,11,1 };

	//std::cout << "Test binsearch, given sequence:\n";
	//printarray(S, 1, n);
	//exchangesort(n, S);
	//std::cout << "Sorted array in increasing order:" << std::endl;
	//printarray(S, 1, n);

	//int loc = 0;
	//binsearch(n, S, x1, loc);
	//binsearch(n, S, x2, loc);

	//delete[] S;

	//---------------fib recursive-------------------
	//int terms = 0;
	//std::cout << std::left;
	//std::cout << std::setw(5) << "n" << std::setw(16) << "#terms computed" << std::endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	terms = 0;
	//	std::cout << std::setw(5) << i;
	//	fib(i, terms);
	//	std::cout << std::setw(16) << terms << std::endl;
	//}


	//---------------fib iterative-----------------
	int n = 20;
	int f[21];
	fib(n, f);
	printarray(f, 0, n);

}

