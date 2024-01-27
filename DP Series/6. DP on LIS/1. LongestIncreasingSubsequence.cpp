#include <iostream>
#include <vector>
using namespace std;

// METHOD 1: Using prevIndex as parameter

// Approach 1: Recursive Approach
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int helper(int index, int prevIndex, int n, vector<int> &nums) {
    // Base case: If we have processed all elements, return 0.
    if (index == n) {
        return 0;
    }

    int take = 0;
    // If the current element is greater than the previous element, we can take it.
    if (prevIndex == -1 || nums[prevIndex] < nums[index]) {
        take = 1 + helper(index + 1, index, n, nums);
    }

    // If we choose not to take the current element.
    int notTake = helper(index + 1, prevIndex, n, nums);

    // Return the maximum of taking and not taking the current element.
    return max(take, notTake);
}

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    return helper(0, -1, n, nums);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

int helper(int index, int prevIndex, int n, vector<int> &nums, vector<vector<int>> &dp) {
    // Base case: If we have processed all elements, return 0.
    if (index == n) {
        return 0;
    }

    // Check if the result for this subproblem is already computed.
    if (dp[index][prevIndex] != -1) {
        return dp[index][prevIndex];
    }

    int take = 0;
    // If the current element is greater than the previous element, we can take it.
    if (prevIndex == 0 || nums[prevIndex - 1] < nums[index]) {
        take = 1 + helper(index + 1, index + 1, n, nums, dp);
    }

    // If we choose not to take the current element.
    int notTake = helper(index + 1, prevIndex, n, nums, dp);

    // Store the result in the memoization table and return it.
    return dp[index][prevIndex] = max(take, notTake);
}

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    // Initialize a memoization table with -1 values.
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

    return helper(0, 0, n, nums, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    // Initialize a 2D DP array with dimensions (n+1) x (n+1).
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Initialize the values in the last row to 0.
    for (int prevIndex = 0; prevIndex <= n; prevIndex++) {
        dp[n][prevIndex] = 0;
    }

    // Fill the DP table starting from the second last row.
    for (int index = n - 1; index >= 0; index--) {
        for (int prevIndex = index; prevIndex >= 0; prevIndex--) {
            int take = 0;
            // If the current element is greater than the previous element, we can take it.
            if (prevIndex == 0 || nums[prevIndex - 1] < nums[index]) {
                take = 1 + dp[index + 1][index + 1];
            }

            // If we choose not to take the current element.
            int notTake = dp[index + 1][prevIndex];

            // Store the result in the DP table.
            dp[index][prevIndex] = max(take, notTake);
        }
    }

    // The answer is in dp[0][0], which represents the length of LIS starting at index 0.
    return dp[0][0];
}

// Approach 4: Space Optimization Approach (Two 1-D arrays)
// Time Complexity: O(N * N)
// Space Complexity: O(2 * N)

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    // Initialize two 1-D arrays to store the DP values for the current and next rows.
    vector<int> next(n + 1, 0);
    vector<int> curr(n + 1, 0);

    // Initialize the values in the last row to 0.
    for (int prevIndex = 0; prevIndex <= n; prevIndex++) {
        next[prevIndex] = 0;
    }

    // Fill the DP table starting from the second last row.
    for (int index = n - 1; index >= 0; index--) {
        for (int prevIndex = index; prevIndex >= 0; prevIndex--) {
            int take = 0;
            // If the current element is greater than the previous element, we can take it.
            if (prevIndex == 0 || nums[prevIndex - 1] < nums[index]) {
                take = 1 + next[index + 1];
            }

            // If we choose not to take the current element.
            int notTake = next[prevIndex];

            // Store the result in the current array.
            curr[prevIndex] = max(take, notTake);
        }

        // Update the next array with the values from the current array for the next iteration.
        next = curr;
    }

    // The answer is in next[0], which represents the length of LIS starting at index 0.
    return next[0];
}

// Approach 5: Space Optimization Approach (One 1-D array)
// Time Complexity: O(N * N)
// Space Complexity: O(N)

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    // Initialize a single 1-D array to store the DP values.
    vector<int> next(n + 1, 0);

    // Initialize the values in the last row to 0.
    for (int prevIndex = 0; prevIndex <= n; prevIndex++) {
        next[prevIndex] = 0;
    }

    // Fill the DP table starting from the second last row.
    for (int index = n - 1; index >= 0; index--) {
        for (int prevIndex = index; prevIndex >= 0; prevIndex--) {
            int take = 0;
            // If the current element is greater than the previous element, we can take it.
            if (prevIndex == 0 || nums[prevIndex - 1] < nums[index]) {
                take = 1 + next[index + 1];
            }

            // If we choose not to take the current element.
            int notTake = next[prevIndex];

            // Update the next array with the result of taking or not taking the current element.
            next[prevIndex] = max(take, notTake);
        }
    }

    // The answer is in next[0], which represents the length of LIS starting at index 0.
    return next[0];
}

// METHOD 2: Assuming the DP array as the dp[i] tells, the LIS till ith index.

// At starting, at every index, there is atleast LIS of length 1, so start from
// one before the current index and if the previous is less than current one, add
// one to the LIS at that previous Index, and if it is greater than current index's
// LIS, update it and find the maximum one from it for every forward index 
// iteration.

// Time Complexity: O(N * N)
// Space Complexity: O(N)

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size(); // Get the size of the input 'nums' array.

    vector<int> dp(n, 1); // Create a dynamic programming array 'dp' of size 'n' and initialize all values to 1.

    int maxi = 1; // Initialize a variable 'maxi' to 1 to store the maximum length of the increasing subsequence.

    for (int index = 1; index < n; index++) {
        // Iterate through the elements of 'nums' starting from the second element.
        
        for (int prevIndex = index - 1; prevIndex >= 0; prevIndex--) {
            // Iterate through the elements before the current 'index' to find smaller elements.

            if (nums[prevIndex] < nums[index]) {
                // If the element at 'prevIndex' is smaller than the element at 'index', it can be part of an increasing subsequence.

                int possibleAns = 1 + dp[prevIndex]; // Calculate the length of a potential increasing subsequence.

                dp[index] = max(dp[index], possibleAns); // Update the 'dp' array with the maximum length found so far for 'index'.
            }
        }

        maxi = max(maxi, dp[index]); // Update 'maxi' with the maximum length found among all elements so far.
    }

    return maxi; // Return the maximum length of the increasing subsequence.
}