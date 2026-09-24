#include <vector>
#include "insertionSort.cpp"
using namespace std;


void merge(vector<int> & arr, int left, int mid, int right)
{
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];

    while (i <= mid && j <= right)
    temp[k++] = arr[i++];

    while(j <= right) temp[k++] = arr[j++];


    for (int i = left; i <= right; i++)
    arr[i] = temp[i - left];
}

void mergeSort(vector<int>& arr, int left, int right, int threshold)
{
    if (right - left + 1<= threshold)
    {
        insertionSort(arr, left, right);
        return;
    }

    int mid = left + (right - left) /2;
    mergeSort(arr, left, mid, threshold);
    merge(arr, leftm mid, right);
}
    
