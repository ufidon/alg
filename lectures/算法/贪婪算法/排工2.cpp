#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

// 最大化利润

typedef struct
{
    int 号, 截;
    double 利;
} 工;

bool 比截(const 工 &甲, const 工 &乙)
{
    return (甲.截 < 乙.截);
}

bool 比利(const 工 &甲, const 工 &乙)
{
    return (甲.利 < 乙.利);
}

string 印工集(const vector<工> &集)
{
    stringstream ss;
    ss << "[";

    int 工数 = 集.size();
    for (int i = 0; i < 工数; i++)
    {
        ss << 集[i].号 << "(" << 集[i].利 << "," << 集[i].截 << ")";
    }
    ss << "]";
    return ss.str();
}

double 求利(const vector<工> &集)
{
    double 利 = 0;
    for (auto 工 : 集)
        利 += 工.利;

    return 利;
}

bool 可排(const vector<工> &工集)
{
    bool 可 = true;
    // 按截升序
    vector<工> 排 = 工集;
    int 工数 = 排.size();
    sort(排.begin(), 排.end(), 比截);
    for (int 日 = 1, 号 = 0; 日 <= 工数; 日++, 号++)
    {
        if (排[号].截 < 日)
        {
            可 = false;
            break;
        }
    }
    return 可;
}

// 工集已按利降序
void 排工(const vector<工> &工集, vector<工> &最优工序)
{
    int 号 = 0, 工数 = 工集.size();
    vector<工> 试;
    最优工序.push_back(工集[号]);
    cout << (号+1) << "优J:" << 印工集(最优工序) << endl;
    for (号 = 1; 号 < 工数; 号++)
    {

        试 = 最优工序;
        试.push_back(工集[号]);
        cout << (号+1) << "试K:" << 印工集(试);
        if (可排(试))
        {
            cout << "可排";
            最优工序 = 试;
            cout <<  "优J:" << 印工集(最优工序) << endl;
        }
        else
            cout << "禁排" << endl;
    }
}

int main()
{
#if 0    
    // 课本178页例4.4
    cout << "课本178页例4.4" << endl;
    vector<工> 优1;
    vector<工> 集1 = {{1, 2, 40}, {2, 1, 35}, {3, 1, 30}, {4, 3, 25}, {5, 1, 20}, {6, 3, 15}, {7, 2, 10}};
    排工(集1, 优1);
    cout << "工集:" << 印工集(集1) << endl;
    cout << "优序:" << 印工集(优1) << endl;
    cout << "丄利:" << 求利(优1) << endl;

    // 课本198页题22
    cout << "\n课本198页题22" << endl;
    vector<工> 优2;
    vector<工> 集2 = {{1, 2, 40}, {2, 4, 15}, {3, 3, 60}, {4, 2, 20}, {5, 3, 10}, {6, 1, 45}, {7, 1, 55}};
    // 按利降序
    sort(集2.rbegin(), 集2.rend(), 比利);
    排工(集2, 优2);
    cout << "工集:" << 印工集(集2) << endl;
    cout << "优序:" << 印工集(优2) << endl;
    cout << "丄利:" << 求利(优2) << endl;
#endif

    // 期末题FB01
    cout << "\n期末题FB01" << endl;
    vector<工> 优3;
    vector<工> 集3 = {{1, 3, 30}, {2, 1, 25}, {3, 4, 40}, {4, 2, 10}, {5, 1, 35}, {6, 2, 50}, {7, 3, 45}};
    cout << "工集:" << 印工集(集3) << endl;
    // 按利降序
    sort(集3.rbegin(), 集3.rend(), 比利);
    排工(集3, 优3);
    cout << "工集:" << 印工集(集3) << endl;
    cout << "优序:" << 印工集(优3) << endl;
    cout << "丄利:" << 求利(优3) << endl;
    return 0;
}