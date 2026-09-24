#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if all characters in the square of given side length are the same
bool isValidSquare(const vector<string>& grid, int r, int c, int sideLength) {
    char ch = grid[r][c];
    int half = sideLength / 2;
    for (int i = r - half; i <= r + half; ++i) {
        for (int j = c - half; j <= c + half; ++j) {
            if (grid[i][j] != ch) return false;
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int M, N, Q;
        cin >> M >> N >> Q;
        
        vector<string> grid(M);
        for (int i = 0; i < M; ++i) {
            cin >> grid[i];
        }

        cout << M << " " << N << " " << Q << endl;

        while (Q--) {
            int r, c;
            cin >> r >> c;

            int maxLength = 1; // Minimum size is 1 (the center itself)
            int sideLength = 1;

            while (true) {
                int half = sideLength / 2;
                if (r - half < 0 || r + half >= M || c - half < 0 || c + half >= N) break;
                if (!isValidSquare(grid, r, c, sideLength)) break;

                maxLength = sideLength;
                sideLength += 2;
            }

            cout << maxLength << endl;
        }
    }

    return 0;
}
