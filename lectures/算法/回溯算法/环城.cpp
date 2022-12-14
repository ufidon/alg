#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>
#include <numeric>

using namespace std;

class 环城
{
public:
    vector<vector<double>> 图; // 图[1..点数][1..点数]
    int 点数;
    int 起点;
    vector<int> 余点; // [0..点数-2]去除起点
    vector<int> 环;   // 环[0..点数-1]
    环城(const vector<vector<double>> &图, int 始);

    int 列号;
    int 前层;

    double 最短环长;

    bool 有戏(int 本点) const;
    void 寻环(int 本点); // 回溯算法
    void 探环(int 本点); // 遍寻环路,穷尽回溯算法
    void 印环() const;
    void 印列(const vector<int> &列) const;
    double 环长() const;
    void 印点(const int 本层);
};

void 环城::印环() const
{
    cout << "[";
    for (int i = 0; i < 点数; i++)
    {
        cout << 环[i] << ((i == 点数 - 1) ? "]" : ",");
    }
    // cout << endl;
}

void 环城::印列(const vector<int> &列) const
{
    cout << "[";
    int 丄号 = 列.size() - 1;
    for (int i = 0; i <= 丄号; i++)
    {
        cout << 列[i] << ((i == 丄号) ? "]" : ",");
    }
    // cout << endl;
}

double 环城::环长() const
{
    double 长 = 0;
    for (int i = 0; i < 点数 - 1; i++)
    {
        长 += 图[环[i]][环[i + 1]];
    }
    长 += 图[环[点数 - 1]][环[0]];

    return 长;
}

void 环城::印点(const int 本层)
{
    if (本层 != 前层)
    {
        前层 = 本层;
        列号 = 1;
    }

    cout << "(" << 本层 << "," << 列号 << ")" << endl;
    列号++;
}

bool 环城::有戏(int 本点) const
{
    int 前点 = 0;
    bool 通;

    if (本点 == 点数 - 1 && !图[环[点数 - 1]][环[0]]) //环首尾不通
    {
        通 = false;
    }
    else if (本点 > 0 && !图[环[本点 - 1]][环[本点]]) // 无点至本点
    {
        通 = false;
    }
    else
    {
        通 = true;
        前点 = 1;
        while (前点 < 本点 && 通)
        {
            if (环[本点] == 环[前点]) // 环只能过每点一次
            {
                通 = false;
            }
            前点++;
        }
    }

    return 通;
}

void 环城::寻环(int 本点)
{
    if (有戏(本点))
    {
        if (本点 == 点数 - 1)
        {
            印环();
            cout << endl;
        }
        else
        {
            for (int 次点 : 余点)
            {
                环[本点 + 1] = 次点;
                寻环(本点 + 1);
            }
        }
    }
}

void 环城::探环(int 本点)
{
    if (有戏(本点))
    {
        if (本点 == 点数 - 1)
        {
            double 长 = 环长();
            if (长 < 最短环长)
            {
                最短环长 = 长;
                cout << "找到新的最短环:";
                印环();
                cout << "=" << 最短环长 << endl;
            }
        }
        else
        {
            for (int 次点 : 余点)
            {
                环[本点 + 1] = 次点;
                探环(本点 + 1);
            }
        }
    }
}

环城::环城(const vector<vector<double>> &图, int 始)
{
    this->图 = 图;
    点数 = 图.size() - 1; // 浪费零行零列

    起点 = 始;
    环 = vector<int>(点数, -1);
    环[0] = 起点;
    余点 = vector<int>(点数, 1);
    iota(余点.begin(), 余点.end(), 1);
    余点.erase(余点.begin() + 起点 - 1);
    cout<<"始"<<起点<<"余";
    印列(余点);
    cout << endl;

    前层 = 0;
    列号 = 0;

    最短环长 = INFINITY;
}

