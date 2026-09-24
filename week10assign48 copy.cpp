#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Function to compute cycle length of n
int cycleLength(int n) {
    int length = 1; // Include n itself
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        length++;
    }
    return length;
}

int main() {
    int i, j;
    // Use cache to store cycle lengths to avoid recalculations
    unordered_map<int, int> cache;
    
    while (cin >> i >> j) {
        int maxCycleLength = 0;
        int start = min(i, j);
        int end = max(i, j);
        
        for (int k = start; k <= end; ++k) {
            if (cache.find(k) == cache.end()) {
                cache[k] = cycleLength(k);
            }
            maxCycleLength = max(maxCycleLength, cache[k]);
        }
        
        cout << i << " " << j << " " << maxCycleLength << endl;
    }

    return 0;
}
