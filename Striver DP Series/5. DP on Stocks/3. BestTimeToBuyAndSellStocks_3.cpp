#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to find the maximum profit we can get after buying
// and selling the stocks at max 2 times. This is an extension of previous problem
// so we have to add the transaction limit parameter in the code. 

// METHOD 1: Using (N*2*3) DP

// Approach 1: Recursive Solution
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int helper(int index, int buy, int numTransactions, int n, vector<int> &prices) {
    if (numTransactions == 2) {
        return 0;
    }

    if (index == n) {
        return 0;
    }

    if (buy == 1) {
        int buyTheStock = -prices[index] + helper(index + 1, 0, numTransactions, n, prices);
        int skipTheStock = helper(index + 1, 1, numTransactions, n, prices);

        return max(buyTheStock, skipTheStock);
    }
    else {
        int sellTheStock = prices[index] + helper(index + 1, 1, numTransactions + 1, n, prices);
        int skipTheStock = helper(index + 1, 0, numTransactions, n, prices);

        return max(sellTheStock, skipTheStock);
    }

    return 0;
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    return helper(0, 1, 0, n, prices);
}

// Approach 2: Memoization Solution
// Time Complexity: O(2 * 3 * N)
// Space Complexity: O(2 * 3 * N)

int helper(int index, int buy, int numTransactions, int n, vector<int> &prices, vector<vector<vector<int>>> &dp) {
    if (numTransactions == 2) {
        return 0;
    }

    if (index == n) {
        return 0;
    }

    if (dp[index][buy][numTransactions] != -1) {
        return dp[index][buy][numTransactions];
    }

    if (buy == 1) {
        int buyTheStock = -prices[index] + helper(index + 1, 0, numTransactions, n, prices, dp);
        int skipTheStock = helper(index + 1, 1, numTransactions, n, prices, dp);

        return dp[index][buy][numTransactions] = max(buyTheStock, skipTheStock);
    }
    else {
        int sellTheStock = prices[index] + helper(index + 1, 1, numTransactions + 1, n, prices, dp);
        int skipTheStock = helper(index + 1, 0, numTransactions, n, prices, dp);

        return dp[index][buy][numTransactions] = max(sellTheStock, skipTheStock);
    }

    return 0;
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));

    return helper(0, 1, 0, n, prices, dp);
}

// Approach 3: Tabulation Method
// Time Complexity: O(2 * 3 * N)
// Space Complexity: O(2 * 3 * N)

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));

    for (int index = 0; index <= n; index++) {
        for (int buy = 0; buy <= 1; buy++) {
            dp[index][buy][2] = 0;
        }
    }

    for (int buy = 0; buy <= 1; buy++) {
        for (int numTransactions = 0; numTransactions <= 2; numTransactions++) {
            dp[n][buy][numTransactions] = 0;
        }
    }

    for (int index = n - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int numTransactions = 1; numTransactions >= 0; numTransactions--) {
                if (buy == 1) {
                    int buyTheStock = -prices[index] + dp[index + 1][0][numTransactions];
                    int skipTheStock = dp[index + 1][1][numTransactions];

                    dp[index][buy][numTransactions] = max(buyTheStock, skipTheStock);
                }
                else {
                    int sellTheStock = prices[index] + dp[index + 1][1][numTransactions + 1];
                    int skipTheStock = dp[index + 1][0][numTransactions];

                    dp[index][buy][numTransactions] = max(sellTheStock, skipTheStock);
                }
            }
        }
    }

    return dp[0][1][0];
}

// Approach 4: Space Optimization Method
// Time Complexity: O(2 * 3 * N)
// Space Complexity: O(1)

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> next(2, vector<int>(3, 0));
    
    vector<vector<int>> curr(2, vector<int>(3, 0));

    for (int index = 0; index <= n; index++) {
        for (int buy = 0; buy <= 1; buy++) {
            next[buy][2] = 0;
        }
    }

    for (int buy = 0; buy <= 1; buy++) {
        for (int numTransactions = 0; numTransactions <= 2; numTransactions++) {
            next[buy][numTransactions] = 0;
        }
    }

    for (int index = n - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int numTransactions = 1; numTransactions >= 0; numTransactions--) {
                if (buy == 1) {
                    int buyTheStock = -prices[index] + next[0][numTransactions];
                    int skipTheStock = next[1][numTransactions];

                    curr[buy][numTransactions] = max(buyTheStock, skipTheStock);
                }
                else {
                    int sellTheStock = prices[index] + next[1][numTransactions + 1];
                    int skipTheStock = next[0][numTransactions];

                    curr[buy][numTransactions] = max(sellTheStock, skipTheStock);
                }
            }
        }

        next = curr;
    }

    return next[1][0];
}

// METHOD 2: Using (N * 4) DP

// In this method, we are assuming the transaction number for checking buying and 
// selling. For 2 transactions at max, it will be Buy Sell Buy Sell (0 1 2 3).

// Therefore, for even number, we have to buy and for odd numbers, we have to sell.
// When, we buy or sell the stock, the transaction number will be incremented and
// if we are not buying or selling the stock, the transaction number reamins same.

