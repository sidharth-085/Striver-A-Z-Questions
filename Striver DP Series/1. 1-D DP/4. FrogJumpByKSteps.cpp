#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force Recursion Solution
// Time Complexity: O(K^N)
// Space Complexity: O(K^N)

int minimizeCostHelper(int index, int k, vector<int> &heights) {
    // Base case: If at the starting position, cost is 0.
    if (index == 0) {
        return 0;
    }

    int mini = INT_MAX;

    // Trying all possible step sizes from 1 to k.
    for (int i=1; i<=k; i++) {
        int iStepJump = INT_MAX;
        if (index > i-1) {
            // Calculate cost of jumping 'i' steps and recursively solve for remaining steps.
            iStepJump = abs(heights[index] - heights[index - i]) + minimizeCostHelper(index - i, k, heights);
            mini = min(mini, iStepJump);
        }
    }

    return mini;
}

int minimizeCost(int n, int k, vector<int> &height) {
    return minimizeCostHelper(n-1, k, height);
}

// Approach 2: Memoization Solution (Top - down)
// Time Complexity: O(N * K)
// Space Complexity: O(N)

int minimizeCostHelper(int index, int k, vector<int> &heights, vector<int> &dp) {
    // Base case: If at the starting position, cost is 0.
    if (index == 0) {
        return 0;
    }

    if (dp[index] != -1) {
        return dp[index]; // Return already computed result from memoization table.
    }

    int mini = INT_MAX;

    // Trying all possible step sizes from 1 to k.
    for (int i=1; i<=k; i++) {
        int iStepJump = INT_MAX;
        if (index > i-1) {
            // Calculate cost of jumping 'i' steps and recursively solve for remaining steps.
            iStepJump = abs(heights[index] - heights[index - i]) + minimizeCostHelper(index - i, k, heights, dp);
            mini = min(mini, iStepJump);
        }
    }

    return dp[index] = mini; // Memoize the result and return.
}

int minimizeCost(int n, int k, vector<int> &height) {
    vector<int> dp(n, -1); // Initialize memoization table with -1.

    return minimizeCostHelper(n-1, k, height, dp);
}

// Approach 3: Iterative DP (Bottom Up)
// Time Complexity: O(N * K)
// Space Complexity: O(N)

int minimizeCost(int n, int k, vector<int> &heights) {
    vector<int> dp(n);

    dp[0] = 0; // Base case: Cost at starting position is 0.

    // Iterate through all positions from 1 to n-1.
    for (int index = 1; index < n; index++) {
        int mini = INT_MAX;

        // Trying all possible step sizes from 1 to k.
        for (int i=1; i<=k; i++) {
            int iStepBack = INT_MAX;
            if (index > i-1) {
                // Calculate cost of jumping 'i' steps and add to previously computed cost.
                iStepBack = abs(heights[index] - heights[index - i]) + dp[index - i];
            }

            mini = min(mini, iStepBack);
        }

        dp[index] = mini; // Store the minimum cost for current position.
    }

    return dp[n-1]; // Return the minimum cost to reach the last position.
}