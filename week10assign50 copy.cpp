#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Directions for the 8 adjacent cells
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void processField(int fieldNumber, char field[][100], int n, int m) {
    int result[100][100] = {0};

    // Calculate the number of mines around each cell
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i][j] == '*') {
                result[i][j] = -1; // Mark the mines separately
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && field[ni][nj] != '*') {
                        result[ni][nj]++;
                    }
                }
            }
        }
    }

    // Print the result for the current field
    printf("Field #%d:\n", fieldNumber);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (result[i][j] == -1) {
                printf("*");
            } else {
                printf("%d", result[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int n, m, fieldNumber = 0;
    char field[100][100];

    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 && m == 0) break;

        for (int i = 0; i < n; ++i) {
            scanf("%s", field[i]);
        }

        if (fieldNumber > 0) {
            printf("\n"); // Print an empty line between fields
        }
        fieldNumber++;
        processField(fieldNumber, field, n, m);
    }

    return 0;
}
