#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>


// common dataype and function
typedef int index;
typedef int keytype;
typedef int number;

void copyarray(const keytype src[], keytype dst[], const int size) {
	for (index i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

void copyarray1(const keytype src[], keytype dst[], const int size) {
	for (index i = 1; i <= size; i++)
	{
		dst[i] = src[i];
	}
}

void copyarray(const keytype src[], keytype dst[], const int low, const int high) {
	for (index i = low; i <= high; i++)
	{
		dst[i] = src[i];
	}
}

void printarray(const keytype a[], const int low, const int high) {
	std::cout << std::left;
	std::cout << std::setw(10) << "Index: ";
	for (int i = low; i <= high; i++)
		std::cout << std::setw(6) << i;
	std::cout << std::endl;
	std::cout << std::setw(10) << "Element: ";
	for (int i = low; i <= high; i++)
		std::cout << std::setw(6) << a[i];
	std::cout << std::endl;
}

void printarray(const keytype a[], // requirement: size(a) > n
	const int n) {
	std::cout << std::left;
	std::cout << std::setw(10) << "Index: ";
	for (int i = 1; i <= n; i++)
		std::cout << std::setw(6) << i;
	std::cout << std::endl;
	std::cout << std::setw(10) << "Element: ";
	for (int i = 1; i <= n; i++)
		std::cout << std::setw(6) << a[i];
	std::cout << std::endl;
}

void showarray(const keytype a[], const int low, const int high) {
	std::cout << std::left;
	for (int i = low; i <= high; i++)
		std::cout << std::setw(6) << a[i];
}

void showarray(const keytype a[], 
	const int n) {
	std::cout << std::left;
	for (int i = 0; i < n; i++)
		std::cout << std::setw(6) << a[i];
}
// 2.1 binary search
// Algorithm 2.1 Binary Search (Recursive) p54
// worst-case # of division = floor(log2(n)) + 1
index location(const int x,
	const int S[],
	index low,
	index high,
	int& count) {

	index mid;
	if (low > high)
		return 0;
	else
	{
		count++; // count the times of division

		mid = (low + high) / 2;
		std::cout << std::setw(6) << count << ": "
			<< std::setw(6) << low
			<< std::setw(6) << mid
			<< std::setw(6) << high
			<< std::endl;
		// suppose the following comparison can be done in one instruction
		if (x == S[mid])
			return mid;
		else if (x < S[mid])
			return location(x, S, low, mid - 1, count);
		else
			return location(x, S, mid + 1, high, count);

	}
}

index location3(const int x, const int S[], index low, index high) {
	index m1, m2;
	if (low > high)
		return -1;
	else
	{
		m1 = low + (high - low) / 3;
		m2 = low + 2 * (high - low) / 3;
		if (x == S[m1])
			return m1;
		else if (x < S[m1])
			return location3(x, S, low, m1 - 1);
		else if (x < S[m2])
			return location3(x, S, m1 + 1, m2 - 1);
		else if (x == S[m2])
			return m2;
		else
			return location3(x, S, m2 + 1, high);
	}
}

int dcmax(const int S[], index low, index high) {
	if (low == high)
		return low;

	index mid = (low + high) / 2;
	index l = dcmax(S, low, mid);
	index r = dcmax(S, mid + 1, high);

	if (S[l] > S[r])
		return l;
	else
		return r;
}

// 2.2 Mergesort
// algorithm 2.3 p59
void merge(int h, int m, const keytype U[], const keytype V[], keytype S[], 
	int& count
) {
	index i, j, k;
	i = 0; j = 0; k = 0;
	while (i < h && j < m)
	{
		count++;
		if (U[i] < V[j]) {
			
			S[k] = U[i];
			i++;
		}
		else {
			S[k] = V[j];
			j++;
		}
		k++;
		if (i >= h)
			copyarray(V + j, S + k, m - j);
		else
			copyarray(U + i, S + k, h - i);
	}
	showarray(S,0, k);
	std::cout << std::endl;
}
// algorithm 2.2 p59
void mergesort(int n, keytype S[], int& count) {
	if (n > 1)
	{
		int h = n / 2, m = n - h;
		keytype* U = new keytype[h], * V = new keytype[m];
		copyarray(S, U, h);
		copyarray(S + h, V, m);

		std::cout << "partition..." << std::endl;
		showarray(U, h);
		std::cout << " | ";
		showarray(V, m);
		std::cout << std::endl;

		mergesort(h, U, count);
		mergesort(m, V, count);

		std::cout << "merge..." << std::endl;
		merge(h, m, U, V, S, count);

		delete[] U;
		delete[] V;
	}
}

void merge(keytype S[], keytype U[], index low, index mid, index high, 
	int& count) {
	index i, j, k;

	i = low; j = mid + 1; k = low;
	while (i <= mid && j <= high) {
		count++;
		if (S[i] < S[j])
		{
			
			U[k] = S[i];
			i++;
		}
		else {
			U[k] = S[j];
			j++;
		}
		k++;
	}
	if (i > mid)
		copyarray(S + j, U + k, high - j + 1);
	else
		copyarray(S + i, U + k, mid - i + 1);

	copyarray(U+low, S+low, high - low + 1);
	showarray(S, low, high);
	std::cout << std::endl;
}

void mergesort(keytype S[], keytype U[], index low, index high, int& count) {
	index mid;
	if (low < high)
	{
		mid = (low + high) / 2;

		std::cout << "partition..." << std::endl;
		showarray(S, low, mid);
		std::cout << " | ";
		showarray(S, mid+1, high);
		std::cout << std::endl;

		mergesort(S, U, low, mid, count);
		mergesort(S, U, mid + 1, high, count);

		std::cout << "merge..." << std::endl;
		merge(S, U, low, mid, high, count);
	}

}

// algorithm 2.7 p66
void partition(keytype S[], index low, index high, index& pivotindex,
	int& count) {
	index i, j;
	keytype pivotitem;

	pivotitem = S[low]; // first item for pivot
	j = low;
	for ( i = low+1; i <= high ; i++)
	{
		count++;
		if (S[i] < pivotitem) {
			
			j++;
			std::swap(S[i], S[j]);
		}
	}
	pivotindex = j;
	std::swap(S[low], S[pivotindex]);

}

// algorithm 2.6 p65
void quicksort(keytype S[], index low, index high, 
	int& count)
{
	index pivotindex;
	if (high>low)
	{
		partition(S, low, high, pivotindex, count);
		std::cout << "partition..." << std::endl;
		showarray(S, low, pivotindex-1);
		std::cout << " | " << S[pivotindex] << " | ";
		showarray(S, pivotindex + 1, high);
		std::cout << std::endl;

		quicksort(S, low, pivotindex - 1, count);
		quicksort(S, pivotindex + 1, high, count);
	}
}


int main(int argc, char* argv[]) {

	//---------inputs from command line-------------
	//if (argc < 3)
	//{
	//    std::cout << "\x1b[31mUsage:\x1b[1m " << argv[0] << "n1 n2 n3 ... nn x" << std::endl;
	//    return -1;
	//}

	//int x = atoi(argv[argc - 1]);
	//int slen = argc - 2;
	//int* S = new int[slen];

	//for (int i = 0; i < slen; i++)
	//{
	//    S[i] = atoi(argv[i + 1]);
	//}
	//index low = 0, high = slen - 1;

	//--------- binary search--------------------
	//index low = 0, high = 12;
	//int count = 0;
	//number S[13] = { 10,12,13,14,18,20,25,27,30,35,40,45,47 };
	//number x = 18;
	//printarray(S, low, high);

	//std::cout << std::left;
	//std::cout << std::setw(6) << "count"
	//	<< std::setw(6) << "low"
	//	<< std::setw(6) << "mid"
	//	<< std::setw(6) << "high" << std::endl;
	//std::cout << "search for " << x << std::endl;
	//index xloc = location(x, S, low, high, count);
	//x = 7; count = 0;
	//std::cout << "search for " << x << std::endl;
	//xloc = location(x, S, low, high, count);
	//x = 70; count = 0;
	//std::cout << "search for " << x << std::endl;
	//xloc = location(x, S, low, high, count);

	// find maximum
	// index maxi = dcmax(S, low, high);
	// std::cout<<S[maxi] << " is the " << maxi << "th element"<<std::endl;

	//---------merge sort---------------------
	// int n = 8, count=0;
	// number S[8] = { 27, 10,12,20,25,13,15,22 };
	// number U[8];

	// //mergesort(n, S, count);
	// mergesort(S, U, 0, 7, count);

	// printarray(S, 0, n-1);
	// std::cout << "\nTime complexity: " << count << std::endl;

	// mergesort2(S, low, high);
	// printarray(S, slen);

	//---------quick sort--------------------
	keytype S[8] = { 15,22,13,27,12,10,20,25 };
	int n = 8, count=0;
	index low = 0, high = n - 1;
	quicksort(S, low, high, count);
	printarray(S, low, high);
	std::cout << "\nTime complexity: " << count << std::endl;

   /* delete[] S;*/

}