#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

// 独源捷径贪婪算法一：沿捷达的（Dijkastra算法）
// 图 =（点集，边集），独源捷径 = (边集）
// 取图任一点为始，沿捷径达其余各点, 得众捷径

typedef struct
{
    int 从;
    int 到;
} 边;
typedef struct
{
    int 靶;
    double 始靶距;
} 捷径;

void 印阵(int n, // 行列数
          int 始号,
          vector<vector<double>> &图)
{

    cout << left;

    for (int i = 始号; i <= n; i++)
    {
        for (int j = 始号; j <= n; j++)
            if (isinf(图[i][j]))
                cout << setw(4) << "∞";
            else
                cout << setw(2) << 图[i][j];
        cout << endl;
    }
    cout << endl;
}

void 印阵(int n, // 行列数
          int 始号,
          vector<vector<int>> &图)
{

    cout << left;

    for (int i = 始号; i <= n; i++)
    {
        for (int j = 始号; j <= n; j++)
            cout << setw(2) << 图[i][j];
        cout << endl;
    }
    cout << endl;
}

template <typename T>
void 印列(const vector<T> &列)
{
    cout << "[";
    for (size_t i = 0; i < 列.size(); i++)
    {
        cout << 列[i] << (i == 列.size() - 1 ? "]" : ",");
    }
}

void 独源捷径(const int 点数,
              const int 始号,
              const vector<vector<double>> &图,
              vector<边> &捷边集,
              vector<捷径> 靶距集)
{
    int 靶号, 前桩;
    边 锋边;
    double 捷长 = INFINITY;
    // int 桩号集[点数 + 1];    // [1..点数]
    // double 始靶长[点数 + 1]; // [1..点数]
    vector<int> 桩号集(点数 + 1);    // [1..点数]
    vector<double> 始靶长(点数 + 1); // [1..点数]

    // 从始号出发
    // 靶号集
    vector<int> 靶号集(点数);
    iota(靶号集.begin(), 靶号集.end(), 1);   // 初设(1..点数)
    靶号集.erase(靶号集.begin() + 始号 - 1); // 移除始号

    cout << 始号 << "->";
    印列(靶号集);
    cout << endl;
    for (int 靶号 : 靶号集)
    {
        桩号集[靶号] = 始号;
        始靶长[靶号] = 图[始号][靶号];
    }
    前桩=靶号集[0];

    cout << "桩号集:";
    印列(桩号集);
    cout << endl;
    cout << "靶号集:";
    印列(靶号集);
    cout << endl;
    cout << "\n"
         << endl;

    // 自始点沿捷径至其余图点
    int 回合数 = 1;
    while (回合数 < 点数) // 共"点数-1"回
    {
        cout << "第" << 回合数 << "回合:";
        捷长 = INFINITY;
        for (int 靶号 : 靶号集)
        {
            if (0 <= 始靶长[靶号] && 始靶长[靶号] < 捷长)
            {
                捷长 = 始靶长[靶号];
                前桩 = 靶号;
                cout << "(" << 前桩 << "," << 捷长 << ")";
            }
        }
        锋边 = {桩号集[前桩], 前桩};
        cout << "锋边" << 回合数 << "(" << 锋边.从 << "," << 锋边.到 << ")" << endl;
        捷边集.push_back(锋边);
        靶距集.push_back({前桩, 捷长});

        for (int 靶号 : 靶号集)
        {
            if (始靶长[前桩] + 图[前桩][靶号] < 始靶长[靶号])
            {
                始靶长[靶号] = 始靶长[前桩] + 图[前桩][靶号];
                桩号集[靶号] = 前桩;
                cout << 桩号集[靶号] << "->" << 靶号 << ":" << 始靶长[靶号] << endl;
            }
        }
        始靶长[前桩] = -1;

        回合数++;
    }

    cout << "\n捷径:" << endl;
    for (auto 靶距 : 靶距集)
    {
        cout << 始号 << "->" << 靶距.靶 << ":" << setw(4) << 靶距.始靶距 << endl;
    }
}

int main()
{
    int 点数 = 5, 始号 = 1;
    // vector<vector<double>> 图1 = {
    //     {0, 0, 0, 0, 0, 0},
    //     {0, 0, 1, 3, INFINITY, INFINITY},
    //     {0, 1, 0, 3, 6, INFINITY},
    //     {0, 3, 3, 0, 4, 2},
    //     {0, INFINITY, 6, 4, 0, 5},
    //     {0, INFINITY, INFINITY, 2, 5, 0}};

    vector<vector<double>> 图1 = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 7, 4, 6, 1},
        {0, INFINITY, 0, INFINITY, INFINITY, INFINITY},
        {0, INFINITY, 2, 0, 5, INFINITY},
        {0, INFINITY, 3, INFINITY, 0, INFINITY},
        {0, INFINITY, INFINITY, INFINITY, 1, 0}};

    点数 = 图1.size() - 1;

    印阵(点数, 1, 图1);

    vector<边> 捷边集;
    vector<捷径> 靶距集;

    for (始号 = 1; 始号 <= 点数; 始号++)
    {
        cout << "\n==================================\n"
             << endl;
        独源捷径(点数, 始号, 图1, 捷边集, 靶距集);
        for (int i = 0; i < 捷边集.size(); i++)
        {
            cout << "(" << 捷边集[i].从 << "," << 捷边集[i].到 << ")" << endl;
        }
        捷边集.clear();
        靶距集.clear();
    }
}