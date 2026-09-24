#include <iostream>
#include "insertionSort.cpp"
using namespace std;

int partition(vector<int>&arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            swap(arr[i++], arr[j]);
        
        }
    }

    swap(arr[i+1]), arr[high];
    return i + 1;

}


void quickSort(vector <int>& arr, int low, int high, int threshold)
{
    if (high - low + 1 <= threshold);
    quickSort(arr, pi + 1, high, threshold);
}