int main()
{

    cout << "================图1==============\n";
    vector<vector<double>> 图1 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0, 1, 1},
        {0, 1, 1, 1, 0, 0, 0, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0, 1, 1}};

    环城 环1(图1, 1);

    环1.寻环(0);
    环1.探环(0);

    cout << "===============图2===============\n";

    vector<vector<double>> 图2 = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 1},
    };

    环城 环2(图2, 1);

    环2.寻环(0);
    环2.探环(0);

    cout << "\n===============图3===============\n";

    vector<vector<double>> 图3 = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 7, 37, 34, 13, 48, 50, 26, 45},
                                  {0, 36, 0, 2, 21, 16, 3, 17, 2, 5},
                                  {0, 14, 14, 0, 44, 10, 29, 22, 2, 6},
                                  {0, 22, 6, 5, 0, 4, 11, 15, 8, 43},
                                  {0, 17, 14, 27, 28, 0, 22, 20, 5, 21},
                                  {0, 38, 33, 34, 41, 49, 0, 33, 27, 32},
                                  {0, 19, 15, 45, 37, 34, 28, 0, 2, 25},
                                  {0, 40, 28, 36, 18, 45, 23, 27, 0, 28},
                                  {0, 17, 48, 37, 5, 4, 34, 36, 12, 0}};

    环城 环3(图3, 1);

    环3.探环(0);

    // 页263 图6.3
    cout << "\n页263 图6.3" << endl;
    vector<vector<double>> 图4 = {//浪费零行零列
                                  {0, 0, 0, 0, 0, 0},
                                  {0, 0, 14, 4, 10, 20},
                                  {0, 14, 0, 7, 8, 7},
                                  {0, 4, 5, 0, 7, 16},
                                  {0, 11, 7, 9, 0, 2},
                                  {0, 18, 7, 17, 4, 0}};

    for (int i = 1; i <= 图4.size() - 1; i++)
    {
        cout << "---------始于" << i << "-----------------" << endl;
        环城 环4(图4, i);
        环4.探环(0);
        cout << "-----------------------------------" << endl;
    }

    环城 环4(图4, 1);
    环4.探环(0);

    // 页281 题7
    cout << "\n页281 题7" << endl;
    vector<vector<double>> 图5 = {//浪费零行零列
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 5, 8, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY},
                                  {0, INFINITY, 0, 4, INFINITY, 4, INFINITY, INFINITY, INFINITY},
                                  {0, INFINITY, INFINITY, 0, 2, INFINITY, INFINITY, 5, INFINITY},
                                  {0, INFINITY, INFINITY, INFINITY, 0, INFINITY, INFINITY, INFINITY, 7},
                                  {0, 1, INFINITY, INFINITY, INFINITY, 0, INFINITY, INFINITY, INFINITY},
                                  {0, INFINITY, 6, INFINITY, INFINITY, 2, 0, INFINITY, INFINITY},
                                  {0, INFINITY, INFINITY, INFINITY, 7, INFINITY, 8, 0, INFINITY},
                                  {0, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 5, 4, 0}

    };

    环城 环5(图5, 1);
    环5.探环(0);

    cout << "\n页281 题7'" << endl;
    vector<vector<double>> 图21 = {//浪费零行零列
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 5, 8, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY},
                                   {0, INFINITY, 0, 4, INFINITY, 4, INFINITY, INFINITY, INFINITY},
                                   {0, INFINITY, INFINITY, 0, 2, INFINITY, INFINITY, 5, INFINITY},
                                   {0, INFINITY, INFINITY, INFINITY, 0, INFINITY, INFINITY, INFINITY, 7},
                                   {0, 1, INFINITY, INFINITY, INFINITY, 0, INFINITY, INFINITY, INFINITY},
                                   {0, INFINITY, 6, INFINITY, INFINITY, 2, 0, INFINITY, INFINITY},
                                   {0, INFINITY, INFINITY, INFINITY, 3, INFINITY, 8, 0, INFINITY},
                                   {0, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 5, 4, 0}

    };

    环城 环6(图21, 1);
    环6.探环(0);

    // 页282 题8
    cout << "\n页282 题8" << endl;
    vector<vector<double>> 图7 = {//浪费零行零列
                                  {0, 0, 0, 0, 0, 0},
                                  {0, 0, 6, 6, 10, 8},
                                  {0, 3, 0, 12, 7, 6},
                                  {0, 8, 7, 0, 14, 20},
                                  {0, 5, 13, 9, 0, 8},
                                  {0, 9, 8, 10, 6, 0}};

    环城 环7(图7, 1);
    环7.探环(0);
}