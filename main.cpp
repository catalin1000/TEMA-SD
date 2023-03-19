#include <iostream>
#include <random>
#include<fstream>
#include<chrono>
#include<ctime>
#include<algorithm>
#include<vector>
using namespace std;
using namespace chrono;
ifstream in ("input.in");
ofstream out ("output.out");
int arr[100000001] ;
int v1[50000001];
int v2[50000001];
int v[100000001];
int buckets[100000001];



int maxim(int arr[], int n)///maxim
{
    int maxi = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxi)
            maxi = arr[i];
    return maxi;
}
bool test_sort(int v[], int n)
{
    for(int i=1; i<n; i++)
        if(v[i]<v[i-1])
            return false;
    return true;
}

void countingSort( int n, int exp)
{

    int i,counter[10]= {0};


    for (i=0; i<n; i++)
        counter[(arr[i] / exp) % 10]++; /// bucket pentru fiecare cifra in baza exponent

    for (i=1; i<10; i++)
        counter[i]+=counter[i-1];/// avem numarul total de numere , practic counter[9]==n

    for (i =n-1; i>=0; i--) /// iau array-ul descrescator
    {
        buckets[counter[(arr[i]/exp)%10]-1]=arr[i];/// asez numerele ordonate dupa cifra, practic ce are cifra 9 se pune la sfarsit, ce e 0 este la inceput
        counter[(arr[i]/exp)%10]--; /// imi scade indexul de la digit counter
    }


    for (i=0; i<n; i++)
        arr[i] = buckets[i];/// imi trebuie noua varianta a array-ului, cea sortata , de aceea copiez
}

void radixSort( int n)
{

    int m = maxim(arr, n);


    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSort(n, exp);
}


void print(int arr[], int n)
{
    for (int i=0; i<n; i++)
        cout<<arr[i]<<" ";
}



void mergeSort(int inc,int sf)
{
    /// IMPARTIREA IN JUMATATI
    int mij=inc +(sf-inc)/2;
    int n1=mij-inc+1;
    int n2=sf-mij;
    //  int v1[n1],v2[n2];
    for(int i=inc; i<=mij; i++)
        v1[i-inc]=v[i];
    for(int i=mij+1; i<=sf; i++)
        v2[i-mij-1]=v[i];





    /// INTERCLASARE
    int i,j,l;
    i=j=0;///i pentru v1 si j pentru v2
    l=inc;
    while(i<n1 && j<n2)
    {
        if(v1[i]<v2[j])
        {
            v[l]=v1[i];
            l++;
            i++;
        }
        else
        {
            v[l]=v2[j];
            l++;
            j++;
        }

    }

    while(j<n2)
    {
        v[l]=v2[j];
        l++;
        j++;
    }



    while(i<n1)
    {
        v[l]=v1[i];
        l++;
        i++;
    }





}
void merge_sort(int inc,int sf)
{
    if(inc>=sf)
        return;
    else
    {
        int mij=inc+(sf-inc)/2;
        merge_sort(inc,mij);
        merge_sort(mij+1,sf);
        mergeSort(inc,sf);
    }
}
void shellSort(int n)
{

    for (int gap=n/2; gap>0; gap/=2)/// luam primul gap de marime n/2 si apoi tot divizam , de unde avem O(log n)
    {

        for (int i=gap; i<n; i++)/// mergem in dreapta array-ului
        {

            int primul=arr[i];/// tinem minte prima valoarea de unde mergem cu gap-ul


            int j;
            for (j=i; j>=gap && arr[j-gap]>primul; j-=gap)

                arr[j]=arr[j-gap];/// elementul din dreapta gap-ului ia valoarea celui din stanga daca este mai mic

            ///  punem elementul pe care l-am comparat pe pozitia pana la care a mers comparartia
            arr[j]=primul;
        }
    }
}

int alegerePivot4(int left, int right)
{
    return v[left];
}


int alegerePivot3(int left,int right)
{
     random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
    return v[(distribution(generator)%(right-left))+left];

}

