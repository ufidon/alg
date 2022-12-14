#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

struct 子集和
{
    子集和(const vector<double> &宝列, const double 包载);

    vector<double> 宝列;
    double 总宝重;
    double 包载;
    int 宝数;
    vector<bool> 取舍;

    void 装宝(int 号, double 现重, double 余重);
    bool 有戏(int 号, double 现重, double 余重);
    void 印宝(int 末号) const;
};

子集和::子集和(const vector<double> &宝列, const double 包载)
{
    宝数 = 宝列.size() - 1;
    this->包载 = 包载;
    this->宝列 = 宝列;
    取舍 = vector<bool>(宝数 + 1, false); // [1..宝数]
    总宝重 = accumulate(宝列.begin(), 宝列.end(), 0);
}

void 子集和::印宝(int 末号) const
{
    cout << "[";
    for (int 号 = 1; 号 <= 末号; 号++)
    {
        if (取舍[号])
        {
            cout << 宝列[号] << " ";
        }
    }
    cout << "]" << endl;
}

bool 子集和::有戏(int 号, double 现重, double 余重)
{
    return (现重 + 余重 >= 包载) && (现重 == 包载 || 现重 + 宝列[号 + 1] <= 包载);
}

void 子集和::装宝(int 号, double 现重, double 余重)
{
    if (有戏(号, 现重, 余重))
    {
        if (现重 == 包载)
        {
            印宝(号);
        }
        else
        {
            取舍[号 + 1] = true;
            装宝(号 + 1, 现重 + 宝列[号 + 1], 余重 - 宝列[号 + 1]);
            取舍[号 + 1] = false;
            装宝(号 + 1, 现重, 余重 - 宝列[号 + 1]);
        }
    }
}

int main()
{
    vector<double> 宝列 = vector<double>{0, 6, 4, 5, 7,9,8}; // 浪费零号
    // double 包载 = 12; // [6 5 1]
    double 包载 = 22; // 无解

    子集和 子1(宝列, 包载);
    子1.装宝(0, 0, 子1.总宝重);
}