#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Approach
// Time Complexity: O(2^N)
// Space Complexity: O(N)

bool subsetSumToKHelper(int index, int sum, int n, vector<int> &arr) {
    if (sum == 0) {
        return true; // Base case: Subset with sum k found.
    }

    if (index == 0) {
        return arr[0] == sum; 
        // Base case: If reached at first index from ending, check is current
        // element is equal to sum or not.
    }

    bool include = false;
    if (arr[index] <= sum) {
        include = subsetSumToKHelper(index - 1, sum - arr[index], n, arr); // Include the current element.
    }

    bool exclude = subsetSumToKHelper(index - 1, sum, n, arr); // Exclude the current element.

    return include || exclude; // Return true if either including or excluding the current element results in a valid subset.
}

bool subsetSumToK(int n, int k, vector<int> &arr) {
    return subsetSumToKHelper(n - 1, k, n, arr);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)

bool subsetSumToKHelper(int index, int sum, int n, vector<int> &arr, vector<vector<int>> &dp) {
    if (sum == 0) {
        return true;
    }

    if (index == 0) {
        return arr[0] == sum; 
        // Base case: If reached at first index from ending, check is current
        // element is equal to sum or not.
    }

    if (dp[index][sum] != -1) {
        return dp[index][sum]; // Return the precomputed result if available.
    }

    bool include = false;
    if (arr[index] <= sum) {
        include = subsetSumToKHelper(index - 1, sum - arr[index], n, arr, dp);
    }

    bool exclude = subsetSumToKHelper(index - 1, sum, n, arr, dp);

    return dp[index][sum] = include || exclude; // Store and return the result.
}

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));

    return subsetSumToKHelper(n - 1, k, n, arr, dp);
}

// Approach 3: Tabulation Approach (Bottom Up DP)
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    for (int index = 0; index < n; index++) {
        dp[index][0] = 1; 
        // Base case: There is always an empty subset with sum 0.
    }

    if (arr[0] <= k) {
        dp[0][arr[0]] = 1;
    }

    for (int index = 1; index < n; index++) {
        for (int sum = 1; sum <= k; sum++) {
            bool include = false;

            if (arr[index] <= sum) {
                include = dp[index - 1][sum - arr[index]]; 
                // Include the current element.
            }

            bool exclude = dp[index - 1][sum]; 
            // Exclude the current element.

            dp[index][sum] = include || exclude; 
            // Store the result for the current state.
        }
    }

    return dp[n-1][k]; // Return the final result.
}

// Approach 4: Space Optimization (Bottom Up DP)
// Time Complexity: O(N * K)
// Space Complexity: O(K)

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<int> prevRow(k + 1, 0);

    prevRow[0] = 1;

    if (arr[0] <= k) {
        prevRow[arr[0]] = 1;
    }

    for (int index = 1; index < n; index++) {
        vector<int> currRow(k + 1, 0);
        currRow[0] = 1;

        for (int sum = 1; sum <= k; sum++) {
            bool include = false;

            if (arr[index] <= sum) {
                include = prevRow[sum - arr[index]]; 
                // Include the current element.
            }

            bool exclude = prevRow[sum]; 
            // Exclude the current element.

            currRow[sum] = include || exclude; 
            // Store the result for the current state.
        }

        prevRow = currRow;
    }

    return prevRow[k]; // Return the final result.
}