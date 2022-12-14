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

typedef struct
{
    int 层;
    int 列;
    vector<int> 路;
    double 界;
} 点;

class 比界
{
public:
    bool operator()(点 &甲, 点 &乙)
    {
        return (甲.界 > 乙.界); // 队中后元大于前元, 为升序堆
    }
};

class 环城
{
public:
    环城(const vector<vector<double>> &图, const int 始城);

    void 寻环(); // 分枝设界先寻最佳者
    void 印环() const;
    void 印点(const 点 &本点);
    void 印路(const vector<int> &路) const;
    double 界(const 点 &本点);
    double 路长(const vector<int> &路) const;
    int 终城(const 点 &本点);
    vector<int> &陌城(const vector<int> &路) const;
    vector<int> &可至城(const int 发城, const vector<int> &路) const;
    void 印队(const priority_queue<点, vector<点>, 比界> &队);

public:
    vector<vector<double>> 图;
    int 城数;
    int 始城;

    int 出队点数;
    int 总点数;
    vector<int> 列号;

    double 最短路长;
    vector<int> 最短环;
};

环城::环城(const vector<vector<double>> &图, const int 始城)
{
    this->图 = 图;        // [1..城数][1..城数]
    城数 = 图.size() - 1; // 浪费零行零列
    this->始城 = 始城;

    出队点数 = 0;
    总点数 = 0;
    列号 = vector<int>(城数, 1);
    列号[0] = 0;

    最短路长 = INFINITY;
    最短环 = vector<int>(城数 + 1, -1); // [0..城数]
}

int 环城::终城(const 点 &本点)
{
    // 前提: 本点.层 == 城数-2
    vector<bool> 陌(城数 + 1, true); // [1..城数]
    for (int i = 0; i < 本点.路.size(); i++)
    {
        陌[本点.路[i]] = false;
    }
    for (int i = 1; i <= 城数; i++)
    {
        if (陌[i])
            return i;
    }
    return -1; // 此返出错
}

vector<int> &环城::陌城(const vector<int> &路) const
{
    vector<int> *未经城 = new vector<int>;
    vector<bool> 陌(城数 + 1, true); // [1..城数]

    // 求陌城
    for (int i = 0; i < 路.size(); i++)
    {
        陌[路[i]] = false;
    }
    for (int i = 1; i <= 城数; i++)
        if (陌[i])
            未经城->push_back(i);

    return *未经城;
}

vector<int> &环城::可至城(const int 发城, const vector<int> &路) const
{
    // 发城只能是路尾城和陌城
    vector<int> *至 = new vector<int>;
    vector<bool> 陌(城数 + 1, true); // [1..城数]

    // 求陌城
    for (int i = 0; i < 路.size(); i++)
    {
        陌[路[i]] = false;
    }

    // 发城为路尾城, 可至城为陌城, 路尾城不能回始城
    if (发城 == 路[路.size() - 1])
    {
        for (int i = 1; i <= 城数; i++)
            if (陌[i])
                至->push_back(i);
    }
    else // 发城为陌城之一
    {
        陌[始城] = true; // 陌城可回始城, 但不可回己
        for (int i = 1; i <= 城数; i++)
            if (陌[i] && 发城 != i)
                至->push_back(i);
    }

    return *至;
}

double 环城::界(const 点 &本点)
{
    double 路长 = 0;
    int 当前首城号 = 0;
    int 当前尾城号 = 本点.路.size() - 1, 尾城 = 本点.路[当前尾城号];
    double 最短路 = INFINITY;

    // 求当前路长
    for (int i = 0; i < 当前尾城号; i++)
    {
        路长 += 图[本点.路[i]][本点.路[i + 1]];
    }

    // cout << "经路长:" << 路长;

    if (尾城 == 始城)
    {
        for (int 发 = 1; 发 <= 城数; 发++)
        {
            最短路 = INFINITY;
            for (int 至 = 1; 至 <= 城数; 至++)
            {
                if (发 != 至)
                    if (图[发][至] < 最短路)
                    {
                        最短路 = 图[发][至];
                    }
            }
            路长 += 最短路;
        }
    }
    else
    {
        // 求未走最短路长
        // 1. 求出发于当前路尾之最短邻距(未经之城或陌城)
        vector<int> 至城 = 可至城(尾城, 本点.路);
        // cout << "尾至城";
        // 印路(至城);
        最短路 = INFINITY;
        for (int 至 = 0; 至 < 至城.size(); 至++)
        {
            if (图[尾城][至城[至]] < 最短路)
            {
                最短路 = 图[尾城][至城[至]];
                // cout << 尾城 << "->" << 至城[至] << ":" << 图[尾城][至城[至]];
            }
        }
        路长 += 最短路;
        // cout << "尾" << 尾城 << "发:" << 最短路;

        // 2. 求发于陌城之最短邻距(未经之城)
        vector<int> 未经城 = 陌城(本点.路);
        for (int 未 = 0; 未 < 未经城.size(); 未++)
        {
            int 发 = 未经城[未];
            vector<int> 至城 = 可至城(发, 本点.路);
            最短路 = INFINITY;
            for (int 至 = 0; 至 < 至城.size(); 至++)
            {
                if (图[发][至城[至]] < 最短路)
                {
                    最短路 = 图[发][至城[至]];
                }
            }
            // cout << "陌" << 发 << "发: " << 最短路;
            // cout << "陌至城";
            //印路(至城);
            路长 += 最短路;
        }
    }

    // cout << "界:" << 路长 << endl;

    return 路长;
}

