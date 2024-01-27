#include <iostream>
#include <vector>
using namespace std;

// IMP NOTE: In problem like Infinite supply of something which can be anything
// coins, weights, etc. We can optimize this solution till single 1-D array.

// This problem is similar to other problems like waysToMakeCoinChange, Unbounded
// Knapsack. We have infinite supply of cutting of rod in this case of particular
// size of cutting i.e. (index + 1)

// Approach 1: Recursive Approach
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int cutRodHelper(int index, int length, int n, vector<int> &price) {
    // Base case: If the length is 0, the revenue is 0.
    if (length == 0) {
        return 0;
    }

    // Base case: If we've reached the first piece, the revenue is the price of the first piece multiplied by the remaining length.
    if (index == 0) {
        return (price[0] * length);
    }

    // Calculate the maximum revenue by either including or excluding the current piece.
    int include = 0;
    if (index + 1 <= length) {
        include = price[index] + cutRodHelper(index, length - index - 1, n, price);
    }

    int notInclude = cutRodHelper(index - 1, length, n, price);

    // Return the maximum of including and not including the current piece.
    return max(include, notInclude);
}

int cutRod(vector<int> &price, int n) {
    return cutRodHelper(n - 1, n, n, price);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

int cutRodHelper(int index, int length, int n, vector<int> &price, vector<vector<int>> &dp) {
    if (length == 0) {
        return 0;
    }

    if (index == 0) {
        return (price[0] * length);
    }

    // If the result is already computed, return it from the dp table.
    if (dp[index][length] != -1) {
        return dp[index][length];
    }

    // Calculate the maximum revenue by either including or excluding the current piece.
    int include = 0;
    if (index + 1 <= length) {
        include = price[index] + cutRodHelper(index, length - index - 1, n, price, dp);
    }

    int notInclude = cutRodHelper(index - 1, length, n, price, dp);

    // Store the result in the dp table and return it.
    return dp[index][length] = max(include, notInclude);
}

int cutRod(vector<int> &price, int n) {
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));

    return cutRodHelper(n - 1, n, n, price, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

int cutRod(vector<int> &price, int n) {
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));

    // Initialize the dp table for base cases.
    for (int index = 0; index < n; index++) {
        dp[index][0] = 0;
    }

    for (int length = 1; length <= n; length++) {
        dp[0][length] = (price[0] * length);
    }

    // Fill in the dp table using dynamic programming.
    for (int index = 1; index < n; index++) {
        for (int length = 1; length <= n; length++) {
            int include = 0;
            if (index + 1 <= length) {
                include = price[index] + dp[index][length - index - 1];
            }

            int notInclude = dp[index - 1][length];

            dp[index][length] = max(include, notInclude);
        }
    }

    // Return the result from the bottom-right cell of the dp table.
    return dp[n - 1][n];
}

// Approach 4: Space Optimization Approach (Two 1-D array)
// Time Complexity: O(N * N)
// Space Complexity: O(2 * N)

int cutRod(vector<int> &price, int n) {
    vector<int> prev(n + 1, -1);

    prev[0] = 0;

    for (int length = 1; length <= n; length++) {
        prev[length] = (price[0] * length);
    }

    // Fill in the dp table using dynamic programming.
    for (int index = 1; index < n; index++) {
        vector<int> curr(n + 1, -1);
        curr[0] = 0;

        for (int length = 1; length <= n; length++) {
            int include = 0;
            if (index + 1 <= length) {
                include = price[index] + curr[length - index - 1];
            }

            int notInclude = prev[length];

            curr[length] = max(include, notInclude);
        }

        // Update the previous array for the next iteration.
        prev = curr;
    }

    // Return the result from the last iteration of the previous array.
    return prev[n];
}

// Approach 5: Space Optimization Approach (One 1-D array)
// Time Complexity: O(N * N)
// Space Complexity: O(N)

int cutRod(vector<int> &price, int n) {
    vector<int> prev(n + 1, -1);

    prev[0] = 0;

    for (int length = 1; length <= n; length++) {
        prev[length] = (price[0] * length);
    }

    // Fill in the dp table using dynamic programming.
    for (int index = 1; index < n; index++) {
        for (int length = 1; length <= n; length++) {
            int include = 0;
            if (index + 1 <= length) {
                include = price[index] + prev[length - index - 1];
            }

            int notInclude = prev[length];

            prev[length] = max(include, notInclude);
        }
    }

    // Return the result from the last iteration of the previous array.
    return prev[n];
}