#include <iostream>
#include <vector>
using namespace std;

// IMP NOTE: In problem like Infinite supply of something which can be anything
// coins, weights, etc. We can optimize this solution till single 1-D array.

// This question is similar to Combination Sum problem in which we can take coins
// any number of times.

// Approach 1: Recursive Approach
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int changeHelper(int index, int sum, int n, vector<int> &coins) {
    if (sum == 0) {
        return 1; 
        // Base case: If the sum is zero, we have found a valid combination.
    }

    if (index == 0) {
        if (sum % coins[0] == 0) {
            return 1; 
            // Base case: If we are at the first coin and it divides 'sum', it's a valid combination.
        }
        return 0; 
        // Base case: If the first coin doesn't divide 'sum', it's not a valid combination.
    }

    int take = 0;
    if (coins[index] <= sum) {
        take = changeHelper(index, sum - coins[index], n, coins); 
        // Try taking the current coin.
    }

    int notTake = changeHelper(index - 1, sum, n, coins); 
    // Skip the current coin.

    return take + notTake; 
    // Sum the results of taking and not taking the current coin.
}

int change(int amount, vector<int>& coins) {
    int n = coins.size();

    return changeHelper(n-1, amount, n, coins); 
    // Start from the last coin.
}

// Approach 2: Memoization Method
// Time Complexity: O(N * AMOUNT)
// Space Complexity: O(N * AMOUNT)

// Helper function for memoization approach
int changeHelper(int index, int sum, int n, vector<int> &coins, vector<vector<int>> &dp) {
    if (sum == 0) {
        return 1;
    }

    if (index == 0) {
        if (sum % coins[0] == 0) {
            return 1;
        }
        return 0;
    }

    if (dp[index][sum] != -1) {
        return dp[index][sum]; 
        // If result for this combination is already computed, return it.
    }

    int take = 0;
    if (coins[index] <= sum) {
        take = changeHelper(index, sum - coins[index], n, coins, dp);
    }

    int notTake = changeHelper(index - 1, sum, n, coins, dp);

    return dp[index][sum] = take + notTake; 
    // Store and return the result.
}

int change(int amount, vector<int>& coins) {
    int n = coins.size();

    vector<vector<int>> dp(n, vector<int>(amount+1, -1)); 
    // Initialize a memoization table.

    return changeHelper(n-1, amount, n, coins, dp);
}

// Approach 3: Tabulation Method (Top-down DP)
// Time Complexity: O(N * AMOUNT)
// Space Complexity: O(N * AMOUNT)

int change(int amount, vector<int>& coins) {
    int n = coins.size();

    vector<vector<int>> dp(n, vector<int>(amount+1, -1)); 
    // Initialize a table to store results.

    for (int index = 0; index < n; index++) {
        dp[index][0] = 1; 
        // Base case: If the sum is zero, there is one way (no coins used).
    }

    for (int sum = 1; sum <= amount; sum++) {
        if (sum % coins[0] == 0) {
            dp[0][sum] = 1; 
            // Base case: If the first coin divides 'sum', there is one way.
        }
        else {
            dp[0][sum] = 0; 
            // Base case: Otherwise, there is no way to make 'sum' with the first coin.
        }
    }

    for (int index = 1; index < n; index++) {
        for (int sum = 1; sum <= amount; sum++) {
            int take = 0;
            if (coins[index] <= sum) {
                take = dp[index][sum - coins[index]]; 
                // Try taking the current coin.
            }

            int notTake = dp[index - 1][sum]; // Skip the current coin.

            dp[index][sum] = take + notTake; // Store and update the result.
        }
    }

    return dp[n-1][amount]; // Return the final result.
}

// Approach 4: Space Optimization (Two 1-D Array)
// Time Complexity: O(N * AMOUNT)
// Space Complexity: O(2 * AMOUNT)

int change(int amount, vector<int>& coins) {
    int n = coins.size();

    vector<int> prev(amount+1, -1); // Initialize the previous row.

    prev[0] = 1; 
    // Base case: If the sum is zero, there is one way (no coins used).

    for (int sum = 1; sum <= amount; sum++) {
        if (sum % coins[0] == 0) {
            prev[sum] = 1; 
            // Base case: If the first coin divides 'sum', there is one way.
        }
        else {
            prev[sum] = 0; 
            // Base case: Otherwise, there is no way to make 'sum' with the first coin.
        }
    }

    for (int index = 1; index < n; index++) {
        vector<int> curr(amount+1, -1); // Initialize the current row.

        curr[0] = 1; // Base case: If the sum is zero, there is one way (no coins used).

        for (int sum = 1; sum <= amount; sum++) {
            int take = 0;
            if (coins[index] <= sum) {
                take = curr[sum - coins[index]]; // Try taking the current coin.
            }

            int notTake = prev[sum]; // Skip the current coin.

            curr[sum] = take + notTake; // Store and update the result.
        }

        prev = curr; // Update the previous row for the next iteration.
    }

    return prev[amount]; // Return the final result.
}

// Approach 5: Space Optimization (One 1-D array)
// Time Complexity: O(N * AMOUNT)
// Space Complexity: O(AMOUNT)

int change(int amount, vector<int>& coins) {
    int n = coins.size();

    vector<int> prev(amount+1, -1); // Initialize the previous row.

    prev[0] = 1; 
    // Base case: If the sum is zero, there is one way (no coins used).

    for (int sum = 1; sum <= amount; sum++) {
        if (sum % coins[0] == 0) {
            prev[sum] = 1; 
            // Base case: If the first coin divides 'sum', there is one way.
        }
        else {
            prev[sum] = 0; 
            // Base case: Otherwise, there is no way to make 'sum' with the first coin.
        }
    }

    for (int index = 1; index < n; index++) {
        for (int sum = 1; sum <= amount; sum++) {
            int take = 0;
            if (coins[index] <= sum) {
                take = prev[sum - coins[index]]; 
            }

            int notTake = prev[sum]; // Skip the current coin.

            prev[sum] = take + notTake; // Store and update the result.
        }
    }

    return prev[amount]; // Return the final result.
}