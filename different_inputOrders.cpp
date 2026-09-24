#include <iostream>
#include <vector>
#include <algorithm>
#include "testSorting.h"  // Assuming this header contains your sorting functions

using namespace std;

int main() {
    // Different array sizes to test
    int sizes[] = {1000, 10000, 100000};
    int thresholds[] = {5, 10, 20};

    for (int size : sizes) {
        // Generate different types of arrays
        vector<int> sortedArray = generateRandomArray(size);
        sort(sortedArray.begin(), sortedArray.end());  // Sort the array to create a sorted version
        
        vector<int> reverseSortedArray = sortedArray;
        reverse(reverseSortedArray.begin(), reverseSortedArray.end());  // Reverse to create reverse sorted array
        
        vector<int> randomArray = generateRandomArray(size);  // Random array for comparison

        for (int threshold : thresholds) {
            cout << "\nTesting array size: " << size << ", Threshold: " << threshold << endl;
            
            // Test sorting on sorted array
            cout << "Testing Sorted Array:\n";
            testSortingWithComparison(sortedArray, threshold);
            
            // Test sorting on reverse sorted array
            cout << "Testing Reverse Sorted Array:\n";
            testSortingWithComparison(reverseSortedArray, threshold);
            
            // Test sorting on random array
            cout << "Testing Random Array:\n";
            testSortingWithComparison(randomArray, threshold);
        }
    }

    return 0;
}

void testSortingWithComparison(vector<int> arr, int threshold) {
    // Copy array for comparison
    vector<int> arrCopy = arr;
    
    // Run your custom sorting methods
    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1, threshold);
    auto stop = chrono::high_resolution_clock::now();
    cout << "Merge Sort Time: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << " ms\n";
    
    // Run the standard sort() function for comparison
    start = chrono::high_resolution_clock::now();
    sort(arrCopy.begin(), arrCopy.end());
    stop = chrono::high_resolution_clock::now();
    cout << "std::sort Time: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << " ms\n";

    // Optionally, verify if both sorts are identical
    if (arr == arrCopy) {
        cout << "Both sorts produced the same result!" << endl;
    } else {
        cout << "There was a mismatch between the two sorting methods." << endl;
    }
}
