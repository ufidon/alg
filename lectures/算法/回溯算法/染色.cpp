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

class 染色
{
public:
    染色(/*int 点数, int 色数,*/ const vector<vector<bool>> &图, const vector<string> &色盘);
    bool 有戏(int 本点号);
    void 染(int 本点号);
    void 印点();

public: // 数据
    int 点数;
    int 色数;
    vector<vector<bool>> 图;
    vector<string> 色盘;
    vector<string> 点色;

    int 胜数;
    int 试数;
};

染色::染色(/*int 点数, int 色数,*/ const vector<vector<bool>> &图, const vector<string> &色盘)
{
    this->点数 = 图.size() - 1;
    this->色数 = 色盘.size() - 1;
    this->图 = 图;
    this->色盘 = 色盘;
    点色 = vector<string>(图.size(), 色盘[0]);
    胜数 = 0;
    试数 = 0;
}

bool 染色::有戏(int 本点号)
{
    int 前点号 = 1;
    bool 可染 = true;

    while (前点号 < 本点号 && 可染)
    {
        if (图[本点号][前点号] && 点色[本点号] == 点色[前点号])
        {
            可染 = false;
        }

        前点号++;
    }

    return 可染;
}

void 染色::印点()
{
    for (int 点号 = 1; 点号 <= 点数; 点号++)
    {
        cout << "(" << 点号 << "," << 点色[点号] << ") ";
    }
    cout << endl;
}

void 染色::染(int 本点号)
{
    int 色;
    if (有戏(本点号))
    {
        if (本点号 == 点数)
        {
            胜数++;
            cout << 红 << "第" << setw(2) << 胜数 << "次染成: " << 黑;
            印点();
        }
        else
        {
            for (色 = 1; 色 <= 色数; 色++)
            {
                试数++;
                点色[本点号 + 1] = 色盘[色];
                cout << "第" << setw(2) << 试数 << "次试染: ";
                印点();
                染(本点号 + 1);
            }
        }
    }
}

int main()
{
    vector<vector<bool>> 图1 = {// 零列零行浪费
                                {true, true, true, true, true},
                                {true, true, true, true, true},
                                {true, true, true, true, false},
                                {true, true, true, true, true},
                                {true, true, false, true, true}};
    vector<string> 色盘 = {"空", "红", "绿", "蓝"}; // 零号浪费
    染色 染1(图1, 色盘);
    染1.染(0);

    vector<vector<bool>> 图2 = {// 零列零行浪费
                                {true, true, true, true, true, true, true, true},
                                {true, true, true, false, true, false, false},
                                {true, true, true, true, false, true, false},
                                {true, false, true, true, false, false, true},
                                {true, true, false, false, true, true, false},
                                {true, false, true, false, true, true, true},
                                {true, false, false, true, false, true, true}
                                };
    染色 染2(图2, 色盘);
    染2.染(0);
}