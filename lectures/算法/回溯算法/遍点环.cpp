#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

string 红 = "\033[0;31m";
string 黑 = "\033[0;30m";

// 起点固定为点1
class 遍点环
{
public:
    遍点环(/*int 点数*/ const vector<vector<bool>> &图);
    bool 有戏(int 本点号);
    void 遍点(int 本点号);
    void 印环();

public: // 数据
    int 点数;
    vector<vector<bool>> 图;
    vector<int> 环;
    int 胜数;
    int 试数;
};

遍点环::遍点环(/*int 点数*/ const vector<vector<bool>> &图)
{
    this->点数 = 图.size() - 1;
    this->图 = 图;
    环 = vector<int>(点数, 1);
    胜数 = 0;
    试数 = 0;
}

bool 遍点环::有戏(int 本点号)
{
    int 别点号 = 1;
    bool 可行 = true;

    if (本点号 == 点数 - 1 && !图[环[点数 - 1]][环[0]])
    {
        // 环首尾需相连
        可行 = false;
    }
    else if (本点号 > 0 && !图[环[本点号 - 1]][环[本点号]])
    {
        // 环上邻居需图中亦相邻
        可行 = false;
    }
    else
    {
        可行 = true;
        别点号 = 1;
        while (别点号 < 本点号 && 可行)
        {
            if (环[本点号] == 环[别点号]) // 查点已在环中否
            {
                可行 = false;
            }
            别点号++;
        }
    }

    return 可行;
}

void 遍点环::印环()
{
    cout << "(";
    for (int i = 0; i < 点数; i++)
    {
        cout << 环[i] << (i == 点数 - 1 ? ")" : ",");
    }
    cout << endl;
}

void 遍点环::遍点(int 本点号)
{
    int 别点号;

    if (有戏(本点号))
    {
        if (本点号 == 点数 - 1)
        {
            胜数++;
            cout << 红 << "第" << setw(2) << 胜数 << "次走回: " << 黑;
            印环();
        }
        else
        {
            for (别点号 = 2; 别点号 <= 点数; 别点号++)
            {
                试数++;
                环[本点号 + 1] = 别点号;
                遍点(本点号 + 1);
                cout << "第" << setw(2) << 试数 << "次试走: ";
                印环();
            }
        }
    }
}

int main()
{
    // 图1
    cout << "\n=========图1=========\n";
    vector<vector<bool>> 图1 = {// 零列零行浪费
                                {true, true, true, true, true},
                                {true, true, true, true, true},
                                {true, true, true, true, false},
                                {true, true, true, true, true},
                                {true, true, false, true, true}};

    遍点环 染1(图1);
    染1.遍点(0);

    // 图2
    cout << "\n=========图2=========\n";
    vector<vector<bool>> 图2 = {// 零列零行浪费
                                {true, true, true, true, true, true},
                                {true, true, true, false, false, true},
                                {true, true, true, true, true, true},
                                {true, false, true, true, true, false},
                                {true, false, true, true, true, false},
                                {true, true, true, false, false, true}};

    遍点环 染2(图2);
    染2.遍点(0);

    // 图3
    cout << "\n=========图3=========\n";
    vector<vector<bool>> 图3 = {// 零列零行浪费
                                {true, true, true, true, true, true, true, true, true},
                                {true, true, true, false, false, false, false, true, true},
                                {true, true, true, true, false, false, false, true, true},
                                {true, true, true, true, true, false, true, false, false},
                                {true, false, false, true, true, true, false, false, false},
                                {true, false, false, false, true, true, true, false, false},
                                {true, false, false, true, false, true, true, true, false},
                                {true, true, true, false, true, true, true, true, true},
                                {true, true, true, false, false, false, false, true, true}};

    遍点环 染3(图3);
    染3.遍点(0);
}