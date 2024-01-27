#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to partition the array in such a way that 
// sum of all elements which will be replaced by maximum element of every
// subarray taken will be maximum. So, we try to do partition at every index
// till kth partition and try to maximize the answer.

// Approach 1: Recursive Approach
// Time Complexity: Exponential
// Space Complexity: O(N)

int helper(int start, int k, int n, vector<int> &arr) {    
    // Base case: If we have reached the end of the array, return 0.
    if (start == n) {
        return 0;
    }

    // Initialize variables to keep track of the maximum sum, length of the subarray, and the maximum element in the subarray.
    int maxSum = INT_MIN;
    int len = 0;
    int maxOfSubarray = INT_MIN;

    // Determine the end index of the current subarray based on 'k.'
    int end = min(start + k, n);

    // Iterate through the subarray and find the maximum element and update the variables.
    for (int index = start; index < end; index++) {
        maxOfSubarray = max(maxOfSubarray, arr[index]);
        len++;

        // Calculate the current sum for this subarray and recursively call the helper function for the next subarray.
        int currSum = (len * maxOfSubarray) + helper(index + 1, k, n, arr);

        // Update the maximum sum.
        maxSum = max(maxSum, currSum);
    }

    return maxSum;
}

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();

    return helper(0, k, n, arr);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * N)
// Space Complexity: O(N)

int helper(int start, int k, int n, vector<int> &arr, vector<int> &dp) {    
    // Base case: If we have reached the end of the array, return 0.
    if (start == n) {
        return 0;
    }

    // If the result for this start index is already calculated, return it.
    if (dp[start] != -1) {
        return dp[start];
    }

    int maxSum = INT_MIN;
    int len = 0;
    int maxOfSubarray = INT_MIN;

    int end = min(start + k, n);

    for (int index = start; index < end; index++) {
        maxOfSubarray = max(maxOfSubarray, arr[index]);
        len++;

        int currSum = (len * maxOfSubarray) + helper(index + 1, k, n, arr, dp);

        maxSum = max(maxSum, currSum);
    }

    // Store the result in the memoization array and return it.
    return dp[start] = maxSum;
}

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();

    vector<int> dp(n + 1, -1);

    return helper(0, k, n, arr, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * N)
// Space Complexity: O(N)

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();

    // Initialize a dynamic programming array to store the results.
    vector<int> dp(n + 1, 0);

    // Initialize the value for the end of the array.
    dp[n] = 0;

    // Iterate through the array in reverse order.
    for (int start = n - 1; start >= 0; start--) {
        int maxSum = INT_MIN;
        int len = 0;
        int maxOfSubarray = INT_MIN;

        // Determine the end index of the current subarray based on 'k.'
        int end = min(start + k, n);

        // Iterate through the subarray and find the maximum element and update the variables.
        for (int index = start; index < end; index++) {
            maxOfSubarray = max(maxOfSubarray, arr[index]);
            len++;

            // Calculate the current sum for this subarray using previously calculated results.
            int currSum = (len * maxOfSubarray) + dp[index + 1];

            // Update the maximum sum.
            maxSum = max(maxSum, currSum);
        }

        // Store the result in the dynamic programming array.
        dp[start] = maxSum;
    }

    // The final result will be stored at the start index (0).
    return dp[0];
}