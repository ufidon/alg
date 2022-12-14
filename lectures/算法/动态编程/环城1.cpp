#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

// 动态编程解环城问题

class 环城
{
public:
    环城(const vector<vector<double>> &图, const int 始城);

public:
    vector<vector<double>> 图;
    int 城数;
    int 始城;
    double 最短环长;
    vector<int> 最短环;
    vector<int>& 差集(const vector<int> &甲, const vector<int> &乙);

public:    
    static vector<vector<vector<int>>>& 造组(const vector<int>& 数组);
    static vector<int>& 算贰系(int n);
    static void 印列(const vector<int> &列);
    static void 印城子集(const vector<vector<vector<int>>>& 城子集);

};

vector<int> &环城::差集(const vector<int> &甲, const vector<int> &乙)
{
    // 已知甲乙为[1..城数]子集
    vector<int> *差 = new vector<int>;
    vector<bool> 在甲(城数+1, false); 
    vector<bool> 在乙(城数+1, false);

    for (int i = 0; i < 甲.size(); i++)
    {
        在甲[甲[i]] = true;
    }
    for (int i = 0; i < 乙.size(); i++)
    {
        在乙[乙[i]] = true;
    }

    // 甲 - 乙 = {不在乙中的甲元}
    for (int i = 1; i <= 城数; i++)
        if (在甲[i] && !在乙[i])
            差->push_back(i);

    return *差;
}

vector<vector<vector<int>>>&  环城::造组(const vector<int>& 数组)
{
    int n = 数组.size(); // n 取 r=1..n
    int r = 0, 贰 = 0;

    bool *含 = new bool[n]{0};

    // 略空集
    vector<vector<vector<int>>> *p = new vector<vector<vector<int>>>(n+1);
    vector<vector<vector<int>>>& 城子集 = *p;

    vector<int>& 贰系 = 算贰系(n);

    for (int r = 1; r <= n; r++)
    {
        城子集[r] = vector<vector<int>>(贰系[r], vector<int>(r, 0));
    }
    //印城子集();    

    for (r = 0; r < n; r++)
    {
        // cout << "\n--------" << (r + 1) << "元组:--------" << endl;
        含[r] = 1;
        贰 = 0;
        // 全部排列
        do
        {
            int k = 0, 列号 = 0;
            for (int j = 0; j < n; j++)
            {

                if (含[j])
                {
                    城子集[r + 1][贰 / (r + 1)][列号] = 数组[j];
                    // cout << "|"
                    //      << "(" << 贰 / (r + 1)
                    //      << "," << 列号 << "):" << j + 1;
                    列号++;
                    贰++;
                }
            }

            k++;
            // cout << endl;
        } while (prev_permutation(含, 含 + n));
    }

    return 城子集;
}

void 环城::印城子集(const vector<vector<vector<int>>>& 城子集)
{
    for (int r = 1; r <= 城子集.size() - 1; r++)
    {
        for (int i = 0; i < 城子集[r].size(); i++)
        {
            cout << "(" << r << "," << i << ")";
            印列(城子集[r][i]);
        }
    }
}

void 环城::印列(const vector<int> &列)
{
    cout << "[";
    for (int i = 0; i < 列.size(); i++)
    {
        cout << 列[i] << (i == 列.size() - 1 ? "]" : ",");
    }
    cout << endl;
}

vector<int>& 环城::算贰系(int n)
{
    vector<int>* p = new vector<int>(n+1,1);
    vector<int>& 贰系 = *p;

    贰系[0] = 1;
    int 旧, 新;
    for (int i = 0; i <= n; i++)
    {
        旧 = 新 = 贰系[0];
        for (int j = 0; j <= min(i, n); j++)
        {
            if (j == 0 || j == i)
            {
                贰系[j] = 1;
            }
            else
            {
                新 = 贰系[j];
                贰系[j] = 旧 + 贰系[j];
                旧 = 新;
            }
        }
    }
    return 贰系;
}



环城::环城(const vector<vector<double>> &图, const int 始城)
{
    this->图 = 图;        // [1..城数][1..城数]
    城数 = 图.size() - 1; // 浪费零行零列
    this->始城 = 始城;

    最短环长 = INFINITY;
    最短环 = vector<int>(城数 + 1, -1); // [0..城数]
}

int main()
{
    // 页282 题8
    cout << "\n页282 题8" << endl;
    vector<vector<double>> 图3 = {//浪费零行零列
                                  {0, 0, 0, 0, 0, 0},
                                  {0, 0, 6, 6, 10, 8},
                                  {0, 3, 0, 12, 7, 6},
                                  {0, 8, 7, 0, 14, 20},
                                  {0, 5, 13, 9, 0, 8},
                                  {0, 9, 8, 10, 6, 0}};

    
    环城 环3(图3, 1);

    vector<int> 数组={3,5,7,9,10};
    环城::印列(环城::算贰系(数组.size()));
    环城::印城子集(环城::造组(数组));


}
