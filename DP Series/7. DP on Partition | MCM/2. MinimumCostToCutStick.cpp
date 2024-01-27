#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to find the minimum cost to cut the stick with
// given cuts array in any order. So, we will apply Partition DP on this. We have 
// cuts array having the positions where we have to cut the stick. So, we will 
// proceed with the costing of cutting the stick, to perform this we first attach
// 0 at the front and length of stick at the back because we will calculate the
// cost of cutting with the formula stick[end + 1] - stick[start + 1] because 
// the cost adds the length of the stick before cutting which is given with this 
// formula. Then, we calculate the minimum cost to cut left part and right part
// with the help of recursion and adds all 3. Finally, we take the minimum of all
// and return the minimum cost.

// Approach 1: Recursive Approach
// Time Complexity: Exponential
// Space Complexity: O(C)

int helper(int start, int end, vector<int> &stick) {
    // Base case: If there are no cuts to make (start > end), cost is 0.
    if (start > end) {
        return 0;
    }

    // Initialize the minimum cost to a very large value.
    int minCost = INT_MAX;

    // Calculate the cost of cutting the stick from start to end.
    int cuttingCost = stick[end + 1] - stick[start - 1];

    // Iterate through all possible cut points.
    for (int index = start; index <= end; index++) {
        // Recursively calculate the cost of left and right subproblems.
        int leftPart = helper(start, index - 1, stick);

        int rightPart = helper(index + 1, end, stick);

        // Total cost is the sum of left, right, and cutting cost.
        int totalCost = leftPart + rightPart + cuttingCost;

        // Update the minimum cost.
        minCost = min(minCost, totalCost);
    }

    // Return the minimum cost for this subproblem.
    return minCost;
}

int cost(int len, int c, vector<int> &cuts) {
    // Create an array to represent the stick with cut points.
    vector<int> stick;

    stick.push_back(0);

    for (int i = 0; i < c; i++) {
        stick.push_back(cuts[i]);
    }

    stick.push_back(len);

    // Sort the cut points.
    sort(stick.begin(), stick.end());

    // Start the recursive calculation with the entire stick.
    return helper(1, c, stick);
}

// Appraoch 2: Memoization Approach
// Time Complexity: O(C * C * C)
// Space Complexity: O(C * C)

int helper(int start, int end, vector<int> &stick, vector<vector<int>> &dp) {
    if (start > end) {
        return 0;
    }

    if (dp[start][end] != -1) {
        return dp[start][end];
    }

    int minCost = INT_MAX;

    int cuttingCost = stick[end + 1] - stick[start - 1];

    for (int index = start; index <= end; index++) {
        int leftPart = helper(start, index - 1, stick, dp);

        int rightPart = helper(index + 1, end, stick, dp);

        int totalCost = leftPart + rightPart + cuttingCost;

        minCost = min(minCost, totalCost);
    }

    dp[start][end] = minCost;
    return minCost;
}

int cost(int len, int c, vector<int> &cuts) {
    vector<int> stick;
    stick.push_back(0);

    for (int i = 0; i < c; i++) {
        stick.push_back(cuts[i]);
    }

    stick.push_back(len);

    sort(stick.begin(), stick.end());

    // Create a memoization table to store computed results.
    vector<vector<int>> dp(c + 2, vector<int>(c + 2, -1));

    // Start the recursive calculation with the entire stick.
    return helper(1, c, stick, dp);
}

// Appraoch 3: Tabulation Approach
// Time Complexity: O(C * C * C)
// Space Complexity: O(C * C)

int cost(int len, int c, vector<int> &cuts) {
    vector<int> stick;

    stick.push_back(0);

    for (int i = 0; i < c; i++) {
        stick.push_back(cuts[i]);
    }

    stick.push_back(len);

    sort(stick.begin(), stick.end());

    // Create a 2D table to store computed results for subproblems.
    vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0));

    // Iterate through the stick's segments in reverse order.
    for (int start = c; start >= 1; start--) {
        for (int end = 1; end <= c; end++) {
            if (start > end) {
                continue;
            }

            int minCost = INT_MAX;

            int cuttingCost = stick[end + 1] - stick[start - 1];

            for (int index = start; index <= end; index++) {
                int leftPart = dp[start][index - 1];

                int rightPart = dp[index + 1][end];

                int totalCost = leftPart + rightPart + cuttingCost;

                minCost = min(minCost, totalCost);
            }

            dp[start][end] = minCost;
        }
    }

    // Return the minimum cost for the original problem.
    return dp[1][c];
}