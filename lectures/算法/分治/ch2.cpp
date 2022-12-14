#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// common dataype and function
typedef int index;
typedef int keytype;

void copyarray(const keytype src[], keytype dst[], const int size){
    for (index i = 0; i < size; i++)
    {
        dst[i] = src[i];
    }   
}

void printarray(const keytype a[], const int size){
    for(int i=0; i<size; i++)
        cout << a[i] << " ";
    cout << endl;
}
// 2.1 binary search



index location(const int x, const int S[], index low, index high){

    index mid;
    if (low > high)
        return -1;
    else
    {
        mid = (low+high)/2;
        cout << setw(6) << low
        << setw(6) << mid
        << setw(6) << high
        << endl;
        // suppose the following comparison can be done in one instruction
        if (x == S[mid])
            return mid;
        else if(x<S[mid])
            return location(x, S, low, mid-1);
        else
            return location(x, S, mid+1, high);
        
    }    
}

index location3(const int x, const int S[], index low, index high){
    index m1,m2;
    if (low>high)
        return -1;
    else
    {
        m1 = low + (high-low)/3;
        m2 = low + 2*(high-low)/3;
        if(x==S[m1])
            return m1;
        else if(x<S[m1])
            return location3(x, S, low, m1-1);
        else if(x<S[m2])
            return location3(x, S, m1+1,m2-1);
        else if(x==S[m2])
            return m2;
        else
            return location3(x,S,m2+1,high);
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

void merge(int h, int m, const keytype U[], const keytype V[], keytype S[]){
    index i,j,k;
    i=0; j=0; k=0;
    while (i<h && j<m)
    {
        if(U[i] < V[j]){
            S[k] = U[i];
            i++;
        }
        else{
            S[k] = V[j];
            j++;
        }
        k++;
        if(i>=h)
            copyarray(V+j, S+k, m-j);
        else
            copyarray(U+i, S+k, h-i);
    }   
}

void mergesort(int n, keytype S[]){
    if (n>1)
    {
        int h=n/2, m=n-h;
        keytype* U = new keytype[h], *V= new keytype[m];
        copyarray(S, U, h);
        copyarray(S+h, V, m);
        mergesort(h, U);
        mergesort(m, V);
        merge(h,m,U,V,S);

        delete [] U;
        delete [] V;        
    } 
}

void merge2(keytype S[], keytype U[], index low, index mid, index high){
    index i,j,k;
    
    i=low; j=mid+1; k=low;

    while (i<=mid && j<=high){
        if (S[i] < S[j])
        {
            U[k] = S[i];
            i++;
        }else{
            U[k] = S[j];
            j++;
        }
        k++;
    }
    if (i> mid)
        copyarray(S+j, U+k, high-j+1);
    else
        copyarray(S+i, U+k, mid-i+1);

    copyarray(U, S, high-low+1);
    
}

void mergesort2(keytype S[],keytype U[], index low, index high){
    index mid;
    if (low<high)
    {
        mid = (low+high)/2;
        mergesort2(S,U, low, mid);
        mergesort2(S,U, mid+1, high);
        merge2(S,U, low, mid, high);
    }
}

int main(int argc, char* argv[]){
    if (argc < 3)
    {
        cout<<"\x1b[31mUsage:\x1b[1m " << argv[0] << "n1 n2 n3 ... nn x" << endl;
        return -1;
    }

    int x = atoi(argv[argc-1]);
    int slen = argc-2;
    int* S = new int[slen];    

    for (int i = 0; i < slen; i++)
    {
        S[i] = atoi(argv[i+1]);
    }
    index low = 0, high = slen-1;

    // binary search
    // cout<<left;
    // cout << setw(6) << "low"
    //     << setw(6) << "mid"
    //     << setw(6) << "high"
    //     << endl;
    // index xloc = location(x,S, low, high);

    // find maximum
    // index maxi = dcmax(S, low, high);
    // cout<<S[maxi] << " is the " << maxi << "th element"<<endl;

    //mergesort(slen, S);

    keytype *U = new keytype[slen];
    mergesort2(S,U, low, high);
    printarray(S, slen);
    printarray(U, slen);

    delete [] S; 
    
}