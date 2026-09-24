#include <vector>
#include <cstlib>
#include <ctime>
using namespace std;

//this is used to generate random array of given size
vector<int>generateRandomArray(int size)
{
    vector<int> arr[size];

    for (int i = 0; i < size, ++i)
    
    arr[i] = rand();
    return arr;
}
