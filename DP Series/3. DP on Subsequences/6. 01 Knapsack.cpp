#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Brute Force Solution
// Time Complexity: O(2 ^ N)
// Space Complexity: O(N)

int knapsackHelper(int index, int maxWeight, int n, vector<int> &weight, vector<int> &value) {
    // Base case: If the knapsack has no capacity, return 0.
    if (maxWeight == 0) {
        return 0;
    }

    // Base case: If we're considering the first item (index 0),
    // check if it can be included in the knapsack.
    if (index == 0) {
        if (weight[0] <= maxWeight) {
            return value[0];
        }
        return 0;
    }

    int takeValue = 0;

    // Calculate the value if we include the current item.
    if (weight[index] <= maxWeight) {
        takeValue = value[index] + knapsackHelper(index - 1, maxWeight - weight[index], n, weight, value);
    }

    // Calculate the value if we exclude the current item.
    int notTakeValue = knapsackHelper(index - 1, maxWeight, n, weight, value);

    // Return the maximum of including and excluding the current item.
    return max(takeValue, notTakeValue);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)  {
    return knapsackHelper(n - 1, maxWeight, n, weight, value);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int knapsackHelper(int index, int maxWeight, int n, vector<int> &weight, vector<int> &value, vector<vector<int>> &dp) {
    // Base case: If the knapsack has no capacity, return 0.
    if (maxWeight == 0) {
        return 0;
    }

    // Base case: If we're considering the first item (index 0),
    // check if it can be included in the knapsack.
    if (index == 0) {
        if (weight[0] <= maxWeight) {
            return value[0];
        }
        return 0;
    }

    // If the value is already computed, return it from the memoization table.
    if (dp[index][maxWeight] != -1) {
        return dp[index][maxWeight];
    }

    int takeValue = 0;

    // Calculate the value if we include the current item.
    if (weight[index] <= maxWeight) {
        takeValue = value[index] + knapsackHelper(index - 1, maxWeight - weight[index], n, weight, value, dp);
    }

    // Calculate the value if we exclude the current item.
    int notTakeValue = knapsackHelper(index - 1, maxWeight, n, weight, value, dp);

    // Store the result in the memoization table and return it.
    return dp[index][maxWeight] = max(takeValue, notTakeValue);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)  {
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));

    return knapsackHelper(n - 1, maxWeight, n, weight, value, dp);
}

// Approach 3: Tabulation Method
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int knapsack(vector<int> weights, vector<int> value, int n, int maxWeight)  {
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));

    // Initialize the first row (when considering only the first item).
    for (int weight = 1; weight <= maxWeight; weight++) {
        if (weights[0] <= weight) {
            dp[0][weight] = value[0];
        }
    }

    // Fill in the dynamic programming table.
    for (int index = 1; index < n; index++) {
        for (int weight = 1; weight <= maxWeight; weight++) {
            int takeValue = 0;
            if (weights[index] <= weight) {
                takeValue = value[index] + dp[index - 1][weight - weights[index]];
            }

            int notTakeValue = dp[index - 1][weight];

            dp[index][weight] = max(takeValue, notTakeValue);
        }
    }

    // Return the maximum value achieved in the knapsack.
    return dp[n - 1][maxWeight];
}

// Approach 4: Space Optimization Method
// Time Complexity: O(N * M)
// Space Complexity: O(2*M)

int knapsack(vector<int> weights, vector<int> value, int n, int maxWeight)  {
    vector<int> prev(maxWeight + 1, 0);

    prev[0] = 0;

    // Initialize the first row (when considering only the first item).
    for (int weight = 1; weight <= maxWeight; weight++) {
        if (weights[0] <= weight) {
            prev[weight] = value[0];
        }
    }

    // Fill in the dynamic programming table using two rows.
    for (int index = 1; index < n; index++) {
        vector<int> curr(maxWeight + 1, 0);
        curr[0] = 0;

        for (int weight = 1; weight <= maxWeight; weight++) {
            int takeValue = 0;
            if (weights[index] <= weight) {
                takeValue = value[index] + prev[weight - weights[index]];
            }

            int notTakeValue = prev[weight];

            curr[weight] = max(takeValue, notTakeValue);
        }

        prev = curr; // Update the previous row.
    }

    // Return the maximum value achieved in the knapsack.
    return prev[maxWeight];
}

// Approach 5: Lowest Space Optimization Method (Single Array DP)
// Time Complexity: O(N * M)
// Space Complexity: O(M)

int knapsack(vector<int> weights, vector<int> value, int n, int maxWeight)  {
    vector<int> prev(maxWeight + 1, 0);

    prev[0] = 0;

    // Initialize the first row (when considering only the first item).
    for (int weight = 1; weight <= maxWeight; weight++) {
        if (weights[0] <= weight) {
            prev[weight] = value[0];
        }
    }

    // Fill in the dynamic programming table using a single row.
    for (int index = 1; index < n; index++) {
        for (int weight = maxWeight; weight >= 1; weight--) {
            int takeValue = 0;
            if (weights[index] <= weight) {
                takeValue = value[index] + prev[weight - weights[index]];
            }

            int notTakeValue = prev[weight];

            prev[weight] = max(takeValue, notTakeValue);
        }
    }

    // Return the maximum value achieved in the knapsack.
    return prev[maxWeight];
}