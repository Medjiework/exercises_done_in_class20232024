#include <iostream>
#include <chrono>
#include "mergeSort.cpp"
#include "quickSort.cpp"
#include "generateArray.cpp"

using namespace std;
using namespace chrono;

//create to test the two functions time execution
void test_Sorting(int size, int threshold)
{
    vector <int> arr1 = generateRandomArray(size);
    vector<int> arr2 = arr1;

    cout << size << ", " << threshold << endl;

    auto start = high_resolution_clock::now();
    mergeSort(arr1, 0, size - 1, threshold);
    auto stop = high_resolution_clock::now();
    cout << "Merge Sort execution time" << duration_cast < milliseconds> (stop - start).count() << " m/s\n";


    start = high_resolution_clock::now();
    quickSort(arr2, 0, size - 1, threshold);
    stop = high_resolution_clock::now();
    cout << "Quick Sort time execution: " << duration_cast<milliseconds> (stop - start).count() << " m/s\n";
}