int alegerePivot2(int left,int right)
{
     int v3[3],s=0;
s+=v[left]+v[(right+left)/2]+v[right];//mediana medianelor
return s/3;
}
int alegerePivot1(int left, int right)
{
    int v3[3],s=0;
//s+=v[left]+v[(right+left)/2]+v[right];//mediana medianelor
//return s/3;
    v3[0]=v[left];
    v3[1]=v[(right+left)/2];
    v3[2]=v[right];
    if((v3[0]>=v3[1] && v3[1]>=v3[2]) || (v3[2]>=v3[1] && v3[1]>=v3[0]) )
        return v3[1];
    if((v3[1]>=v3[0] && v3[0]>=v3[2]) || (v3[2]>=v3[0] && v3[0]>=v3[1]) )
        return v3[0];
    if((v3[0]>=v3[2] && v3[2]>=v3[1]) || (v3[1]>=v3[2] && v3[2]>=v3[0]) )
        return v3[2];

    /*int v3[5];
        v3[0]=v[left];
        v3[1]=v[left/2+(right+left)/4];
        v3[2]=v[(right+left)/2];
        v3[3]=v[right/2+(right+left)/4];
        v3[4]=v[right];
        for(int i=0; i<3; i++)
            for(int j=i+1; j<5; j++)

                if(arr[i]>arr[j])
                    swap(arr[i],arr[j]);
            return v3[2];
            */
}
void quickSort1(int left, int right)
{

    int i=left, j=right;

    //int pivot=v[rand()%(right-left)+left];
    //int pivot=v[i];
    int pivot=alegerePivot1(left,right);



///INTERSCHMB VALORILE CARE SUNT INAINTE SI DUPA PIVOT,cele mai mici trebuie inainte ,iar restul dupa
    while (i<=j)
    {

        while (v[i]<pivot)

            i++;

        while (v[j]>pivot)

            j--;

        if (i<=j)
        {
            swap(v[i],v[j]);
            i++;
            j--;

        }

    };
///continuam quicksort-ul din cu celelalte bucati din array
    if (left<j)
        quickSort1(left,j);

    if (i<right)
        quickSort1(i,right);
}

void quickSort2(int left, int right)
{

    int i=left, j=right;

    //int pivot=v[rand()%(right-left)+left];
    //int pivot=v[i];
    int pivot=alegerePivot2(left,right);



///INTERSCHMB VALORILE CARE SUNT INAINTE SI DUPA PIVOT,cele mai mici trebuie inainte ,iar restul dupa
    while (i<=j)
    {

        while (v[i]<pivot)

            i++;

        while (v[j]>pivot)

            j--;

        if (i<=j)
        {
            swap(v[i],v[j]);
            i++;
            j--;

        }

    };
///continuam quicksort-ul din cu celelalte bucati din array
    if (left<j)
        quickSort2(left,j);

    if (i<right)
        quickSort2(i,right);
}

void quickSort3(int left, int right)
{

    int i=left, j=right;

    //int pivot=v[rand()%(right-left)+left];
    //int pivot=v[i];
    int pivot=alegerePivot3(left,right);



///INTERSCHMB VALORILE CARE SUNT INAINTE SI DUPA PIVOT,cele mai mici trebuie inainte ,iar restul dupa
    while (i<=j)
    {

        while (v[i]<pivot)

            i++;

        while (v[j]>pivot)

            j--;

        if (i<=j)
        {
            swap(v[i],v[j]);
            i++;
            j--;

        }

    };
///continuam quicksort-ul din cu celelalte bucati din array
    if (left<j)
        quickSort3(left,j);

    if (i<right)
        quickSort3(i,right);
}

void quickSort4(int left, int right)
{

    int i=left, j=right;

    //int pivot=v[rand()%(right-left)+left];
    //int pivot=v[i];
    int pivot=alegerePivot4(left,right);



///INTERSCHMB VALORILE CARE SUNT INAINTE SI DUPA PIVOT,cele mai mici trebuie inainte ,iar restul dupa
    while (i<=j)
    {

        while (v[i]<pivot)

            i++;

        while (v[j]>pivot)

            j--;

        if (i<=j)
        {
            swap(v[i],v[j]);
            i++;
            j--;

        }

    };
///continuam quicksort-ul din cu celelalte bucati din array
    if (left<j)
        quickSort4(left,j);

    if (i<right)
        quickSort4(i,right);
}

