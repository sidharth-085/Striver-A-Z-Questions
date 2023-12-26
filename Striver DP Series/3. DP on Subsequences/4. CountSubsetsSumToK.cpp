#include <iostream>
#include <vector>
using namespace std;

// In this question, we are given constraints 1 <= arr[i] <= 10^9 and we solve 
// this using this given solution, but in next question we are given constraints
// starting from 0. It means there can be 0 present as element in arr and we have
// to count as subset. So, we modify the code little bit.

// Approach 1: Recursive Approach
// Time Complexity: O(2 ^ N)
// Space Complexity: O(N)

int countSubsets(int index, int sum, vector<int> &arr, int n) {
    // If the required sum is achieved, return 1 to count this subset.
    if (sum == 0) {
        return 1;
    }

    // If we have exhausted the array but haven't found the sum, return 0.
    if (index == 0) {
        return arr[0] == sum;
    }

    // Try including the current element in the subset sum.
    int include = 0;
    if (arr[index] <= sum) {
        include = countSubsets(index - 1, sum - arr[index], arr, n);
    }

    // Try excluding the current element from the subset sum.
    int exclude = countSubsets(index - 1, sum, arr, n);

    // Return the total count of subsets that achieve the sum.
    return include + exclude;
}

int findWays(vector<int>& arr, int k) {
    int n = arr.size();

    // Call the recursive function to count subsets.
    return countSubsets(n - 1, k, arr, n);
}

// Approach 2: Memoization Approach (Top - down dp) 
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)

int countSubsets(int index, int sum, vector<int> &arr, int n, vector<vector<int>> &dp) {
    // If the required sum is achieved, return 1 to count this subset.
    if (sum == 0) {
        return 1;
    }

    // If we have exhausted the array but haven't found the sum, return 0.
    if (index == 0) {
        return arr[0] == sum;
    }

    // If the result for the current index and sum has already been computed,
    // return it from the memoization table.
    if (dp[index][sum] != -1) {
        return dp[index][sum];
    }

    // Try including the current element in the subset sum.
    int include = 0;
    if (arr[index] <= sum) {
        include = countSubsets(index - 1, sum - arr[index], arr, n, dp);
    }

    // Try excluding the current element from the subset sum.
    int exclude = countSubsets(index - 1, sum, arr, n, dp);

    // Store the result in the memoization table and return it.
    return dp[index][sum] = include + exclude;
}

int findWays(vector<int>& arr, int k) {
    int n = arr.size();

    // Create a memoization table with initial values of -1.
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));

    // Call the recursive function with memoization to count subsets.
    return countSubsets(n - 1, k, arr, n, dp);
}

// Approach 3: Tabulation Method (Bottom Up DP)
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)

int findWays(vector<int>& arr, int k) {
    int n = arr.size();

    // Create a DP table with initial values of -1.
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    // Initialize the base cases: If the sum is 0, there is one possible subset (empty).
    for (int index = 0; index < n; index++) {
        dp[index][0] = 1;
    }

    // Initialize the base cases: If there are no elements, there is no possible subset.
    if (arr[0] <= k) {
        dp[0][arr[0]] = 1;
    }

    // Fill the DP table using a bottom-up approach.
    for (int index = 1; index < n; index++) {
        for (int sum = 1; sum <= k; sum++) {
            // Try including the current element in the subset sum.
            int include = 0;
            if (arr[index] <= sum) {
                include = dp[index - 1][sum - arr[index]];
            }

            // Try excluding the current element from the subset sum.
            int exclude = dp[index - 1][sum];

            // Update the DP table with the result.
            dp[index][sum] = include + exclude;
        }
    }

    // Return the number of ways to form subsets that sum to 'k'.
    return dp[n-1][k];
}

// Approach 4: Space Optimization Method (Bottom Up DP)
// Time Complexity: O(N * K)
// Space Complexity: O(K)

int findWays(vector<int>& arr, int k) {
    int n = arr.size();

    // Create a vector to represent the current row of the DP table.
    vector<int> prevRow(k + 1, 0);

    // Initialize the base case: If the sum is 0, there is one possible subset (empty).
    prevRow[0] = 1;

    // Initialize the base cases: If there are no elements, there is no possible subset.
    if (arr[0] <= k) {
        prevRow[arr[0]] = 1;
    }

    // Fill the DP table using a bottom-up approach.
    for (int index = 1; index < n; index++) {
        vector<int> currRow(k + 1, 0);
        currRow[0] = 1;

        for (int sum = 1; sum <= k; sum++) {
            // Try including the current element in the subset sum.
            int include = 0;
            if (arr[index] <= sum) {
                include = prevRow[sum - arr[index]];
            }

            // Try excluding the current element from the subset sum.
            int exclude = prevRow[sum];

            // Update the current row with the result.
            currRow[sum] = include + exclude;
        }

        // Update the nextRow for the next iteration.
        prevRow = currRow;
    }

    // Return the number of ways to form subsets that sum to 'k'.
    return prevRow[k];
}