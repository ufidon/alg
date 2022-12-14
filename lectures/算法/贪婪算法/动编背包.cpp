#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

typedef struct
{
    int 号;
    int 价;
    int 重;
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
    int 总价 = 0, 总重 = 0;
    cout << "宝物: " << endl;

    for (auto 宝 : 宝列)
    {
        总价 += 宝.价;
        总重 += 宝.重;
        cout << "[" << 宝.号 << "(" << 宝.价 << "," << 宝.重 << ")"
             << "] ";
    }
    cout << endl;
    cout << "总价: " << 总价 << ", 总重: " << 总重 << endl;
}

// 0-1 背包问题: 每宝整块拿
// 有宝几许,各重i,值钱i,背包承重有限,如何取物使价值最大

vector<int> 利;
vector<int> 重;

// 分治算法
int 丄利(const int 宝号, const int 剩容)
{
    if (宝号 == 0 || 剩容 == 0)
    {
        cout << "界|丄利[" << 宝号 << "," << 剩容 << "]=0" << endl;
        return 0;
    }
    else
    {
        if (重[宝号] > 剩容)
        {
            printf("破|重[%d]=%d>剩容=%d: ", 宝号, 重[宝号], 剩容);
            int 丄舍 = 丄利(宝号 - 1, 剩容);
            printf("丄利[%d][%d]=%d\n", 宝号 - 1, 剩容, 丄舍);
            return 丄舍;
        }
        else
        {
            printf("欠|重[%d]=%d≤剩容=%d: ", 宝号, 重[宝号], 剩容);

            int 丄舍 = 丄利(宝号 - 1, 剩容);
            printf("利[%d]=%d, 重[%d]=%d, 丄舍[%d][%d]=%d: ", 宝号, 利[宝号], 宝号, 重[宝号], 宝号 - 1, 剩容, 丄舍);
            int 丄取 = 丄利(宝号 - 1, 剩容 - 重[宝号]);
            printf("利[%d]=%d, 重[%d]=%d, 丄取[%d][%d]=%d: ", 宝号, 利[宝号], 宝号, 重[宝号], 宝号 - 1, 剩容 - 重[宝号], 丄取);
            int 丄 = max(丄舍, 利[宝号] + 丄取);
            printf("大者{丄利[%d][%d], 利[%d] + 丄利[%d][剩容-重[%d]]}=%d\n", 宝号 - 1, 剩容, 宝号, 宝号 - 1, 宝号, 丄);
            return 丄;
        }
    }
}

// 动态编程, 重量和价格都需为整数
// 动态编程算法 1: 每项都算
int 动编(int 宝数, int 包载)
{
    vector<vector<int>> 丄利(宝数 + 1, vector<int>(包载 + 1, 0));
    for (int 号 = 0; 号 <= 宝数; 号++)
    {
        for (int 载 = 0; 载 <= 包载; 载++)
        {
            if (号 == 0 || 载 == 0)
            {
                丄利[号][载] = 0;
                cout << "(" << 号 << "," << 载 << ")" << 丄利[号][载] << endl;
            }
            else
            {
                if (重[号] > 载)
                {
                    丄利[号][载] = 丄利[号 - 1][载];
                }
                else // 重[号] <= 载
                {
                    丄利[号][载] = max(丄利[号 - 1][载], 利[号] + 丄利[号 - 1][载 - 重[号]]);
                }
                cout << "(" << 号 << "," << 载 << ")" << 丄利[号][载] << endl;
            }
        }
    }
    return 丄利[宝数][包载];
}

// 动态编程算法 2: 只算需要的
typedef struct
{
    int 号, 载;
} 号载;

struct 比号载升
{
    bool operator()(const 号载 &甲, const 号载 &乙)
    {
        return ((甲.号 < 乙.号) || ((甲.号 == 乙.号) && (甲.载 < 乙.载)));
    }
};

struct 比号载降
{
    bool operator()(const 号载 &甲, const 号载 &乙)
    {
        return ((甲.号 > 乙.号) || ((甲.号 == 乙.号) && (甲.载 > 乙.载)));
    }
};

bool 号载比(const pair<号载,int> &甲, const   pair<号载,int>  &乙)
{
    return ((甲.first.号 < 乙.first.号) || ((甲.first.号 == 乙.first.号) && (甲.first.载 < 乙.first.载)));
}

map<号载, int, 比号载降> 要算;

int 寻算(const int 宝号, const int 剩容)
{
    if (宝号 == 0 || 剩容 == 0)
    {
        if (要算.find({宝号, 剩容}) == 要算.end())
            要算.insert({{宝号, 剩容}, 0});
        return 0;
    }
    else
    {
        if (重[宝号] > 剩容)
        {
            int 丄舍 = 0;
            if (要算.find({宝号 - 1, 剩容}) == 要算.end())
            {
                丄舍 = 寻算(宝号 - 1, 剩容);
                要算.insert({{宝号 - 1, 剩容}, 丄舍});
            }
            else
                丄舍 = 要算[{宝号 - 1, 剩容}];

            return 丄舍;
        }
        else
        {
            int 丄舍 = 0;
            if (要算.find({宝号 - 1, 剩容}) == 要算.end())
            {
                丄舍 = 寻算(宝号 - 1, 剩容);
                要算.insert({{宝号 - 1, 剩容}, 丄舍});
            }
            else
                丄舍 = 要算[{宝号 - 1, 剩容}];

            int 丄取 = 0;
            if (要算.find({宝号 - 1, 剩容 - 重[宝号]}) == 要算.end())
            {
                丄取 = 寻算(宝号 - 1, 剩容 - 重[宝号]);
                要算.insert({{宝号 - 1, 剩容 - 重[宝号]}, 丄取});
            }
            else
                丄取 = 要算[{宝号 - 1, 剩容 - 重[宝号]}];

            int 丄 = max(丄舍, 利[宝号] + 丄取);
            return 丄;
        }
    }
}

string 印丄项(const map<号载, int, 比号载降> &丄项)
{
    stringstream ss;
    for (auto 项 : 丄项)
    {
        ss << "丄[" << 项.first.号 << "][" << 项.first.载 << "]=" << 项.second << endl;
    }
    return ss.str();
}

int main()
{
    int 包容 = 30, 宝数 = 3;
    利 = vector<int>{0, 50, 60, 140};
    重 = vector<int>{0, 5, 10, 20};

    cout << "分治算法:" << endl;
    cout << 丄利(宝数, 包容) << endl;

    cout << "\n动编算法:" << endl;
    cout << 动编(宝数, 包容) << endl;

    cout << "\n只算要的:" << endl;
    cout << 寻算(宝数, 包容) << endl;
    cout << 印丄项(要算) << endl;
}
