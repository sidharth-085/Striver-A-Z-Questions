#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Recursive Approach
// Time Complexity: Exponential
// Space Complexity: O(N)

int helper(int start, int end, vector<int> &balloons) {
    // Base case: If the start index is greater than the end index, there are no balloons in this range, return 0.
    if (start > end) {
        return 0;
    }

    // Initialize a variable to keep track of the maximum coins in this range.
    int maxCoins = 0;

    // Iterate through balloons in the current range.
    for (int index = start; index <= end; index++) {
        // Calculate the number of coins obtained by bursting the balloon at 'index'.
        int numCoins = balloons[start - 1] * balloons[index] * balloons[end + 1];

        // Recursively calculate the maximum coins for the left and right parts of the range.
        int leftPart = helper(start, index - 1, balloons);
        int rightPart = helper(index + 1, end, balloons);

        // Calculate the total coins for the current arrangement and update maxCoins if necessary.
        int totalCoins = leftPart + numCoins + rightPart;
        maxCoins = max(maxCoins, totalCoins);
    }

    // Return the maximum coins for the current range.
    return maxCoins;
}

int maxCoins(vector<int>& nums) {
    int n = nums.size();

    // Create a modified balloons vector with added 1's at the beginning and end.
    vector<int> balloons;
    balloons.push_back(1);
    for (int i = 0; i < n; i++) {
        balloons.push_back(nums[i]);
    }
    balloons.push_back(1);

    // Start the recursion with the initial range (1, n).
    return helper(1, n, balloons);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * N * N)
// Space Complexity: O(N * N)

int helper(int start, int end, vector<int> &balloons, vector<vector<int>> &dp) {
    // Base case: If the start index is greater than the end index, return 0.
    if (start > end) {
        return 0;
    }

    // If the result for this range is already calculated, return it from dp array.
    if (dp[start][end] != -1) {
        return dp[start][end];
    }

    // Initialize a variable to keep track of the maximum coins in this range.
    int maxCoins = 0;

    // Iterate through balloons in the current range.
    for (int index = start; index <= end; index++) {
        // Calculate the number of coins obtained by bursting the balloon at 'index'.
        int numCoins = balloons[start - 1] * balloons[index] * balloons[end + 1];

        // Recursively calculate the maximum coins for the left and right parts of the range.
        int leftPart = helper(start, index - 1, balloons, dp);
        int rightPart = helper(index + 1, end, balloons, dp);

        // Calculate the total coins for the current arrangement and update maxCoins if necessary.
        int totalCoins = leftPart + numCoins + rightPart;
        maxCoins = max(maxCoins, totalCoins);
    }

    // Store the result in the dp array and return it.
    return dp[start][end] = maxCoins;
}

int maxCoins(vector<int>& nums) {
    int n = nums.size();

    // Create a modified balloons vector with added 1's at the beginning and end.
    vector<int> balloons;
    balloons.push_back(1);
    for (int i = 0; i < n; i++) {
        balloons.push_back(nums[i]);
    }
    balloons.push_back(1);

    // Create a memoization table with -1 values.
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));

    // Start the recursion with the initial range (1, n).
    return helper(1, n, balloons, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * N * N)
// Space Complexity: O(N * N)

int maxCoins(vector<int>& nums) {
    int n = nums.size();

    // Create a modified balloons vector with added 1's at the beginning and end.
    vector<int> balloons;
    balloons.push_back(1);
    for (int i = 0; i < n; i++) {
        balloons.push_back(nums[i]);
    }
    balloons.push_back(1);

    // Create a 2D dp array to store maximum coins for different subranges.
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    // Iterate through subranges and calculate the maximum coins using dynamic programming.
    for (int start = n; start >= 1; start--) {
        for (int end = 1; end <= n; end++) {
            int maxCoins = 0;

            // Iterate through balloons in the current range.
            for (int index = start; index <= end; index++) {
                // Calculate the number of coins obtained by bursting the balloon at 'index'.
                int numCoins = balloons[start - 1] * balloons[index] * balloons[end + 1];

                // Get the maximum coins for left and right parts from the dp array.
                int leftPart = dp[start][index - 1];
                int rightPart = dp[index + 1][end];

                // Calculate the total coins for the current arrangement and update maxCoins if necessary.
                int totalCoins = leftPart + numCoins + rightPart;
                maxCoins = max(maxCoins, totalCoins);
            }

            // Store the result in the dp array.
            dp[start][end] = maxCoins;
        }
    }

    // Return the maximum coins for the entire range (1, n).
    return dp[1][n];
}