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

typedef pair<int, int> 边;
typedef pair<int, double> 捷径;

void 印阵(int n, // 行列数
          int 始号,
          vector<vector<double>> &邻距)
{

    std::cout << std::left;

    for (int i = 始号; i <= n; i++)
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
          vector<vector<int>> &邻距)
{

    std::cout << std::left;

    for (int i = 始号; i <= n; i++)
    {
        for (int j = 始号; j <= n; j++)
            std::cout << std::setw(2) << 邻距[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void 独源捷径(const int 点数,
              const int 始号,
              const vector<vector<double>> &邻距,
              vector<边> &树边集,
              vector<捷径> 捷径集)
{
    int 靶号, 桩号;
    边 锋边;
    int 桩号集[点数 + 1];    // [2..点数]
    double 临捷长[点数 + 1]; // [2..点数]

    // 从始号出发
    // 点号集
    vector<int> 点号集(点数);
    iota(点号集.begin(), 点号集.end(), 1);   // 初设(1..点数)
    点号集.erase(点号集.begin() + 始号 - 1); // 移除始号

    for (int i : 点号集)
    {
        桩号集[i] = 始号;
        临捷长[i] = 邻距[始号][i];
    }

    // 自始点沿捷径至其余图点
    int 回合数 = 1;
    cout << "第" << 回合数 << "回合：始于点" << 始号 << endl;

    while (回合数 < 点数) // 共"点数-1"回
    {
        double 捷长 = INFINITY;
        for (int i : 点号集)
        {
            if (临捷长[i] >= 0 && 临捷长[i] < 捷长)
            {
                捷长 = 临捷长[i];
                靶号 = i;
            }
        }
        锋边 = make_pair(桩号集[靶号], 靶号);
        树边集.push_back(锋边);

        for (int i : 点号集)
        {
            if (临捷长[靶号] + 邻距[i][靶号] < 临捷长[i])
            {
                临捷长[i] = 临捷长[靶号] + 邻距[i][靶号];
                桩号集[i] = 靶号;
                cout<<始号<<"->"<<靶号<<":"<<临捷长[i]<<endl;
            }

            临捷长[靶号] = -1;
        }
        捷径 捷 = make_pair(靶号, 临捷长[靶号]);
        捷径集.push_back(捷);

        回合数++;
        cout << "第" << 回合数 << "回合：" << endl;
        cout << "至点: " << 靶号 << endl;
    }

    cout << "\n捷径:" << endl;
    for (int i : 点号集)
    {
        cout << left << "源 -> 的" << endl;
        cout << setw(2) << 始号 << "->" << 捷径集[i].first << ":" << setw(4) << 捷径集[i].second << endl;
    }
}

int main()
{
    int 点数 = 5, 始号 = 1;
    vector<vector<double>> 邻距 = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 3, INFINITY, INFINITY},
        {0, 1, 0, 3, 6, INFINITY},
        {0, 3, 3, 0, 4, 2},
        {0, INFINITY, 6, 4, 0, 5},
        {0, INFINITY, INFINITY, 2, 5, 0}};

    印阵(点数, 1, 邻距);

    vector<边> 树边集;
    vector<捷径> 捷径集;

    for (始号 = 1; 始号 <= 点数; 始号++)
    {
        cout << "\n==================================\n"
             << endl;
        独源捷径(点数, 始号, 邻距, 树边集, 捷径集);
        for (int i = 0; i < 树边集.size(); i++)
        {
            cout << "(" << 树边集[i].first << "," << 树边集[i].second << ")" << endl;
        }
        树边集.clear();
    }
}