int main()
{

    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
    cout<<"Pentru citire de la fisier apasati 1, iar in caz contrar alt numar: ";
    int citire;
    cin>>citire;

    int n,nmax;
   // cout<<"Vectorul este sortat crescator \n";
if (citire!=1)
 {
    cout<<"Introduceti numarul de elemente din sir: ";
    cin>>n;
    cout<<"Introduceti valoarea maxima pe care o doriti sa aiba numerele: ";
    cin>>nmax;
}
    if(citire!=1)
    for(int i=0; i<n; ++i)
        v[i]=arr[i]=distribution(generator)%(nmax+1);
        else
        {  n=0;
            while(in>>citire)
            {
                v[n]=arr[n]=citire;
                n++;
            }
        }

    auto start = high_resolution_clock::now();
    radixSort(n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent radixSort-ului este: "<<duration.count() << endl;
    cout<<test_sort(arr,n);
    ///print(arr, n);
    for(int i=0; i<n; ++i)
        arr[i]=v[i];




    cout<<endl;
    start = high_resolution_clock::now();
    merge_sort(0,n-1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent mergeSort-ului este: "<<duration.count() << endl;
    cout<<test_sort(v,n);
    for(int i=0; i<n; ++i)
        v[i]=arr[i];

    cout<<endl;
    start = high_resolution_clock::now();
    shellSort(n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent shellSort-ului este: "<<duration.count() << endl;
    cout<<test_sort(arr,n);


    for(int i=0; i<n; ++i)
        arr[i]=v[i];

    cout<<endl;
    start = high_resolution_clock::now();
    quickSort1(0,n-1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent quickSort-ului este: "<<duration.count() << endl;
    cout<<test_sort(v,n);

    for(int i=0; i<n; ++i)
        v[i]=arr[i];
    cout<<endl;
    start = high_resolution_clock::now();
    sort(v,v+n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent sortarii native din c++ este: "<<duration.count() << endl;
    cout<<test_sort(v,n);




    start = high_resolution_clock::now();
    bool ok;
    do
    {
        ok=0;
        for(int i=0; i<n-1; i++)
        {
            if(arr[i]>arr[i+1])
            {
                swap(arr[i],arr[i+1]);
                ok=1;

            }
        }

    }
    while(ok);

    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<endl;
    cout<<"Timpul de executie aferent bubleSort-ului este: "<<duration.count() << endl;
    cout<<test_sort(arr,n)<<endl;
    cout<<v[n-1];
    //print(v,n);


/**


    auto start = high_resolution_clock::now();
    quickSort1(0,n-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent quickSort-ului cu pivotul ca fiind mediana din 3 este: "<<duration.count() << endl;
    cout<<test_sort(v,n);
    ///print(arr, n);
    for(int i=0; i<n; ++i)
        v[i]=arr[i];




    cout<<endl;
    start = high_resolution_clock::now();
    quickSort2(0,n-1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent quickSort-ului cu pivotul ca fiind mediana medianelor este: "<<duration.count() << endl;
    cout<<test_sort(v,n);
    for(int i=0; i<n; ++i)
        v[i]=arr[i];

    cout<<endl;
    start = high_resolution_clock::now();
    quickSort3(0,n-1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent quickSort-ului cu pivotul generat random este: "<<duration.count() << endl;
    cout<<test_sort(v,n);


    for(int i=0; i<n; ++i)
        v[i]=arr[i];

    cout<<endl;
    start = high_resolution_clock::now();
    quickSort4(0,n-1);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Timpul de executie aferent quickSort-ului cu pivotul ca fiind primul element din stanga este: "<<duration.count() << endl;
    cout<<test_sort(v,n);

*/
    return 0;






}

