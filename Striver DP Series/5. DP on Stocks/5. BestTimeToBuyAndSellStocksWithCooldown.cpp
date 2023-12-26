#include <iostream>
#include <vector>
using namespace std;

// In this question, we can do infinite number of transactions but we have to take
// 1 day for cool down after selling the stock i.e. after every completion of
// transaction. So we are keeping a variable cooldown which becomes 1 when we have
// cooldown day so that we cant buy on that day and 0 if cooldown day ends and we 
// can buy the stock.

// Method 1: For cooldown, we have to skip next day after selling to buy another
// stock. So when we sell the stock, jump to day after next. But, we will not
// space optimize it.

// Approach 1: Recursive Solution
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int helper(int index, int buy, int n, vector<int> &prices) {
    if (index >= n) {
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
        int sellAtCurrPrice = prices[index] + helper(index + 2, 1, n, prices);

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
    if (index >= n) {
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
        int sellAtCurrPrice = prices[index] + helper(index + 2, 1, n, prices, dp);

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
    int n = prices.size();

    vector<vector<int>> dp(n + 2, vector<int>(2, 0));

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
                int sellAtCurrPrice = prices[index] + dp[index + 2][1];

                int dontSellAtCurrPrice = dp[index + 1][0];

                dp[index][buy] = max(sellAtCurrPrice, dontSellAtCurrPrice);
            }
        }
    }

    return dp[0][1]; // The result is the maximum profit with stocks owned at the beginning.
}

// Method 2: Using a Cooldown Variable

// Approach 1: Recursive Approach
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int helper(int index, int buy, int cooldown, int n, vector<int> &prices) {
    if (index == n) {
        return 0; // Base case: No more days left, so no profit can be made.
    }

    if (buy == 1) {
        if (cooldown == 1) {
            return helper(index + 1, 1, 0, n, prices); 
            // Cooldown, can't buy today, so cooldown also not be there.
        }
        else {
            // Two choices: Buy the stock or skip it.
            int buyTheStock = -prices[index] + helper(index + 1, 0, 1, n, prices); 
            // Buy the stock today, when we buy the stock it will be cooldown period starts

            int skipTheStock = helper(index + 1, 1, 0, n, prices); 
            // Skip the stock today, so cooldown will not be there

            return max(buyTheStock, skipTheStock); 
            // Choose the maximum of the two choices.
        }
    }
    else {
        // Two choices: Sell the stock or skip it.
        int sellTheStock = prices[index] + helper(index + 1, 1, 1, n, prices); 
        // Sell the stock today, then transaction is completed hence, we cant buy
        // the stock next day. So, there will be cooldown.

        int skipTheStock = helper(index + 1, 0, 0, n, prices); 
        // Skip the stock today, so there will not be cooldown

        return max(sellTheStock, skipTheStock); 
        // Choose the maximum of the two choices.
    }
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    return helper(0, 1, 0, n, prices); // Start the recursion with initial parameters.
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * 2 * 2)
// Space Complexity: O(N * 2 * 2)

int helper(int index, int buy, int cooldown, int n, vector<int> &prices, vector<vector<vector<int>>> &dp) {
    if (index == n) {
        return 0; // Base case: No more days left, so no profit can be made.
    }

    if (dp[index][buy][cooldown] != -1) {
        return dp[index][buy][cooldown]; // If the result is already cached, return it.
    }

    if (buy == 1) {
        if (cooldown == 1) {
            return dp[index][buy][cooldown] = helper(index + 1, 1, 0, n, prices, dp); // Cooldown, can't buy today.
        }
        else {
            // Two choices: Buy the stock or skip it.
            int buyTheStock = -prices[index] + helper(index + 1, 0, 1, n, prices, dp); // Buy the stock today.
            int skipTheStock = helper(index + 1, 1, 0, n, prices, dp); // Skip the stock today.

            return dp[index][buy][cooldown] = max(buyTheStock, skipTheStock); // Cache and return the maximum of the two choices.
        }
    }
    else {
        // Two choices: Sell the stock or skip it.
        int sellTheStock = prices[index] + helper(index + 1, 1, 1, n, prices, dp); // Sell the stock today.
        int skipTheStock = helper(index + 1, 0, 0, n, prices, dp); // Skip the stock today.

        return dp[index][buy][cooldown] = max(sellTheStock, skipTheStock); // Cache and return the maximum of the two choices.
    }
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(2, -1)));

    return helper(0, 1, 0, n, prices, dp); // Start the recursion with initial parameters.
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * 2 * 2)
// Space Complexity: O(N * 2 * 2)

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(2, -1)));

    // Initialize the base cases.
    for (int buy = 0; buy <= 1; buy++) {
        for (int cooldown = 0; cooldown <= 1; cooldown++) {
            dp[n][buy][cooldown] = 0; // Base case: No more days left, so no profit can be made.
        }
    }

    // Dynamic programming loop to fill the table.
    for (int index = n-1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cooldown = 1; cooldown >= 0; cooldown--) {
                if (buy == 1) {
                    if (cooldown == 1) {
                        dp[index][1][1] = dp[index + 1][1][0]; // Cooldown, can't buy today.
                    }
                    else {
                        // Two choices: Buy the stock or skip it.
                        int buyTheStock = -prices[index] + dp[index + 1][0][1]; // Buy the stock today.
                        int skipTheStock = dp[index + 1][1][0]; // Skip the stock today.

                        dp[index][buy][cooldown] = max(buyTheStock, skipTheStock); // Store the maximum of the two choices.
                    }
                }
                else {
                    // Two choices: Sell the stock or skip it.
                    int sellTheStock = prices[index] + dp[index + 1][1][1]; // Sell the stock today.
                    int skipTheStock = dp[index + 1][0][0]; // Skip the stock today.

                    dp[index][buy][cooldown] = max(sellTheStock, skipTheStock); // Store the maximum of the two choices.
                }
            }
        }
    }

    return dp[0][1][0]; // The final result is in the top-left corner of the table.
}

// Approach 4: Space Optimization Approach
// Time Complexity: O(N * 2 * 2)
// Space Complexity: O(2 * 2)

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> next(2, vector<int>(2, 0)); // Store the next step's results.
    vector<vector<int>> curr(2, vector<int>(2, 0)); // Store the current step's results.

    // Initialize the base cases.
    for (int buy = 0; buy <= 1; buy++) {
        for (int cooldown = 0; cooldown <= 1; cooldown++) {
            next[buy][cooldown] = 0; // Base case: No more days left, so no profit can be made.
        }
    }

    // Dynamic programming loop to fill the table.
    for (int index = n-1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cooldown = 1; cooldown >= 0; cooldown--) {
                if (buy == 1) {
                    if (cooldown == 1) {
                        curr[1][1] = next[1][0]; // Cooldown, can't buy today.
                    }
                    else {
                        // Two choices: Buy the stock or skip it.
                        int buyTheStock = -prices[index] + next[0][1]; // Buy the stock today.
                        int skipTheStock = next[1][0]; // Skip the stock today.

                        curr[buy][cooldown] = max(buyTheStock, skipTheStock); // Store the maximum of the two choices.
                    }
                }
                else {
                    // Two choices: Sell the stock or skip it.
                    int sellTheStock = prices[index] + next[1][1]; // Sell the stock today.
                    int skipTheStock = next[0][0]; // Skip the stock today.

                    curr[buy][cooldown] = max(sellTheStock, skipTheStock); // Store the maximum of the two choices.
                }
            }
        }

        next = curr; // Update 'next' with 'curr' for the next iteration.
    }

    return next[1][0]; // The final result is in the top-left corner of the table.
}