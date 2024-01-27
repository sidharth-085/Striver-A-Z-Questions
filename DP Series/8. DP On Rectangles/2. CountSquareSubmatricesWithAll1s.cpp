#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

int countSquares(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    if (n == 0 || m == 0) {
        return 0;
    }

    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int col = 0; col < m; col++) {
        if (matrix[0][col] == 1) {
            dp[0][col] = 1;
        }
    }

    for (int row = 0; row < n; row++) {
        if (matrix[row][0] == 1) {
            dp[row][0] = 1;
        }
    }

    for (int row = 1; row < n; row++) {
        for (int col = 1; col < m; col++) {
            if (matrix[row][col] == 1) {
                int prevTop = dp[row - 1][col];
                int prevLeft = dp[row][col - 1];
                int prevDiagonal = dp[row - 1][col - 1];

                dp[row][col] = 1 + min(prevTop, min(prevDiagonal, prevLeft));
            }
            else {
                dp[row][col] = 0;
            }
        }
    }

    int count = 0;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            count += dp[row][col];
        }
    }

    return count;
}