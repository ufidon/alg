#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

// #define N 4
// const int N=4;
int N = 4;
// int 列[N + 1]; // 列[1..N]

vector<int> 列;

int 解号 = 0;
int 总解数 = 0;
int 检点数 = 0;
int 有戏点数 = 0;
int 试次 = 0;

void 印排布()
{
    for (int 行号 = 1; 行号 <= N; 行号++)
    {
        for (int 列号 = 1; 列号 <= N; 列号++)
            cout << (列[行号] == 列号 ? "|♕" : "|-");

        cout << "|" << endl;
    }
    cout << endl;
}

bool 有戏(int 本行)
{
    int 前行;
    bool 无冲突;

    前行 = 1;
    无冲突 = true;

    while (前行 < 本行 && 无冲突)
    {
        if (列[本行] == 列[前行] || abs(列[本行] - 列[前行]) == 本行 - 前行)
            无冲突 = false;
        前行++;
    }
    return 无冲突;
}

bool 都有戏(int 本行)
{
    for (int 行 = 2; 行 <= 本行; 行++)
    {
        if (!有戏(行))
        {
            return false;
        }
    }
    return true;
}

int 昨行 = 0;
string 进退[2] = {"进", "退"};
// 回溯1
void 排皇后(int 本行)
{
    int 列号;

    if (有戏(本行)) // 本行放皇后,与前面行的皇后都没冲突
    {

        有戏点数++;
        if (本行 == N)
        {
            cout << "成:";
            总解数++;
            cout << "第" << ++解号 << "号解" << endl;
            印排布();
        }
        else
            for (列号 = 1; 列号 <= N; 列号++)
            {
                检点数++;
                列[本行 + 1] = 列号;
                int 向 = (昨行 > 本行 + 1);
                昨行 = 本行 + 1;
                cout << 进退[向] << "(" << (本行 + 1) << "," << 列号 << ")";
                fill(列.begin() + 本行 + 2, 列.end(), 0);

                cout << (有戏(本行 + 1) ? "√ " : "✕ ");
                cout << "第" << ++试次 << "次尝试" << endl;
                印排布();
                排皇后(本行 + 1);
            }
    }
}

// 回溯1, 课本210页
void 排皇后1(int 本行)
{
    int 列号;
    for (列号 = 1; 列号 <= N; 列号++)
    {
        if (有戏(本行)) // 本行放皇后,与前面行的皇后都没冲突
        {

            有戏点数++;
            if (本行 == N)
            {
                cout << "成:";
                总解数++;
                cout << "第" << ++解号 << "号解" << endl;
                印排布();
            }
            else
            {
                检点数++;
                列[本行 + 1] = 列号;
                int 向 = (昨行 > 本行 + 1);
                昨行 = 本行 + 1;
                cout << 进退[向] << "(" << (本行 + 1) << "," << 列号 << ")";
                fill(列.begin() + 本行 + 2, 列.end(), 0);

                cout << (有戏(本行 + 1) ? "√ " : "✕ ");
                cout << "第" << ++试次 << "次尝试" << endl;
                印排布();
                排皇后(本行 + 1);
            }
        }
    }
}

// 遍历,穷尽
void 遍历棋盘(int 本行)
{
    int 列号;

    if (本行 == N)
    {
        if (都有戏(本行))
        {
            cout << "成:";
            总解数++;
            cout << "第" << ++解号 << "号解" << endl;
            印排布();
        }
    }
    else
        for (列号 = 1; 列号 <= N; 列号++)
        {
            检点数++;
            列[本行 + 1] = 列号;
            int 向 = (昨行 > 本行 + 1);
            昨行 = 本行 + 1;
            cout << 进退[向] << "(" << (本行 + 1) << "," << 列号 << ")";
            fill(列.begin() + 本行 + 2, 列.end(), 0);
            bool 无冲突 = 都有戏(本行 + 1);
            if (无冲突)
                有戏点数++;
            cout << (无冲突 ? "√ " : "✕ ");
            cout << "第" << ++试次 << "次尝试" << endl;
            印排布();
            遍历棋盘(本行 + 1);
        }
}

int 随机估点(int 行数)
{
    int 本行, 列号;
    vector<int> 列(行数 + 1); // 列[1..行数]
    int 有戏点数, 有戏点数积, 总点数;
    vector<int> 有戏子集;

    本行 = 0, 总点数 = 1, 有戏点数 = 1, 有戏点数积 = 1;

    while (有戏点数 != 0 && 本行 != 行数)
    {
        有戏点数积 *= 有戏点数;
        总点数 += 有戏点数积 * 行数;
        本行++;

        有戏点数 = 0;
        有戏子集.clear();
        for (列号 = 1; 列号 <= 行数; 列号++)
        {
            列[本行] = 列号;
            if (有戏(本行))
            {
                有戏点数++;
                有戏子集.push_back(列号);
            }
        }
        if (有戏点数 != 0)
        {
            列号 = 有戏子集[rand() % 有戏子集.size()];
            // cout << "随机列号: " << 列号 << endl;
            列[本行] = 列号;
        }
    }
    return 总点数;
}

int main(int argc, char *argv[])
{
    stringstream ss(argv[1]);
    int n;
    ss >> n;

    N = n;
    列 = vector<int>(N + 1, 0);
    srand(time(0));

    // 排皇后(0);
    排皇后1(0);
    //遍历棋盘(0);
    cout << "有戏点数: " << 有戏点数 << ", "
         << "检点数: " << 检点数 << ", "
         << "总解数: " << 总解数 << endl;

    cout << n << "x" << n << "棋盘随机估计有戏点均数: " << 随机估点(n) << endl;
}