#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

typedef struct
{
    double 利;
    double 重;
} 宝;

class 背包
{
public:              /* 数据 */
    vector<宝> 宝列; // 已按单价降序排好
    double 包载;
    int 宝数;
    double 最大收获;
    int 末宝号;          // 装袋末宝号
    vector<bool> 取;     // 取[i]真取假舍i号宝
    vector<bool> 最优集; // 最优集[i]真取假舍i号宝
    vector<int> 列号;

public:
    背包(const vector<宝> &宝列, const double &包载);
    bool 有戏(int 本宝号, double 现利, double 现重);
    double 界(int 本宝号, double 现利, double 现重);
    void 装宝(int 本宝号, double 现利, double 现重);
    void 印包();
};

void 背包::印包()
{
    cout << "最大获利:" << 最大收获 << "[";
    for (int i = 1; i <= 宝数; i++)
    {

        cout << (最优集[i] ? "取" : "舍") << i << "(" << 宝列[i].利 << "," << 宝列[i].重 << ")";

        cout << (i == 宝数 ? "]" : ",");
    }
    cout << endl;
}

背包::背包(const vector<宝> &宝列, const double &包载)
{
    this->宝列 = 宝列;
    宝数 = 宝列.size() - 1; // 浪费0号
    最优集 = vector<bool>(宝列.size(), false);
    取 = vector<bool>(宝列.size(), false);
    列号 = vector<int>(宝列.size(), 1);
    列号[0] = 0;
    this->包载 = 包载;
    末宝号 = 0;
    最大收获 = 0;
}

bool 背包::有戏(int 本宝号, double 现利, double 现重)
{
    int 下号, 破号;
    double 全重;

    double 利界;

    if (现重 >= 包载)
    {
        return false;
    }
    else
    {
        下号 = 本宝号 + 1;
        利界 = 现利;
        全重 = 现重;

        // 包载之内装尽可能多的宝
        while (下号 <= 宝数 && 全重 + 宝列[下号].重 <= 包载)
        {
            全重 += 宝列[下号].重;
            利界 += 宝列[下号].利;
            下号++;
        }
        破号 = 下号;
        if (破号 <= 宝数)
        {
            利界 += (包载 - 全重) * 宝列[破号].利 / 宝列[破号].重;
        }

        return (利界 > 最大收获);
    }
}

double 背包::界(int 本宝号, double 现利, double 现重)
{
    int 下号, 破号;
    double 全重;

    double 利界;

    if (现重 >= 包载)
    {
        return 0;
    }
    else
    {
        下号 = 本宝号 + 1;
        利界 = 现利;
        全重 = 现重;

        // 包载之内装尽可能多的宝
        while (下号 <= 宝数 && 全重 + 宝列[下号].重 <= 包载)
        {
            全重 += 宝列[下号].重;
            利界 += 宝列[下号].利;
            下号++;
        }
        破号 = 下号;
        if (破号 <= 宝数)
        {
            利界 += (包载 - 全重) * 宝列[破号].利 / 宝列[破号].重;
        }

        return 利界;
    }
}

int 昨宝号 = 0;
string 进退[] = {"进", "退"};
void 背包::装宝(int 本宝号, double 现利, double 现重)
{
    if (现重 <= 包载 && 现利 > 最大收获)
    {
        最大收获 = 现利;
        末宝号 = 本宝号;
        最优集 = 取;
    }

    int 进或退 = (昨宝号 < 本宝号);
    cout << left << 进退[进或退] << "[(" << 本宝号 << "," << 列号[本宝号]++ << ")利:" << setw(4) << 现利 << "重:" << setw(4)
         << 现重 << "界:" << setw(4) << 界(本宝号, 现利, 现重) << "丄利:" << 最大收获 << "]" << endl;
    昨宝号 = 本宝号;
    if (有戏(本宝号, 现利, 现重))
    {
        取[本宝号 + 1] = true;
        装宝(本宝号 + 1, 现利 + 宝列[本宝号 + 1].利, 现重 + 宝列[本宝号 + 1].重);
        取[本宝号 + 1] = false;
        装宝(本宝号 + 1, 现利, 现重);
    }
}

int main()
{
    vector<宝> 宝列1 = {{0, 0}, // 浪费零号
                        {40, 2},
                        {30, 5},
                        {50, 10},
                        {10, 5}};

    double 包载1 = 16;

    背包 包1(宝列1, 包载1);
    包1.装宝(0, 0, 0);
    包1.印包();

    vector<宝> 宝列2 = {{0, 0}, // 浪费零号
                        {20, 2},
                        {30, 5},
                        {35, 7},
                        {12, 3},
                        {3, 1}};

    double 包载2 = 9;

    背包 包2(宝列2, 包载2);
    包2.装宝(0, 0, 0);
    包2.印包();
}
