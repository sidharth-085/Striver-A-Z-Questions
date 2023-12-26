#include <iostream>
#include <vector>
using namespace std;

// IMP NOTE: In problem like Infinite supply of something which can be anything
// coins, weights, etc. We can optimize this solution till single 1-D array.

// This Problem is similar to 01 Knapsack problem, but in this we have infinite
// supply of goods, so it is same as combinational sum problem.

// Approach 1: Recursive Approach
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int unboundedKnapsackHelper(int index, int weight, int n, vector<int> &values, vector<int> &weights) {
    // Base case: If the weight becomes 0, we can't add any more items.
    if (weight == 0) {
        return 0;
    }

    // Base case: If we've reached the first item and it's a multiple of the weight,
    // we can add as many as (weight / weights[0]) items and return their total value.
    if (index == 0) {
        if (weight % weights[0] == 0) {
            return ((values[0]) * (weight / weights[0]));
        }

        // If not divisible, we can't add this item, so return 0.
        return 0;
    }

    // Calculate the maximum value by either including or excluding the current item.
    int include = 0;
    if (weights[index] <= weight) {
        include = values[index] + unboundedKnapsackHelper(index, weight - weights[index], n, values, weights);
    }

    int exclude = unboundedKnapsackHelper(index - 1, weight, n, values, weights);

    return max(include, exclude);
}

int unboundedKnapsack(int n, int maxWeight, vector<int> &values, vector<int> &weights) {
    return unboundedKnapsackHelper(n - 1, maxWeight, n, values, weights);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * Max Weight)
// Space Complexity: O(N * Max Weight)

int unboundedKnapsackHelper(int index, int weight, int n, vector<int> &values, vector<int> &weights, vector<vector<int>> &dp) {
    if (weight == 0) {
        return 0;
    }

    if (index == 0) {
        if (weight % weights[0] == 0) {
            return ((values[0]) * (weight / weights[0]));
        }
        return 0;
    }

    if (dp[index][weight] != -1) {
        return dp[index][weight];
    }

    int include = 0;
    if (weights[index] <= weight) {
        include = values[index] + unboundedKnapsackHelper(index, weight - weights[index], n, values, weights, dp);
    }

    int exclude = unboundedKnapsackHelper(index - 1, weight, n, values, weights, dp);

    // Store the result in the memoization table.
    return dp[index][weight] = max(include, exclude);
}

int unboundedKnapsack(int n, int maxWeight, vector<int> &values, vector<int> &weights) {
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));

    return unboundedKnapsackHelper(n - 1, maxWeight, n, values, weights, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * Max Weight)
// Space Complexity: O(N * Max Weight)

int unboundedKnapsack(int n, int maxWeight, vector<int> &values, vector<int> &weights) {
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));

    // Initialize the first row of the table for the base case.
    for (int index = 0; index < n; index++) {
        dp[index][0] = 0;
    }

    // Initialize the first column of the table for the base case.
    for (int weight = 1; weight <= maxWeight; weight++) {
        if (weight % weights[0] == 0) {
            dp[0][weight] = ((values[0]) * (weight / weights[0]));
        } else {
            dp[0][weight] = 0;
        }
    }

    // Fill in the table using dynamic programming.
    for (int index = 1; index < n; index++) {
        for (int weight = 1; weight <= maxWeight; weight++) {
            int include = 0;
            if (weights[index] <= weight) {
                include = values[index] + dp[index][weight - weights[index]];
            }

            int notInclude = dp[index - 1][weight];

            dp[index][weight] = max(include, notInclude);
        }
    }

    // Return the result from the bottom-right cell of the table.
    return dp[n - 1][maxWeight];
}

// Approach 4: Space Optimization Approach (Two 1-D arrays)
// Time Complexity: O(N * Max Weight)
// Space Complexity: O(2 * Max Weight)

int unboundedKnapsack(int n, int maxWeight, vector<int> &values, vector<int> &weights) {
    vector<int> prev(maxWeight + 1, -1);

    prev[0] = 0;

    for (int weight = 1; weight <= maxWeight; weight++) {
        if (weight % weights[0] == 0) {
            prev[weight] = ((values[0]) * (weight / weights[0]));
        } else {
            prev[weight] = 0;
        }
    }

    for (int index = 1; index < n; index++) {
        vector<int> curr(maxWeight + 1, -1);
        curr[0] = 0;

        for (int weight = 1; weight <= maxWeight; weight++) {
            int include = 0;
            if (weights[index] <= weight) {
                include = values[index] + curr[weight - weights[index]];
            }

            int notInclude = prev[weight];

            curr[weight] = max(include, notInclude);
        }

        // Update the previous array for the next iteration.
        prev = curr;
    }

    // Return the result from the last iteration of the previous array.
    return prev[maxWeight];
}

// Approach 5: Space Optimization Approach (One 1-D array)
// Time Complexity: O(N * Max Weight)
// Space Complexity: O(Max Weight)

int unboundedKnapsack(int n, int maxWeight, vector<int> &values, vector<int> &weights) {
    vector<int> prev(maxWeight + 1, -1);

    prev[0] = 0;

    for (int weight = 1; weight <= maxWeight; weight++) {
        if (weight % weights[0] == 0) {
            prev[weight] = ((values[0]) * (weight / weights[0]));
        } else {
            prev[weight] = 0;
        }
    }

    for (int index = 1; index < n; index++) {
        for (int weight = 1; weight <= maxWeight; weight++) {
            int include = 0;
            if (weights[index] <= weight) {
                include = values[index] + prev[weight - weights[index]];
            }

            int notInclude = prev[weight];

            prev[weight] = max(include, notInclude);
        }
    }

    // Return the result from the last iteration of the previous array.
    return prev[maxWeight];
}