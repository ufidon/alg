// C++ program for the above approach
// https://www.geeksforgeeks.org/power-set/
#include <iostream>
#include <algorithm>    // std::next_permutation, std::sort, std::reverse
#include <vector> 
using namespace std;

vector<vector<vector<char>>> combs(3);

// Function to print all the power set
void printPowerSet(char set[], int n)
{
	bool *contain = new bool[n]{0};
	combs[0] = vector<vector<char>>(3);
	combs[1] = vector<vector<char>>(3);
	combs[2] = vector<vector<char>>(1);
	
	// Empty subset
	cout << "" << endl;
	for(int i = 0; i < n; i++)
	{
		contain[i] = 1;
		// All permutation
		do
		{
		   int k=0;
			for(int j = 0; j < n; j++)
				if(contain[j])
				{
				    combs[i+1][k].push_back(set[j]);
					cout << set[j];
				}
			k++;
			cout << endl;
		} while(prev_permutation(contain, contain + n));
	}
}

/*Driver code*/
int main()
{
    
	char set[] = {'a','b','c'};
	printPowerSet(set, 3);
	
	for(int i=0; i<combs.size(); i++)
	{
	    for(int j=0; j<combs[i].size(); j++)
	    {
	        for(int k=0; k<combs[i][j].size(); k++)
	            cout<<combs[i][j][k] << " ";
	        
	        cout<<endl;
	    }
	}
	return 0;
}

