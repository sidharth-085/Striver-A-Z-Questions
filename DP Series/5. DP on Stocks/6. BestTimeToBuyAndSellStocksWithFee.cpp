#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to find the maximum profit we can get after buying
// and selling the stocks any number of times with transaction fee. 
// The transaction fee will be counted only if one transaction is completed i.e. 
// when we bought the stock (buy = 1) and we are selling the stock.

// Approach 1: Recursive Solution
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int helper(int index, int buy, int fee, int n, vector<int> &prices) {
    if (index == n) {
        return 0; // If we have reached the end of the prices array, return 0 profit.
    }

    if (buy == 1) {
        // If we are in a "buy" state, we can either buy the current stock or skip it.
        int buyAtCurrPrice = -prices[index] + helper(index + 1, 0, fee, n, prices);   

        int dontBuyAtCurrPrice = helper(index + 1, 1, fee, n, prices);

        return max(buyAtCurrPrice, dontBuyAtCurrPrice); // Return the maximum of these two options.
    }
    else {
        // If we are in a "sell" state, we can either sell the current stock or skip it.
        int sellAtCurrPrice = -fee + prices[index] + helper(index + 1, 1, fee, n, prices);
        // when we are selling, we have to add the transaction fee because one
        // transaction completes here.

        int dontSellAtCurrPrice = helper(index + 1, 0, fee, n, prices);

        return max(sellAtCurrPrice, dontSellAtCurrPrice); // Return the maximum of these two options.
    }

    return 0; // This line is not necessary as it is unreachable.
}

int maxProfit(vector<int> &prices, int fee) {
    int n = prices.size();

    return helper(0, 1, fee, n, prices);
}

// Approach 2: Memoization Solution
// Time Complexity: O(2 * N)
// Space Complexity: O(2 * N)

int helper(int index, int buy, int fee, int n, vector<int> &prices, vector<vector<int>> &dp) {
    if (index == n) {
        return 0;
    }

    if (dp[index][buy] != -1) {
        return dp[index][buy]; // If the result is already computed, return it from the memoization table.
    }
    
    if (buy == 1) {
        // Calculate and store results in the memoization table.
        int buyAtCurrPrice = -prices[index] + helper(index + 1, 0, fee, n, prices, dp);   

        int dontBuyAtCurrPrice = helper(index + 1, 1, fee, n, prices, dp);

        return dp[index][buy] = max(buyAtCurrPrice, dontBuyAtCurrPrice);
    }
    else {
        int sellAtCurrPrice = -fee + prices[index] + helper(index + 1, 1, fee, n, prices, dp);
        // when we are selling, we have to add the transaction fee because one
        // transaction completes here.

        int dontSellAtCurrPrice = helper(index + 1, 0, fee, n, prices, dp);

        return dp[index][buy] = max(sellAtCurrPrice, dontSellAtCurrPrice);
    }

    return 0; // This line is not necessary as it is unreachable.
}

int maxProfit(vector<int> &prices, int fee) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2, -1));

    return helper(0, 1, fee, n, prices, dp);
}

// Approach 3: Tabulation Method
// Time Complexity: O(2 * N)
// Space Complexity: O(2 * N)

int maxProfit(vector<int> &prices, int fee) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2, -1));

    dp[n][1] = dp[n][0] = 0; // Initialize the base case (no stocks owned at the end).

    for (int index = n - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            if (buy == 1) {
                // Calculate and store results in the DP table.
                int buyAtCurrPrice = -prices[index] + dp[index + 1][0];   

                int dontBuyAtCurrPrice = dp[index + 1][1];  

                dp[index][buy] = max(buyAtCurrPrice, dontBuyAtCurrPrice);
            }
            else {
                int sellAtCurrPrice = -fee + prices[index] + dp[index + 1][1];
                // when we are selling, we have to add the transaction fee because
                // one transaction completes here.

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

int maxProfit(vector<int> &prices, int fee) {
    int n = prices.size();

    vector<int> next(2, -1);
    
    vector<int> curr(2, -1);

    next[1] = next[0] = 0; // Initialize the base case.

    for (int index = n - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            if (buy == 1) {
                int buyAtCurrPrice = -prices[index] + next[0];   

                int dontBuyAtCurrPrice = next[1];  

                curr[buy] = max(buyAtCurrPrice, dontBuyAtCurrPrice);
            }
            else {
                int sellAtCurrPrice = -fee + prices[index] + next[1];
                // when we are selling, we have to add the transaction fee because
                // one transaction completes here.

                int dontSellAtCurrPrice = next[0];

                curr[buy] = max(sellAtCurrPrice, dontSellAtCurrPrice);
            }
        }

        next = curr; // Update the "next" vector for the next iteration.
    }

    return next[1]; // The result is the maximum profit with stocks owned at the beginning.
}