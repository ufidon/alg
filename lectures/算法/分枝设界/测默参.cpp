#include <iostream>

using namespace std;

int print(int a=2, int b=3)
{
	cout<<"(a,b)=("<<a<<","<<b<<")"<<endl;
	return a+b;
}

template <typename T1=int, int cap=10>
class Two{};

template <typename T1=double, typename T2=char>
class Shuang{};


int main()
{
	print();
	print(4);
	print(5,6);

	Two<double > two;
	Two<> t2;
	//Two<5> t3;
	Two<char, 2> t4;

	Shuang<int> s1;

	return 0;
}
