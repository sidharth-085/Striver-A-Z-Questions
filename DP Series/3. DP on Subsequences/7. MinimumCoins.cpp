#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Brute Force Solution
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int minimumElementsHelper(int index, int target, vector<int> &nums) {
    // Base case: If the target amount is 0, no coins needed.
    if (target == 0) {
        return 0;
    }

    // Base case: If we are at the first coin denomination (index 0),
    // check if the target amount is divisible by this coin.
    if (index == 0) {
        if (target % nums[index] == 0) {
            return (target / nums[index]);
        }

        // If not divisible, return a large value to indicate no solution.
        return 1e9;
    }

    // Initialize takeCoin to a large value.
    int takeCoin = 1e9;

    // If the current coin denomination can be used for the target amount,
    // recursively calculate the minimum number of coins needed.
    if (nums[index] <= target) {
        takeCoin = 1 + minimumElementsHelper(index, target - nums[index], nums);
    }

    // Calculate the minimum number of coins without using the current coin.
    int notTakeCoin = minimumElementsHelper(index - 1, target, nums);

    // Return the minimum of takeCoin and notTakeCoin.
    return min(takeCoin, notTakeCoin);
}

int minimumElements(vector<int> &nums, int amount) {
    int n = nums.size();

    // Calculate the result using the recursive helper function.
    int result = minimumElementsHelper(n - 1, amount, nums);

    // If there is no valid solution, return -1.
    if (result == 1e9) {
        return -1;
    }

    return result;
}

// Approach 2: Memoization Solution
// Time Complexity: O(N * A)
// Space Complexity: O(N * A)

// A is the amount given in question

int minimumElementsHelper(int index, int target, vector<int> &nums, vector<vector<int>> &dp) {
    if (target == 0) {
        return 0;
    }

    if (index == 0) {
        if (target % nums[0] == 0) {
            return (target / nums[0]);
        }

        return 1e9;
    }

    // Check if the result for this combination of index and target
    // has been previously calculated and stored in the dp table.
    if (dp[index][target] != -1) {
        return dp[index][target];
    }

    int takeCoin = 1e9;

    if (nums[index] <= target) {
        takeCoin = 1 + minimumElementsHelper(index, target - nums[index], nums, dp);
    }

    int notTakeCoin = minimumElementsHelper(index - 1, target, nums, dp);

    // Store the result in the dp table and return it.
    return dp[index][target] = min(takeCoin, notTakeCoin);
}

int coinChange(vector<int> &nums, int amount) {
    int n = nums.size();

    // Initialize a memoization table with -1 values.
    vector<vector<int>> dp(n, vector<int>(amount + 1, -1));

    // Calculate the result using the memoization helper function.
    int result = minimumElementsHelper(n - 1, amount, nums, dp);

    if (result == 1e9) {
        return -1;
    }

    return result;
}

// Approach 3: Tabulation Method
// Time Complexity: O(N * A)
// Space Complexity: O(N * A)

// A is the amount given in question

int coinChange(vector<int> &nums, int amount) {
    int n = nums.size();

    // Initialize a 2D table to store subproblem results.
    vector<vector<int>> dp(n, vector<int>(amount + 1, -1));

    // Initialize base case: for target amount 0, no coins needed.
    for (int index = 0; index < n; index++) {
        dp[index][0] = 0;
    }

    // Fill in the table for each combination of index and target amount.
    for (int target = 1; target <= amount; target++) {
        if (target % nums[0] == 0) {
            dp[0][target] = target / nums[0];
        } else {
            dp[0][target] = 1e9;
        }
    }

    for (int index = 1; index < n; index++) {
        for (int target = 1; target <= amount; target++) {
            int takeCoin = 1e9;

            if (nums[index] <= target) {
                takeCoin = 1 + dp[index][target - nums[index]];
            }

            int notTakeCoin = dp[index - 1][target];

            // Store the minimum of takeCoin and notTakeCoin in the table.
            dp[index][target] = min(takeCoin, notTakeCoin);
        }
    }

    // If there is no valid solution, return -1.
    if (dp[n - 1][amount] == 1e9) {
        return -1;
    }

    return dp[n - 1][amount];
}

// Approach 4: Space Optimization Method
// Time Complexity: O(N * A)
// Space Complexity: O(A)

// A is the amount given in question

int coinChange(vector<int> &nums, int amount) {
    int n = nums.size();

    // Use two rows to optimize space usage.
    vector<int> prevRow(amount + 1, -1);
    prevRow[0] = 0;

    // Initialize base case for the first row.
    for (int target = 1; target <= amount; target++) {
        if (target % nums[0] == 0) {
            prevRow[target] = target / nums[0];
        } else {
            prevRow[target] = 1e9;
        }
    }

    for (int index = 1; index < n; index++) {
        // Create a new row for the current coin denomination.
        vector<int> currRow(amount + 1, -1);
        currRow[0] = 0;

        for (int target = 1; target <= amount; target++) {
            int takeCoin = 1e9;

            if (nums[index] <= target) {
                takeCoin = 1 + currRow[target - nums[index]];
            }

            int notTakeCoin = prevRow[target];

            // Store the minimum of takeCoin and notTakeCoin in the current row.
            currRow[target] = min(takeCoin, notTakeCoin);
        }

        // Update the previous row with the current row for the next iteration.
        prevRow = currRow;
    }

    // If there is no valid solution, return -1.
    if (prevRow[amount] == 1e9) {
        return -1;
    }

    return prevRow[amount];
}