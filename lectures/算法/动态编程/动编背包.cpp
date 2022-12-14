#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

typedef struct
{
    int 号;
    int 价;
    int 重;
} 宝;

bool 比价(宝 甲, 宝 乙)
{
    return (甲.价 < 乙.价);
}

bool 比重(宝 甲, 宝 乙)
{
    return (甲.重 < 乙.重);
}

bool 比单价(宝 甲, 宝 乙)
{
    return (甲.价 / 甲.重 < 乙.价 / 乙.重);
}

void 印宝(const vector<宝> 宝列)
{
    int 总价 = 0, 总重 = 0;
    cout << "宝物: " << endl;

    for (auto b : 宝列)
    {
        总价 += b.价;
        总重 += b.重;
        cout << "[" << b.号 << "(" << b.价 << "," << b.重 << ")"
             << "] ";
    }
    cout << endl;
    cout << "总价: " << 总价 << ", 总重: " << 总重 << endl;
}

// 0-1 背包问题: 每宝整块拿
// 有宝几许,各重i,值钱i,背包承重有限,如何取物使价值最大
// 动态编程, 重量和价格都需为整数
// 动态编程算法 1: 每项都算

// 动态编程算法 2: 只算需要的
vector<int> p;
vector<int> w;

int P(const int n, const int W)
{
    if (n == 0 || W == 0)
    {
        cout << "P[" << n << "," << W << "]=0" << endl;
        return 0;
    }
    else
    {
        if (w[n] > W)
        {
            int r = P(n - 1, W);
            printf("w[%d]=%d>W=%d: ", n, w[n], W);
            printf("P[%d][%d]=%d\n", n - 1, W, r);
            return r;
        }
        else
        {
            int r1 = P(n - 1, W);
            int r2 = P(n - 1, W - w[n]);
            int r = max(r1, p[n] + r2);
            printf("w[%d]=%d≤W=%d: ", n, w[n], W);
            printf("p[%d]=%d, w[%d]=%d, P[%d][%d]=%d, P[%d][%d]=%d: ", n, p[n], n, w[n], n - 1, W, r1, n - 1, W - w[n], r2);
            printf("max{P[%d][%d], p[%d] + P[%d][W-w[%d]]}=%d\n", n - 1, W, n, n - 1, n, r);
            return r;
        }
    }
}

int main()
{
    int W = 30, n = 3;
    p = vector<int>{0, 50, 60, 140};
    w = vector<int>{0, 5, 10, 20};

    cout << P(n, W) << endl;
}
