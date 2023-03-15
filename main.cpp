#include <iostream>
#include <random>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<chrono>
#include<ctime>
using namespace std;
using namespace chrono;
int arr[100000000] ;
int output[100000000];
// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
bool check(int v[], int n)
{
    for(int i=1;i<n;i++)
        if(v[i]<v[i-1])
        return false;
    return true;
}
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort( int n, int exp)
{
     // output array
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++; // bucket pentru fiecare cifra in baza exponent

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];// asez numarul pe pozitia buna
        count[(arr[i] / exp) % 10]--; // imi scade cand am luat un numar din bucket si mi-l baga in output
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];// copiez copia array-ului in array, avand deja cifra curenta sortata
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort( int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(n, exp);
}

// A utility function to print an array
void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

// Driver Code
int main()
{
     srand(time(0)); // initialize random seed

    int n;
    cin>>n;
     for(int i=0;i<n;++i)
        arr[i]=rand()%1000000;
      // Function Call
 auto start = high_resolution_clock::now();
      radixsort(n);
       auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
      cout<<"Timp de executie pentru testul"<<" de la radixsort este "<<duration.count() << endl;
      cout<<check(arr,n);
   // print(arr, n);
    return 0;
}
