#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    vector<string> 币名列;
    vector<int> 币值列;

    string 币名;
    int 币值, 零钱;

    cout << "降序输入可用硬币币值(以0结束): ";
    while (cin >> 币值)
    {
        if(币值 == 0) break;

        币值列.push_back(币值);
    }
    for (int i = 0; i < 币值列.size(); i++)
    {
        cout << 币值列[i] << " ";
    }
    cout << endl;

    cout << "输入上述硬币名称(以止结束): ";
    while (cin >> 币名)
    {
        if(币名 == "止") break;

        币名列.push_back(币名);
    }
    for (int i = 0; i < 币名列.size(); i++)
    {
        cout << 币名列[i] << " ";
    }
    cout << endl;

    cout<<"您要换多少零钱？ ";
    cin>> 零钱;

    cout<<"这是您的零钱: "<<endl;;
    cout<<left;
    cout<<setw(10)<<"硬币"<<setw(6)<<"个数"<<endl;
    for (int i = 0; i < 币值列.size(); i++)
    {
        cout <<setw(10)<<币名列[i]<<setw(6)<<零钱/币值列[i]<<endl;
        零钱 %= 币值列[i];
    }
    

    return 0;
}