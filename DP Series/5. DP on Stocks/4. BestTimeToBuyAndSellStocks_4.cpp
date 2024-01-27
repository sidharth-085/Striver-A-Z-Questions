#include <iostream>
#include <vector>
using namespace std;

// METHOD 1: Using (N*2*(K + 1)) DP

// Approach 1: Recursive Solution
// Time Complexity: O(2^(N + K)
// Space Complexity: O(N + K)

int helper(int index, int buy, int numTransactions, int k, int n, vector<int> &prices) {
    if (numTransactions == k) {
        return 0;
    }

    if (index == n) {
        return 0;
    }

    if (buy == 1) {
        int buyTheStock = -prices[index] + helper(index + 1, 0, numTransactions, k, n, prices);
        int skipTheStock = helper(index + 1, 1, numTransactions, k, n, prices);

        return max(buyTheStock, skipTheStock);
    }
    else {
        int sellTheStock = prices[index] + helper(index + 1, 1, numTransactions + 1, k, n, prices);
        int skipTheStock = helper(index + 1, 0, numTransactions, k, n, prices);

        return max(sellTheStock, skipTheStock);
    }

    return 0;
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    return helper(0, 1, 0, k, n, prices);
}

// Approach 2: Memoization Solution
// Time Complexity: O(2 * (K+1) * N)
// Space Complexity: O(2 * (K+1) * N)

int helper(int index, int buy, int numTransactions, int k, int n, vector<int> &prices, vector<vector<vector<int>>> &dp) {
    if (numTransactions == k) {
        return 0;
    }

    if (index == n) {
        return 0;
    }

    if (dp[index][buy][numTransactions] != -1) {
        return dp[index][buy][numTransactions];
    }

    if (buy == 1) {
        int buyTheStock = -prices[index] + helper(index + 1, 0, numTransactions, k, n, prices, dp);
        int skipTheStock = helper(index + 1, 1, numTransactions, k, n, prices, dp);

        return dp[index][buy][numTransactions] = max(buyTheStock, skipTheStock);
    }
    else {
        int sellTheStock = prices[index] + helper(index + 1, 1, numTransactions + 1, k, n, prices, dp);
        int skipTheStock = helper(index + 1, 0, numTransactions, k, n, prices, dp);

        return dp[index][buy][numTransactions] = max(sellTheStock, skipTheStock);
    }

    return 0;
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));

    return helper(0, 1, 0, k, n, prices, dp);
}