double 环城::路长(const vector<int> &路) const
{
    double 长 = 0;
    int 号;
    for (号 = 0; 号 < 路.size() - 1; 号++)
    {
        长 += 图[路[号]][路[号 + 1]];
    }
    return 长;
}

void 环城::寻环()
{
    priority_queue<点, vector<点>, 比界> 队;

    点 子, 父;
    父.层 = 0;
    父.列 = 0;
    父.路.push_back(始城);
    父.界 = 界(父);
    最短路长 = INFINITY;
    印点(父);
    总点数++;
    队.push(父);
    cout << "入(" << 父.层 << "," << 父.列 << ")\n"
         << endl;
    while (!队.empty())
    {
        印队(队);
        父 = 队.top();
        队.pop(); // 按界升序,左小右大,左侧出队
        cout << "出(" << 父.层 << "," << 父.列 << ")" << endl;
        出队点数++;
        父.界 = 界(父);
        if (父.界 < 最短路长)
        {
            子.层 = 父.层 + 1;
            // 父路之陌城
            vector<int> 父陌 = 陌城(父.路);
            for (int 陌 : 父陌)
            {
                子.路 = 父.路;
                子.路.push_back(陌);
                子.界 = 界(子);
                子.列 = 列号[子.层]++;
                总点数++;

                if (子.层 == 城数 - 2)
                {
                    子.路.push_back(终城(子));
                    子.路.push_back(始城);
                    double 经路长 = 路长(子.路);
                    if (经路长 < 最短路长)
                    {
                        最短路长 = 经路长;
                        最短环 = 子.路;
                    }
                    cout << "环";
                    印点(子);
                }
                else
                {
                    cout << "算";
                    印点(子);
                    if (子.界 < 最短路长)
                    {
                        队.push(子);
                        cout << "入(" << 子.层 << "," << 子.列 << ")" << endl;
                    }
                    else
                    {
                        cout << "灭(" << 子.层 << "," << 子.列 << ")" << endl;
                    }
                }
            }
            cout << endl;
        }
        else
        {
            cout << "灭(" << 父.层 << "," << 父.列 << ")" << endl;
        }
    }
}

void 环城::印环() const
{
    cout << "最短环路[";
    for (int i = 0; i < 最短环.size(); i++)
    {
        cout << 最短环[i] << (i == 最短环.size() - 1 ? "]" : ",");
    }
    cout << "=" << 路长(最短环);
    cout << endl;
    cout << "出队点数:" << 出队点数 << endl;
    cout << "总点数:" << 总点数 << endl;
}

void 环城::印路(const vector<int> &路) const
{
    cout << "[";
    for (int i = 0; i < 路.size(); i++)
    {
        cout << 路[i] << (i == 路.size() - 1 ? "]" : ",");
    }
    // cout<<endl;
}

void 环城::印队(const priority_queue<点, vector<点>, 比界> &队)
{
    priority_queue<点, vector<点>, 比界> d = 队;
    cout << "[";
    while (!d.empty())
    {
        cout << "(" << d.top().层 << "," << d.top().列 << ")";
        d.pop();
    }

    cout << "]" << endl;
}

void 环城::印点(const 点 &本点)
{
    //本点.列 = 列号[本点.层];
    cout << "[(" << 本点.层 << "," << 本点.列 << ")";
    印路(本点.路);
    cout << "=" << 路长(本点.路);
    cout << "|界" << 本点.界 << "|最短路长" << 最短路长 << "]" << endl;
    //列号[本点.层]++;
}

int main()
{
    // 页263 图6.3
    cout << "\n页263 图6.3" << endl;
    vector<vector<double>> 图1 = {//浪费零行零列
                                  {0, 0, 0, 0, 0, 0},
                                  {0, 0, 14, 4, 10, 20},
                                  {0, 14, 0, 7, 8, 7},
                                  {0, 4, 5, 0, 7, 16},
                                  {0, 11, 7, 9, 0, 2},
                                  {0, 18, 7, 17, 4, 0}};

    int 始 = 1;
    cout << "=====出发于城" << 始 << "=====" << endl;
    环城 环1(图1, 始);
    环1.寻环();
    环1.印环();
    cout << "==============" << endl;

#if 0
    for (int 始 = 1; 始 <= 图1.size() - 1; 始++)
    {
        cout << "=====出发于城" << 始 << "=====" << endl;
        环城 环1(图1, 始);
        环1.寻环();
        环1.印环();
        cout << "==============" << endl;
    }
#endif

    // 页281 题7
    cout << "\n页281 题7" << endl;
    vector<vector<double>> 图2 = {//浪费零行零列
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

    环城 环2(图2, 1);
    环2.寻环();
    环2.印环();

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

    环城 环21(图21, 1);
    环21.寻环();
    环21.印环();

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
    环3.寻环();
    环3.印环();

}