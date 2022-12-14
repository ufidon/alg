#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <string>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

// 最优二进制前缀码贪婪造法： Huffman算法

struct 点
{
    string 符;
    int 频次;
    点 *左子树;
    点 *右子树;
};

class 比点
{
public:
    bool operator()(点 *左, 点 *右)
    {
        return (左->频次 > 右->频次);
    }
};

void 印队(const priority_queue<点 *, vector<点 *>, 比点> &队)
{
    priority_queue<点 *, vector<点 *>, 比点> 队1 = 队;
    for (cout << "队: "; !队1.empty(); 队1.pop())
    {
        cout << 队1.top()->符 << ":" << 队1.top()->频次 << ":"
             << " ";
    }
    cout << endl;
}

void 印树(const 点 *父, int &深度, int &位数)
{
    if (!父)
        return;

    // 左序遍历
    cout << 父->符 << ":" << 父->频次 << ":" << 深度 << ":" << 位数;
    if (!父->右子树) //至叶, 最优码树为满树,查一枝即可
    {
        位数 += 深度 * 父->频次;
        return;
    }

    static int 此层 = ++深度;
    cout << "(";
    印树(父->左子树, 深度, 位数);
    cout << "|";
    深度 = 此层; // 左右同层
    印树(父->右子树, 深度, 位数);
    cout << ")";
}

点 *造优码(priority_queue<点 *, vector<点 *>, 比点> &符频队)
{
    int 字符数 = 符频队.size();
    for (int i = 1; i <= 字符数 - 1; i++)
    {
        点 *左 = 符频队.top();
        符频队.pop();
        点 *右 = 符频队.top();
        符频队.pop();

        点 *父 = new 点;

        父->左子树 = 左; // 左小右大(频次)
        父->右子树 = 右;
        父->频次 = 左->频次 + 右->频次;
        父->符 = 左->符 + 右->符;

        符频队.push(父);
        印队(符频队);
        cout << "树: ";
        int 深度 = 0, 位数 = 0;
        印树(父, 深度, 位数);
        cout << endl;
    }

    return 符频队.top();
}

int main()
{
    int 点数 = 6;
    vector<点 *> 符频列 = {new 点{"a", 16, 0, 0},
                           new 点{"b", 5, 0, 0},
                           new 点{"c", 12, 0, 0},
                           new 点{"d", 17, 0, 0},
                           new 点{"e", 10, 0, 0},
                           new 点{"f", 25, 0, 0}};

    priority_queue<点 *, vector<点 *>, 比点> 队;

    for (auto d : 符频列)
        队.push(d);

    印队(队);

    点 *根 = 造优码(队);
    cout << "总频次: " << 根->频次 << endl;

    cout << "树: ";
    int 深度=0, 位数 = 0;
    印树(根, 深度, 位数);
    cout << endl;
}
