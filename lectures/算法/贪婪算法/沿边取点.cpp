#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

// 最小支撑树贪婪算法一：沿捷取点（Prim算法）
// 图=（点集，边集），最小支撑树 = （点集，边集）
// 最小支撑树始于图之任一点，沿捷径吞图之点，止于吞完
// 捷径 = 最小支撑树点集至图点集之最短边

// {树点集：桩点}--捷径--{靶点：待吞图点集}
// 待吞图点集即剩余图点集
// #define D点数   5
typedef pair<int, int> 边;

void 印阵(int n, // 行列数
        int 始号,
    vector<vector<double>> &邻距) {

    std::cout << std::left;

    for (int i = 始号;  i <= n;  i++)
    {
        for (int j = 始号; j <= n; j++)
            if (std::isinf(邻距[i][j]))
                std::cout << std::setw(4) << "∞";
            else
                std::cout << std::setw(2) << 邻距[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void 印阵(int n, // 行列数
        int 始号,
    vector<vector<int>> &邻距) {

    std::cout << std::left;

    for (int i = 始号; i <= n; i++)
    {
        for (int j = 始号; j <= n; j++)
               std::cout << std::setw(2) << 邻距[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void 沿捷取点(const int 点数,
              const int 始号,
              const vector<vector<double>> &邻距,
              vector<边> &树边集,
              double &全重)
{
    int 靶号;
    double 捷径长;
    边 捷径;
    int 桩号集[点数 + 1];    // [2..点数]
    double 桩靶距[点数 + 1]; // [2..点数]

    // 从始号出发
    靶号 = 始号;
    全重 = 0;
    // 点号集
    vector<int> 点号集(点数);
    iota(点号集.begin(), 点号集.end(), 1);   // 初设(1..点数)
    点号集.erase(点号集.begin() + 始号 - 1); // 移除始号

    for (int i : 点号集)
    {
        桩号集[i] = 始号;
        桩靶距[i] = 邻距[始号][i];
    }

    // 沿捷径吞其余图点
    int 回合数 = 1;
    cout << "第" << 回合数 << "回合：始于点" << 始号 << endl;

    while (回合数 < 点数)
    {
        捷径长 = INFINITY;
        for (int i : 点号集)
        {
            if (桩靶距[i] >= 0 && 桩靶距[i] < 捷径长)
            {
                捷径长 = 桩靶距[i];
                靶号 = i;
            }
        }
        捷径 = make_pair(桩号集[靶号], 靶号);
        树边集.push_back(捷径);
        桩靶距[靶号] = -1;

        for (int i : 点号集)
        {
            if (邻距[i][靶号] < 桩靶距[i])
            {
                桩靶距[i] = 邻距[i][靶号];
                桩号集[i] = 靶号;
            }
        }

        全重 += 捷径长;
        回合数++;
        cout << "第" << 回合数 << "回合：" << endl;
        cout << "捷径：（" << 捷径.first << "," << 捷径.second << "）" << endl;
        cout << "捷距：" << 捷径长 << endl;
        cout << "吞点: " << 靶号 << endl;
    }
}

int main()
{
    int 点数 = 5, 始号 = 1;
    vector<vector<double>> 邻距 = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 3, INFINITY, INFINITY},
        {0, 1, 0, 7, 6, INFINITY},
        {0, 3, 7, 0, 4, 2},
        {0, INFINITY, 6, 4, 0, 5},
        {0, INFINITY, INFINITY, 2, 5, 0}};

    印阵(点数, 1, 邻距);
    vector<边> 树边集;
    double 全重 = 0;

    for (始号 = 1; 始号 <= 点数; 始号++)
    {
        cout << "\n==================================\n"
             << endl;
        沿捷取点(点数, 始号, 邻距, 树边集, 全重);
        for (int i = 0; i < 树边集.size(); i++)
        {
            cout << "(" << 树边集[i].first << "," << 树边集[i].second << ")" << endl;
        }
        树边集.clear();
        cout << "最小支撑树全重： " << 全重 << endl;
    }
}