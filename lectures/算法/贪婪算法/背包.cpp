#include <iostream>
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
    double 价;
    double 重;
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
    double 总价 = 0, 总重 = 0;
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
// 贪婪算法1: 按价降序排,依次装至包容限

void 贵者先(const vector<宝> &宝列,
            const double &包限)
{
    vector<宝> 依价降序 = 宝列;
    sort(依价降序.rbegin(), 依价降序.rend(), 比价);

    vector<宝> 装宝;
    double 装价 = 0, 装重 = 0;

    for (宝 某 : 依价降序)
    {
        装重 += 某.重;
        if (装重 > 包限)
        {
            装重 -= 某.重;
            break;
        }

        装价 += 某.价;
        装宝.push_back(某);
    }

    cout << "装得宝物: 贵者先" << endl;

    for (auto b : 装宝)
    {
        cout << "[" << b.号 << "(" << b.价 << "," << b.重 << ")"
             << "] ";
    }
    cout << endl;
    cout << "总价: " << 装价 << ", 总重: " << 装重 << ", 浪费容量: " << 包限 - 装重 << endl;
}

// 贪婪算法2: 按重升序排,依次装至包容限

void 轻者先(const vector<宝> &宝列,
            const double &包限)
{
    vector<宝> 先拿轻的 = 宝列;
    sort(先拿轻的.begin(), 先拿轻的.end(), 比重);

    vector<宝> 装宝;
    double 装价 = 0, 装重 = 0;

    for (宝 某 : 先拿轻的)
    {
        装重 += 某.重;
        if (装重 > 包限)
        {
            装重 -= 某.重;
            break;
        }

        装价 += 某.价;
        装宝.push_back(某);
    }

    cout << "装得宝物: 轻者先" << endl;

    for (auto b : 装宝)
    {
        cout << "[" << b.号 << "(" << b.价 << "," << b.重 << ")"
             << "] ";
    }
    cout << endl;
    cout << "总价: " << 装价 << ", 总重: " << 装重 << ", 浪费容量: " << 包限 - 装重 << endl;
}

// 贪婪算法3: 按单价降序排,依次装至包容限

void 单价高者先(const vector<宝> &宝列,
                const double &包限)
{
    vector<宝> 单价高先 = 宝列;
    sort(单价高先.rbegin(), 单价高先.rend(), 比单价);

    vector<宝> 装宝;
    double 装价 = 0, 装重 = 0;

    for (宝 某 : 单价高先)
    {
        装重 += 某.重;
        if (装重 > 包限)
        {
            装重 -= 某.重;
            break;
        }

        装价 += 某.价;
        装宝.push_back(某);
    }

    cout << "装得宝物: 单价高者先" << endl;

    for (auto b : 装宝)
    {
        cout << "[" << b.号 << "(" << b.价 << "," << b.重 << ")"
             << "] ";
    }
    cout << endl;
    cout << "总价: " << 装价 << ", 总重: " << 装重 << ", 浪费容量: " << 包限 - 装重 << endl;
}

// 分数背包问题: 每宝可拿任意部分，如金沙
// 有宝几许,各重i,值钱i,背包承重有限,如何取物使价值最大
// 贪婪算法1: 按价降序排,依次装至包容限
void 单价高者先拿(const vector<宝> &宝列,
                const double &包限)
{
    vector<宝> 单价高先 = 宝列;
    sort(单价高先.rbegin(), 单价高先.rend(), 比单价);

    vector<宝> 装宝;
    double 装价 = 0, 装重 = 0;

    for (宝 某 : 单价高先)
    {
        装重 += 某.重;
        if (装重 > 包限)
        {
            装重 -= 某.重;
            // 取最后那块宝一部分
            double 剩容 = 包限-装重;
            if (剩容>0)
            {
                装重 = 包限;
                装价 += 剩容*某.价/某.重;
                某.重 = 剩容;
                装宝.push_back(某);
            }           

            break;
        }

        装价 += 某.价;
        装宝.push_back(某);
    }

    cout << "装得宝物: 单价高者先" << endl;

    for (auto b : 装宝)
    {
        cout << "[" << b.号 << "(" << b.价 << "," << b.重 << ")"
             << "] ";
    }
    cout << endl;
    cout << "总价: " << 装价 << ", 总重: " << 装重 << ", 浪费容量: " << 包限 - 装重 << endl;
}

int main()
{
    vector<宝> 宝列;
    int 号 = 1;
    double 价 = 0, 重 = 0;
    double 包限 = 0;

    cout << "输入包容重: ";
    cin >> 包限;

    cout << "输入各宝价重(以 0 0 结束): ";
    while (cin >> 价 >> 重)
    {
        // cout << "号: " << 号 << endl;
        if (价 == 0 && 重 == 0)
            break;

        宝 某{号, 价, 重};
        宝列.push_back(某);
        号++;
    }

    cout << "待装";
    印宝(宝列);
    cout << endl;

    贵者先(宝列, 包限);
    cout << endl;

    轻者先(宝列, 包限);
    cout << endl;

    单价高者先(宝列, 包限);
    cout << endl;

    单价高者先拿(宝列, 包限);
    cout << endl;
}