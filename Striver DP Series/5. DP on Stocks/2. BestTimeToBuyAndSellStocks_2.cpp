#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to find the maximum profit we can get after buying
// and selling the stocks any number of times 

// Approach 1: Recursive Solution
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int helper(int index, int buy, int n, vector<int> &prices) {
    if (index == n) {
        return 0; // If we have reached the end of the prices array, return 0 profit.
    }

    if (buy == 1) {
        // If we are in a "buy" state, we can either buy the current stock or skip it.
        int buyAtCurrPrice = -prices[index] + helper(index + 1, 0, n, prices);   

        int dontBuyAtCurrPrice = helper(index + 1, 1, n, prices);

        return max(buyAtCurrPrice, dontBuyAtCurrPrice); // Return the maximum of these two options.
    }
    else {
        // If we are in a "sell" state, we can either sell the current stock or skip it.
        int sellAtCurrPrice = prices[index] + helper(index + 1, 1, n, prices);

        int dontSellAtCurrPrice = helper(index + 1, 0, n, prices);

        return max(sellAtCurrPrice, dontSellAtCurrPrice); // Return the maximum of these two options.
    }

    return 0; // This line is not necessary as it is unreachable.
}

int maxProfit(vector<int> &prices) {
    int n = prices.size();

    return helper(0, 1, n, prices);
}

// Approach 2: Memoization Solution
// Time Complexity: O(2 * N)
// Space Complexity: O(2 * N)

int helper(int index, int buy, int n, vector<int> &prices, vector<vector<int>> &dp) {
    if (index == n) {
        return 0;
    }

    if (dp[index][buy] != -1) {
        return dp[index][buy]; // If the result is already computed, return it from the memoization table.
    }
    
    if (buy == 1) {
        // Calculate and store results in the memoization table.
        int buyAtCurrPrice = -prices[index] + helper(index + 1, 0, n, prices, dp);   

        int dontBuyAtCurrPrice = helper(index + 1, 1, n, prices, dp);

        return dp[index][buy] = max(buyAtCurrPrice, dontBuyAtCurrPrice);
    }
    else {
        int sellAtCurrPrice = prices[index] + helper(index + 1, 1, n, prices, dp);

        int dontSellAtCurrPrice = helper(index + 1, 0, n, prices, dp);

        return dp[index][buy] = max(sellAtCurrPrice, dontSellAtCurrPrice);
    }

    return 0; // This line is not necessary as it is unreachable.
}

int maxProfit(vector<int> &prices) {
    int size = prices.size();

    vector<vector<int>> dp(size + 1, vector<int>(2, -1));

    return helper(0, 1, size, prices, dp);
}

// Approach 3: Tabulation Method
// Time Complexity: O(2 * N)
// Space Complexity: O(2 * N)

int maxProfit(vector<int> &prices) {
    int size = prices.size();

    vector<vector<int>> dp(size + 1, vector<int>(2, -1));

    dp[size][1] = dp[size][0] = 0; // Initialize the base case (no stocks owned at the end).

    for (int index = size - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            if (buy == 1) {
                // Calculate and store results in the DP table.
                int buyAtCurrPrice = -prices[index] + dp[index + 1][0];   

                int dontBuyAtCurrPrice = dp[index + 1][1];  

                dp[index][buy] = max(buyAtCurrPrice, dontBuyAtCurrPrice);
            }
            else {
                int sellAtCurrPrice = prices[index] + dp[index + 1][1];

                int dontSellAtCurrPrice = dp[index + 1][0];

                dp[index][buy] = max(sellAtCurrPrice, dontSellAtCurrPrice);
            }
        }
    }

    return dp[0][1]; // The result is the maximum profit with stocks owned at the beginning.
}

// Approach 4: Space Optimization Method
// Time Complexity: O(2 * N)
// Space Complexity: O(1)

int maxProfit(vector<int> &prices) {
    int size = prices.size();

    vector<int> next(2, -1);
    
    vector<int> curr(2, -1);

    next[1] = next[0] = 0; // Initialize the base case.

    for (int index = size - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            if (buy == 1) {
                int buyAtCurrPrice = -prices[index] + next[0];   

                int dontBuyAtCurrPrice = next[1];  

                curr[buy] = max(buyAtCurrPrice, dontBuyAtCurrPrice);
            }
            else {
                int sellAtCurrPrice = prices[index] + next[1];

                int dontSellAtCurrPrice = next[0];

                curr[buy] = max(sellAtCurrPrice, dontSellAtCurrPrice);
            }
        }

        next = curr; // Update the "next" vector for the next iteration.
    }

    return next[1]; // The result is the maximum profit with stocks owned at the beginning.
}