// Approach 3: Tabulation Method
// Time Complexity: O(2 * (K+1) * N)
// Space Complexity: O(2 * (K+1) * N)

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, -1)));

    for (int index = 0; index <= n; index++) {
        for (int buy = 0; buy <= 1; buy++) {
            dp[index][buy][k] = 0;
        }
    }

    for (int buy = 0; buy <= 1; buy++) {
        for (int numTransactions = 0; numTransactions <= k; numTransactions++) {
            dp[n][buy][numTransactions] = 0;
        }
    }

    for (int index = n - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int numTransactions = k - 1; numTransactions >= 0; numTransactions--) {
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
// Time Complexity: O(2 * (K+1) * N)
// Space Complexity: O(1)

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> next(2, vector<int>(k + 1, 0));
    
    vector<vector<int>> curr(2, vector<int>(k + 1, 0));

    for (int index = 0; index <= n; index++) {
        for (int buy = 0; buy <= 1; buy++) {
            next[buy][k] = 0;
        }
    }

    for (int buy = 0; buy <= 1; buy++) {
        for (int numTransactions = 0; numTransactions <= k; numTransactions++) {
            next[buy][numTransactions] = 0;
        }
    }

    for (int index = n - 1; index >= 0; index--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int numTransactions = k - 1; numTransactions >= 0; numTransactions--) {
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

// METHOD 2: Using (N * (2*K + 1)) DP
// Same as previous question's method 2, the transactionNo will be equal to 
// twice of number of transactions i.e buy and sell both

// Approach 1: Recursive Approach
// Time Complexity: O(2^(N + 2*K))
// Space Complexity: O(N + (2*K))

int helper(int index, int transactionNo, int n, int k, vector<int> &prices) {
    if (transactionNo == 2*k) {
        return 0; // Base case: All transactions are complete.
    }
    
    if (index == n) {
        return 0; // Base case: All stock prices are processed.
    }  

    if (transactionNo % 2 == 0) {
        // Buy or skip decisions for even-numbered transactions.
        int buyTheStock = -prices[index] + helper(index + 1, transactionNo + 1, n, k, prices);
        int skipTheStock = helper(index + 1, transactionNo, n, k, prices);

        return max(buyTheStock, skipTheStock); // Take the maximum of buying or skipping.
    }
    else {
        // Sell or skip decisions for odd-numbered transactions.
        int sellTheStock = prices[index] + helper(index + 1, transactionNo + 1, n, k, prices);
        int skipTheStock = helper(index + 1, transactionNo, n, k, prices);

        return max(sellTheStock, skipTheStock); // Take the maximum of selling or skipping.
    }
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    return helper(0, 0, n, k, prices);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * 2 * K)
// Space Complexity: O(N * 2 * K)

int helper(int index, int transactionNo, int n, int k, vector<int> &prices, vector<vector<int>> dp) {
    if (transactionNo == 2*k) {
        return 0;
    }
    
    if (index == n) {
        return 0;
    }  

    if (dp[index][transactionNo] != -1) {
        return dp[index][transactionNo]; // If the result is already computed, return it.
    }

    if (transactionNo % 2 == 0) {
        // Buy or skip decisions for even-numbered transactions.
        int buyTheStock = -prices[index] + helper(index + 1, transactionNo + 1, n, k, prices, dp);
        int skipTheStock = helper(index + 1, transactionNo, n, k, prices, dp);

        return dp[index][transactionNo] = max(buyTheStock, skipTheStock);
    }
    else {
        // Sell or skip decisions for odd-numbered transactions.
        int sellTheStock = prices[index] + helper(index + 1, transactionNo + 1, n, k, prices, dp);
        int skipTheStock = helper(index + 1, transactionNo, n, k, prices, dp);

        return dp[index][transactionNo] = max(sellTheStock, skipTheStock);
    }
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2*k + 1, -1));

    return helper(0, 0, n, k, prices, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * 2 * K)
// Space Complexity: O(N * 2 * K)

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    vector<vector<int>> dp(n + 1, vector<int>(2*k + 1, 0));

    // Initialize base cases: no transactions can be made at the end.
    for (int index = 0; index <= n; index++) {
        dp[index][2*k] = 0;
    }

    for (int i = 0; i <= 2*k; i++) {
        dp[n][i] = 0;
    }

    // Fill the DP table by considering buy, sell, or skip decisions.
    for (int index = n - 1; index >= 0; index--) {
        for (int transactionNo = 2*k - 1; transactionNo >= 0; transactionNo--) {
            if (transactionNo % 2 == 0) {
                // Buy or skip decisions for even-numbered transactions.
                int buyTheStock = -prices[index] + dp[index + 1][transactionNo + 1];
                int skipTheStock = dp[index + 1][transactionNo];

                dp[index][transactionNo] = max(buyTheStock, skipTheStock);
            }
            else {
                // Sell or skip decisions for odd-numbered transactions.
                int sellTheStock = prices[index] + dp[index + 1][transactionNo + 1];
                int skipTheStock = dp[index + 1][transactionNo];

                dp[index][transactionNo] = max(sellTheStock, skipTheStock);
            }
        }
    }

    return dp[0][0];
}

// Approach 4: Space Optimization Approach
// Time Complexity: O(N * 2 * K)
// Space Complexity: O(2 * K)

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

    vector<int> next(2*k + 1, 0);
    vector<int> curr(2*k + 1, 0);

    next[2*k] = 0;

    for (int transactionNo = 0; transactionNo <= 2*k; transactionNo++) {
        next[transactionNo] = 0;
    }

    // Fill the DP table by considering buy, sell, or skip decisions.
    for (int index = n - 1; index >= 0; index--) {
        for (int transactionNo = 2*k - 1; transactionNo >= 0; transactionNo--) {
            if (transactionNo % 2 == 0) {
                // Buy or skip decisions for even-numbered transactions.
                int buyTheStock = -prices[index] + next[transactionNo + 1];
                int skipTheStock = next[transactionNo];

                curr[transactionNo] = max(buyTheStock, skipTheStock);
            }
            else {
                // Sell or skip decisions for odd-numbered transactions.
                int sellTheStock = prices[index] + next[transactionNo + 1];
                int skipTheStock = next[transactionNo];

                curr[transactionNo] = max(sellTheStock, skipTheStock);
            }
        }

        next = curr;
    }

    return next[0];
}