#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
using namespace std;
using namespace std::chrono;

void Magic(const int n) {
    const int MaxSize = 51;
    int square[MaxSize][MaxSize], k, l;
    if ((n > MaxSize) || (n < 1))
        throw "Error!..n out of range!";
    else if (n % 2 == 0)
        throw "Error!..n is even!";

    // Initialize the square array
    for (int i = 0; i < n; i++)
        fill(square[i], square[i] + n, 0); // Using STL to initialize
    
    square[0][(n - 1) / 2] = 1;
    int key = 2, i = 0, j = (n - 1) / 2;
    
    // Generate the magic square
    while (key <= n * n) {
        if (i - 1 < 0) k = n - 1;
        else k = i - 1;
        if (j - 1 < 0) l = n - 1;
        else l = j - 1;
        
        if (square[k][l]) {
            i = (i + 1) % n;
        } else {
            i = k;
            j = l;
        }
        
        square[i][j] = key;
        key++;
    }
}

void timeMagicFunction() {
    int sizes[] = {11, 21, 31, 41, 51};  // Magic square sizes
    for (int n : sizes) {
        cout << "Timing for magic square size: " << n << endl;
        for (int iterations = 10; iterations <= 100; iterations += 10) {
            auto start = high_resolution_clock::now();
            
            // Run the Magic function for specified iterations
            for (int i = 0; i < iterations; i++) {
                Magic(n);  // Call the Magic function without printing
            }
            
            auto end = high_resolution_clock::now();
            auto totalTime = duration_cast<microseconds>(end - start).count();
            double averageTime = static_cast<double>(totalTime) / iterations;

            // Output the total time and average time for each iteration count
            cout << "Iterations: " << iterations 
                 << " | Total time: " << totalTime << " microseconds"
                 << " | Average time: " << averageTime << " microseconds" << endl;
        }
        cout << endl;
    }
}

int main() {
    try {
        timeMagicFunction();  // Time the Magic function for different square sizes
    } catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}
