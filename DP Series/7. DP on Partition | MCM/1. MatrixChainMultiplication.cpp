#include <iostream>
#include <vector>
using namespace std;

// This is the new pattern of DP, so in which we have to follow different approach
// so what we will do is, we take two variables start and end to denote the
// starting and ending points of the partition. Then, we will apply the partition 
// one by one and check the number of operations to multiply them. Then finally 
// take minimum operations.

// Approach 1: Recursive Approach
// Time Complexity: Exponential
// Space Complexity: O(N)

int helper(int start, int end, int *arr) {
    // Base case: If the start and end indices are the same, no multiplication is needed.
    if (start == end) {
        return 0;
    }

    int minMultiplications = INT_MAX;

    // Iterate through possible positions to split the matrix chain.
    for (int index = start; index < end; index++) {
        // Recursive calls to find the minimum cost for the left and right sub-chains.
        int firstBracket = helper(start, index, arr);
        int secondBracket = helper(index + 1, end, arr);

        // Calculate the total cost for the current split and update minMultiplications.
        int multiplications = firstBracket + secondBracket + (arr[start - 1] * arr[index] * arr[end]);
        minMultiplications = min(minMultiplications, multiplications);
    }

    return minMultiplications;
}

int matrixChainMultiplication(int* arr, int n) {
    return helper(1, n, arr);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * N * N)
// Space Complexity: O(N * N)

int helper(int start, int end, int *arr, vector<vector<int>> &dp) {
    // Base case: If the start and end indices are the same, no multiplication is needed.
    if (start >= end) {
        return 0;
    }

    // If the result for this subproblem is already computed, return it.
    if (dp[start][end] != -1) {
        return dp[start][end];
    }

    int minMultiplications = INT_MAX;

    for (int index = start; index < end; index++) {
        int firstBracket = helper(start, index, arr, dp);
        int secondBracket = helper(index + 1, end, arr, dp);

        int multiplications = firstBracket + secondBracket + (arr[start - 1] * arr[index] * arr[end]);

        minMultiplications = min(minMultiplications, multiplications);
    }

    // Store the result in the DP table and return it.
    return dp[start][end] = minMultiplications;
}

int matrixChainMultiplication(int* arr, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

    return helper(1, n, arr, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * N * N)
// Space Complexity: O(N * N)

int matrixChainMultiplication(int* arr, int n) {
    // Create a 2D DP table to store minimum multiplications.
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Loop over the matrix chain lengths, starting from the shortest to the longest.
    for (int start = n; start >= 1; start--) {
        for (int end = 1; end <= n; end++) {
            // base case declared inside the loops, now just start and end reverses
            // from 1 to n -> n to 1 && n to 1 -> 1 to n.
            if (start == end) {
                continue;
            }

            int minMultiplications = INT_MAX;

            // Iterate through possible positions to split the matrix chain.
            for (int index = start; index < end; index++) {
                int firstBracket = dp[start][index];
                int secondBracket = dp[index + 1][end];

                // Calculate the total cost for the current split and update minMultiplications.
                int multiplications = firstBracket + secondBracket + (arr[start - 1] * arr[index] * arr[end]);
                minMultiplications = min(minMultiplications, multiplications);
            }

            // Store the result in the DP table.
            dp[start][end] = minMultiplications;
        }
    }

    // The final result is stored at dp[1][n], representing the minimum cost of matrix chain multiplication.
    return dp[1][n];
}