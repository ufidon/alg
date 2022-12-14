#include <iostream>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <string>
#include <sstream>

typedef int index;
#define N 6

void zero2d(int n,
    int d[][N + 1]) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            d[i][j] = 0;
}

void print2d(int n,
    const int d[][N + 1]) {

    std::cout << std::left;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
            std::cout << std::setw(6) << d[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// algorithm 3.6 p117
// find the minimum number of multiplications for multiplying matrix A1 through An
int minmult(
	const int n, // matrices # = N
	const int d[], // indexed from 0 to n, dim(matrix i) = rows x cols = d[i-1] x d[i]
	int M[][N+1], // solution constructor, indexes from 1 to n, minimum number of multiplications for multiplying matrix Ai through Aj
	index P[][N + 1] // indexes from 1 to n, P[i][j] is the point where matrices i through j are split in an optimal order for multiplying the matrices
) {
	index i, j, k, diagonal;

    for (i = 1; i <= n; i++)
        M[i][i] = 0;

    for(diagonal=1; diagonal <= n-1; diagonal++)
        for (i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            // k from i to j-1, find min(M[i][k]+M[k+1][j]+d[i-1]*d[k]*d[j])
            P[i][j] = i;
            M[i][j] = M[i][i] + M[i + 1][j] + d[i - 1] * d[i] * d[j];
            for (k = i+1; k <=j-1 ; k++)
            {
                if (M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j] < M[i][j])
                {
                    M[i][j] = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
                    P[i][j] = k; // the value of k that gave the minimum
                }
            }
        }
    return M[1][n];
}

// algorithm 3.7 p120
// print optimal order
void order(const index P[][N+1],
    index i, index j) 
{
    if (i == j)
        std::cout << "A" << i;
    else
    {
        index k = P[i][j];
        std::cout << "(";
        order(P, i, k);
        order(P, k + 1, j);
        std::cout << ")";
    }
}

int main() {
    // Example 3.5 p114
    // A1(5x2)A2(2x3)A3(3x4)A4(4x6)A5(6x7)A6(7x8)
    int n = N;
    int d[N + 1] = { 5,2,3,4,6,7,8 };
    int M[N + 1][N + 1], P[N+1][N+1];
    zero2d(n, M), zero2d(n, P);

    minmult(n, d, M, P);

    std::cout << "M=" << std::endl;
    print2d(n, M);

    std::cout << "P=" << std::endl;
    print2d(n, P);

    std::cout << "several optimal orders:" << std::endl;
    order(P, 1, n);
    std::cout << std::endl;
    order(P,2, n);
    std::cout << std::endl;
    order(P,2, 5);
}