// Approach 1: Recursive Method
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int helper(int index, int transactionNo, int n, vector<int> &prices) {
    if (transactionNo == 4) {
        return 0; // Base case: If we've completed 4 transactions, return 0 profit.
    }
    
    if (index == n) {
        return 0; // Base case: If we've traversed all prices, return 0 profit.
    }  

    if (transactionNo % 2 == 0) {
        // Buy or skip options for even transactions
        int buyTheStock = -prices[index] + helper(index + 1, transactionNo + 1, n, prices);
        int skipTheStock = helper(index + 1, transactionNo, n, prices);

        return max(buyTheStock, skipTheStock); // Return the maximum profit.
    }
    else {
        // Sell or skip options for odd transactions
        int sellTheStock = prices[index] + helper(index + 1, transactionNo + 1, n, prices);
        int skipTheStock = helper(index + 1, transactionNo, n, prices);

        return max(sellTheStock, skipTheStock); // Return the maximum profit.
    }
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    return helper(0, 0, n, prices); // Start the recursion from index 0 with 0 transactions.
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * 4)
// Space Complexity: O(N * 4)

int helper(int index, int transactionNo, int n, vector<int> &prices, vector<vector<int>> dp) {
    if (transactionNo == 4) {
        return 0; // Base case: If we've completed 4 transactions, return 0 profit.
    }
    
    if (index == n) {
        return 0; // Base case: If we've traversed all prices, return 0 profit.
    }  

    if (dp[index][transactionNo] != -1) {
        return dp[index][transactionNo]; // If the result is memoized, return it.
    }

    if (transactionNo % 2 == 0) {
        // Buy or skip options for even transactions
        int buyTheStock = -prices[index] + helper(index + 1, transactionNo + 1, n, prices, dp);
        int skipTheStock = helper(index + 1, transactionNo, n, prices, dp);

        return dp[index][transactionNo] = max(buyTheStock, skipTheStock); // Memoize and return the maximum profit.
    }
    else {
        // Sell or skip options for odd transactions
        int sellTheStock = prices[index] + helper(index + 1, transactionNo + 1, n, prices, dp);
        int skipTheStock = helper(index + 1, transactionNo, n, prices, dp);

        return dp[index][transactionNo] = max(sellTheStock, skipTheStock); // Memoize and return the maximum profit.
    }
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(5, -1));

    return helper(0, 0, n, prices, dp); // Start the recursion from index 0 with 0 transactions.
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * 4)
// Space Complexity: O(N * 4)

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(5, 0));

    for (int index = 0; index <= n; index++) {
        dp[index][4] = 0; // Initialize the last column to 0 (4 transactions completed).
    }

    for (int transactionNo = 0; transactionNo <= 4; transactionNo++) {
        dp[n][transactionNo] = 0; // Initialize the last row to 0 (no prices left to process).
    }

    for (int index = n - 1; index >= 0; index--) {
        for (int transactionNo = 3; transactionNo >= 0; transactionNo--) {
            if (transactionNo % 2 == 0) {
                // Buy or skip options for even transactions
                int buyTheStock = -prices[index] + dp[index + 1][transactionNo + 1];
                int skipTheStock = dp[index + 1][transactionNo];

                dp[index][transactionNo] = max(buyTheStock, skipTheStock); // Update the table with the maximum profit.
            }
            else {
                // Sell or skip options for odd transactions
                int sellTheStock = prices[index] + dp[index + 1][transactionNo + 1];
                int skipTheStock = dp[index + 1][transactionNo];

                dp[index][transactionNo] = max(sellTheStock, skipTheStock); // Update the table with the maximum profit.
            }
        }
    }

    return dp[0][0]; // The top-left cell contains the maximum profit with 0 transactions completed.
}

// Approach 4: Space Optimization Approach
// Time Complexity: O(N * 4)
// Space Complexity: O(1)

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    vector<int> next(5, 0); // Array to store the maximum profits for the next transaction.
    vector<int> curr(5, 0); // Array to store the maximum profits for the current transaction.

    next[4] = 0; // Initialize the last element to 0 (4 transactions completed).

    for (int i = 0; i <= 4; i++) {
        next[i] = 0; // Initialize the last row to 0 (no prices left to process).
    }

    for (int index = n - 1; index >= 0; index--) {
        for (int transactionNo = 3; transactionNo >= 0; transactionNo--) {
            if (transactionNo % 2 == 0) {
                // Buy or skip options for even transactions
                int buyTheStock = -prices[index] + next[transactionNo + 1];
                int skipTheStock = next[transactionNo];

                curr[transactionNo] = max(buyTheStock, skipTheStock); // Update the current array.
            }
            else {
                // Sell or skip options for odd transactions
                int sellTheStock = prices[index] + next[transactionNo + 1];
                int skipTheStock = next[transactionNo];

                curr[transactionNo] = max(sellTheStock, skipTheStock); // Update the current array.
            }
        }

        next = curr; // Update the 'next' array with the results of the current transaction.
    }

    return next[0]; // The first element contains the maximum profit with 0 transactions completed.
}