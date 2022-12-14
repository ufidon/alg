/*

1. [Change default code page of Windows console to UTF-8](https://superuser.com/questions/269818/change-default-code-page-of-windows-console-to-utf-8)
*/

#include <iostream>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <string>
#include <sstream>

typedef int index;

#define N 5

void copy2d(int n,
    const double W[][N + 1],
    double D[][N + 1]) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            D[i][j] = W[i][j];
}

void zero2d(int n,
    double d[][N + 1]) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            d[i][j] = 0.0;
}
void zero2d(int n,
    int d[][N + 1]) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            d[i][j] = 0;
}

void print2d(int n,
    const double d[][N + 1]) {

    std::cout << std::left;

    for (int i = 1;  i <= N;  i++)
    {
        for (int j = 1; j <= N; j++)
            if (std::isinf(d[i][j]))
                std::cout << std::setw(8) << "∞";
            else
                std::cout << std::setw(6) << d[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
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

// algorithm 3.3 p106
void floyd(int n,
    const double W[][N + 1],
    double D[][N+1])
{
    int i, j, k;
    copy2d(n, W, D);
    std::cout << "D(0) = " << std::endl;
    print2d(n, D);

    for (k = 1; k <= n; k++) {
        std::cout << "D(" << k << ")=" << std::endl;
        for(i=1; i<=n; i++)
            for ( j = 1; j <= n ; j++)
            {
                D[i][j] = std::min<double>(D[i][j], D[i][k] + D[k][j]);
            }
        print2d(n, D);
    }

}

// algorithm 3.4 p107
void floyd(int n,
    const double W[][N + 1],
    double D[][N + 1],
    int P[][N + 1]
) {
    int i, j, k;
    zero2d(n, P);

    copy2d(n, W, D);
    std::cout << "D(0) = " << std::endl;
    print2d(n, D);
    for (k = 1; k <= n; k++) {
        std::cout << "D(" << k << ")=" << std::endl;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    P[i][j] = k;
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        print2d(n, D);
    }
    std::cout << "P = " << std::endl;
    print2d(n, P);
}


//int P[6][6] = {
//    {0,0,0,0,0,0},
//    {0,0,0,4,0,4},
//    {0,5,0,0,0,4},
//    {0,5,5,0,0,4},
//    {0,5,5,0,0,0},
//    {0,0,1,4,1,0}
//};



// algorithm 3.5 p109
void path(const int P[][N+1], index f, index t) {
    if (P[f][t] != 0) {
        path(P, f, P[f][t]);
        std::cout << " v" << P[f][t];
        path(P, P[f][t], t);
    }
}

double W[N + 1][N + 1] = {
    {0,0,0,0,0,0},
    {0,0,1,INFINITY,1,5},
    {0,9,0,3,2,INFINITY},
    {0,INFINITY,INFINITY,0,4,INFINITY},
    {0,INFINITY,INFINITY,2,0,3},
    {0,3,INFINITY,INFINITY,INFINITY,0}
};
double D[N + 1][N + 1];
int P[N + 1][N + 1];

int main()
{


    //--------test floyd--------------------------------
    //floyd(5, W, D);
    floyd(N, W, D, P);
    //path(P, 5, 3);

    std::cout << "Print shortest path" << std::endl;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            std::cout << "(" << i << "," << j << "):" << std::endl;
            path(P, i, j);
            std::cout << std::endl;
        }

    }

}


