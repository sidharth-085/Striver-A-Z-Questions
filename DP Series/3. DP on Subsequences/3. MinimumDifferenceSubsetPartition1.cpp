#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to divide the given array into two subsets in such
// a way that the difference of both subsets (absolute) is minimum.

// This question have to start from memoization approach because we are going to
// use the memoization table to check that if current sum in first or last row 
// (depends on the approach for dp) is a subset sum from main array or not. If it 
// is the subset sum from main array, then we find the remaining sum (total - sum)
// and take difference of both and minimize it to get the proper answer.

// This approach only works for +ve elements.

// Approach 1: Recursive Memoization Approach
// Time Complexity: O(N * K * K)
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

// Function to find the minimum difference between two subset sums.
int minSubsetSumDifference(vector<int> &arr, int n) {
    // Calculate the total sum of all elements in the array.
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum = totalSum + arr[i];
    }

    // Create a memoization table with initial values of -1.
    vector<vector<int>> dp(n, vector<int>(totalSum + 1, -1));

    // Fill the memoization table by checking possible subsets for each sum.
    for (int sum = 0; sum <= totalSum; sum++) {
        subsetSumToKHelper(n-1, sum, n, arr, dp);
    }

    // Initialize a variable to store the minimum difference.
    int mini = INT_MAX;

    // Find the minimum difference by iterating through the memoization table.
    for (int sum1 = 0; sum1 <= totalSum; sum1++) {
        if (dp[n-1][sum1] == 1) {
            int sum2 = totalSum - sum1;

            // Update the minimum difference if necessary.
            mini = min(mini, abs(sum1 - sum2));
        }
    }

    // Return the minimum difference.
    return mini;
}

// Approach 2: Tabulation Method (Bottom Up Dp)
// Time Complexity: O(N * K * K)
// Space Complexity: O(N * K)

int minSubsetSumDifference(vector<int> &arr, int n) {
    // Calculate the total sum of all elements in the array.
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum = totalSum + arr[i];
    }

    // Create a DP table with initial values of -1.
    vector<vector<int>> dp(n, vector<int>(totalSum + 1, 0));

    for (int index = 0; index < n; index++) {
        dp[index][0] = 1; 
        // Base case: There is always an empty subset with sum 0.
    }

    if (arr[0] <= totalSum) {
        dp[0][arr[0]] = 1;
    }

    for (int index = 1; index < n; index++) {
        for (int sum = 1; sum <= totalSum; sum++) {
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

    // Initialize a variable to store the minimum difference.
    int mini = INT_MAX;

    // Find the minimum difference by iterating through the DP table.
    for (int sum1 = 0; sum1 <= totalSum / 2; sum1++) {
        if (dp[n-1][sum1] == 1) {
            int sum2 = totalSum - sum1;

            // Update the minimum difference if necessary.
            mini = min(mini, abs(sum1 - sum2));
        }
    }

    // Return the minimum difference.
    return mini;
}

// Approach 3: Space Optimization (Bottom Up Dp)
// Time Complexity: O(N * K * K)
// Space Complexity: O(K)

int minSubsetSumDifference(vector<int> &arr, int n) {
    // Calculate the total sum of all elements in the array.
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum = totalSum + arr[i];
    }

    // Create a vector to represent the current row of the DP table.
    vector<int> prevRow(totalSum + 1, 0);

    prevRow[0] = 1;

    if (arr[0] <= totalSum) {
        prevRow[arr[0]] = 1;
    }

    for (int index = 1; index < n; index++) {
        vector<int> currRow(totalSum + 1, 0);
        currRow[0] = 1;

        for (int sum = 1; sum <= totalSum; sum++) {
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

    // Initialize a variable to store the minimum difference.
    int mini = INT_MAX;

    // Find the minimum difference by iterating through the DP table.
    for (int sum1 = 0; sum1 <= totalSum / 2; sum1++) {
        if (prevRow[sum1] == 1) {
            int sum2 = totalSum - sum1;

            // Update the minimum difference if necessary.
            mini = min(mini, abs(sum1 - sum2));
        }
    }

    // Return the minimum difference.
    return mini;
}