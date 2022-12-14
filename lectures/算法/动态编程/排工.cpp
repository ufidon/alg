#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

// 最小化系统等待及服务时间
// 无截时
typedef pair<int, double> 工; // <工号,工时>

bool 比工时(工 &甲, 工 &乙)
{
    return (甲.second < 乙.second);
}

void 排无截(const vector<工> &工集,
            vector<工> &最优工序,
            double &最小伺时,
            vector<工> &最差工序,
            double &最大伺时)
{
    // 用排序不等式求解
    int 工数 = 工集.size();
    最优工序 = 工集; // 按工时升序
    sort(最优工序.begin(), 最优工序.end(), 比工时);

    最差工序 = 工集; // 按工时降序
    sort(最差工序.rbegin(), 最差工序.rend(), 比工时);
    最小伺时 = 最大伺时 = 0;

    for (int i = 0; i < 工数; i++)
    {
        最小伺时 += (工数 - i) * 最优工序[i].second;
        最大伺时 += (工数 - i) * 最差工序[i].second;
    }
}

void 印工序(const vector<工> &工集)
{
    double 全时 = 0;
    int 工数 = 工集.size();

    cout << "[";
    for (int i = 0; i < 工数; i++)
    {
        cout << left << setw(2) << 工集[i].first << "(" << setw(3) << 工集[i].second << ")" << ((i == 工数 - 1) ? "" : ",");
        全时 += (工数 - i) * 工集[i].second;
    }
    cout << "] = " << 全时 << endl;
}

void 印工序(const vector<double> 工集, const vector<int> 号集, double& 全时)
{
    int 工数 = 工集.size();
    全时 = 0;
    cout << "[";
    for (int i = 0; i < 工数; i++)
    {
        cout << left << setw(2) << (号集[i] + 1) << "(" << setw(3) << 工集[号集[i]] << ")" << ((i == 工数 - 1) ? "" : ",");
        全时 += (工数 - i) * 工集[号集[i]];
    }
    cout << "] = " << 全时 << endl;
}

void 排无截(const vector<double> &工集, vector<int> &最优工序, vector<int> &最差工序)
{

    double 全时 = 0;
    int 工数 = 工集.size();
    vector<int> 号集(工数);

    iota(号集.begin(), 号集.end(), 0);
    double 最省时 = INFINITY;
    double 最耗时 = 0;
    do
    {
        印工序(工集, 号集, 全时);
        if (最省时 > 全时)
        {
            最省时 = 全时;
            最优工序 = 号集;
        }
        if (最耗时 < 全时)
        {
            最耗时 = 全时;
            最差工序 = 号集;
        }

    } while (next_permutation(号集.begin(), 号集.end()));
}

int main()
{
    vector<double> 工集;
    vector<工> 工集2;

    double 工时, 全时 = 0;
    int 工号 = 1;
    cout << "输入各工时(以0结束): ";
    while (cin >> 工时)
    {
        cout<<"工号: " << 工号 << " 工时: " << 工时<<endl;
        if (工时 == 0)
            break;

        工集.push_back(工时);
        工集2.push_back(工(工号, 工时));
        工号++;
    }
    int 工数 = 工集.size();
    vector<int> 最优工序(工数);
    vector<int> 最差工序(工数);

    排无截(工集, 最优工序, 最差工序);

    cout << "最优工序: " << endl;
    印工序(工集, 最优工序, 全时);
    cout << "最差工序: " << endl;
    印工序(工集, 最差工序, 全时);

    double 最长耗时 = 0, 最短耗时 = 0;
    vector<工> 差工序(工数);
    vector<工> 良工序(工数);

    排无截(工集2, 良工序, 最短耗时, 差工序, 最长耗时);
    cout << "最优工序: " << endl;
    印工序(良工序);
    cout << "最差工序: " << endl;
    印工序(差工序);    

    return 0;
}