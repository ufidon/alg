#include <cstdlib>

#include "排组.h"
using namespace std;

int main(int argc, char **argv)
{
	//cs245::造排(atoi(argv[1]));
	for (int i = 1; i <= atoi(argv[1]); i++)
	{
		cs245::造组(atoi(argv[1]), i);
	}
	
	
	vector<int> 列 = cs245::组合数(atoi(argv[1]));
	cs245::印列(列);
	return 0;
}