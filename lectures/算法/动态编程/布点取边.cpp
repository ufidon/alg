#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <numeric>
#include "散集.h"

using namespace std;

// 最小支撑树贪婪算法一: 布点取边（Kruskal算法）
// 图=（点集，边集），最小支撑树 = （点集，边集）
// 最小支撑树始于全部图点，按边长升序取边
// 边数达点数减一止

typedef struct
{
    pair<int, int> 端点;
    double 长度;
} 边;

bool 比边长(边 a, 边 b)
{
    return (a.长度 < b.长度);
}

void 印边集(const vector<边>& 边集)
{
    for (auto 边: 边集)
    {
        cout << 边.端点.first<<"-("<<边.长度<<")-"<<边.端点.second<<endl;
    }   
}

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

void 布点取边(
    const vector<vector<double>> &邻距,
    vector<边> &树边集,
    double &全重)
{
    // 从邻距求图全情
    int 点数 = 邻距.size() - 1; // 号从1取而非0
    int 边数 = 0;

    vector<边> 图边集;
    for (int i = 1; i <= 点数 - 1; i++)
    {
        for (int j = i + 1; j <= 点数; j++)
        {
            if (!isinf(邻距[i][j]))
            {
                边 i2j;
                i2j.端点.first = i, i2j.端点.second = j;
                i2j.长度 = 邻距[i][j];
                边数++;
                图边集.push_back(i2j);
            }
        }
    }

    // 升序排边
    sort(图边集.begin(), 图边集.end(), 比边长);
    cout<<"升序图边集: "<<endl;
    印边集(图边集);

    全重 = 0;

    号 图边号 = 0;

    
    //散列集 散(点数);
    //散树集 散(点数);
    散木集 散(点数);
    while (树边集.size() < 点数 - 1)
    {
        // 此处等长边未处理
        // 等长边之不同选择可能生成不同最小支撑树
        // 办法: 将等长边做全排列然后依个处理
        边 b = 图边集[图边号];
        号 i = b.端点.first;
        号 j = b.端点.second;
        集手 p = 散.寻(i);
        集手 q = 散.寻(j);

        if (! 散.同(p,q))
        {
            散.并(p,q);
            树边集.push_back(b);
            全重 += b.长度;
        }
        
        图边号++;
    }
}

int main()
{
    int 点数 = 5, 始号 = 1;
    vector<vector<double>> 邻距 = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 2, 3, INFINITY, INFINITY},
        {0, 2, 0, 1, 6, INFINITY},
        {0, 3, 1, 0, 4, 7},
        {0, INFINITY, 6, 4, 0, 5},
        {0, INFINITY, INFINITY, 7, 5, 0}};

    印阵(点数, 1, 邻距);
    vector<边> 树边集;
    double 全重 = 0;

    布点取边(邻距, 树边集, 全重);
    cout<<"最小支撑树边集:"<<endl;
    印边集(树边集);
    cout <<"全重: "<<全重<<endl;
}