#include <iostream>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <string>
#include <sstream>

// algorithm 3.1 p97
// count = 2(n choose k) - 1
int bin(int n, int k, int& count) {
	count++;

	if (k==0 || n==k)
		return 1;
	else
	{
		return bin(n - 1, k - 1, count) + bin(n - 1, k, count);
	}
}

// algorithm 3.2 p99
// passes = (2n-k+2)(k+1)/2
int bin(int n, int k, int& passes, int** B)
{
	int i, j;
	for(i=0; i<=n; i++)
		for (j = 0; j <= std::min(i, k); j++)
		{
			passes++;
			if (j == 0 || j == i)
				B[i][j] = 1;
			else
				B[i][j] = B[i - 1][j - 1] + B[i - 1][j];
		}

	return B[n][k];
}

void print2d(const int r,
	const int c,
	const int** d) {

	std::cout << std::left;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
			std::cout << std::setw(10) << d[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void zero2d(const int r,
	const int c,
	int** d) {
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			d[i][j] = 0;
}

int main()
{
	int n = 20, k = 10, count = 0;

	//bin(n, k, count);
 //   std::cout << "bin(" << n<<"," <<k <<") is called "<<count << " times" << std::endl;

	int r = n + 1, c = k + 1, passes = 0;
	int** B = new int* [r];
	for (int i = 0; i < r; i++)
	{
		B[i] = new int[c];
	}

	zero2d(r,c,B);

	bin(n, k, passes, B);
	print2d(r, c, (const int**)B);
	std::cout << "bin(" << n << "," << k << ") looped " << passes << " passes" << std::endl;

	for (int i = 0; i < r; i++)
	{
		delete[] B[i];
	}
	delete[] B;
}

