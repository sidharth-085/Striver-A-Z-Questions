#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Using Recursion
// Time Complexity: O(2^N)
// Space Complexity: O(2^N)

int climbStairs(int n) {
    // Base case: If there are 0 or 1 steps, there's only one way to climb (no steps or one step).
    if (n <= 1) {
        return 1;
    }

    // Recursive calls to climbStairs for taking one step or two steps.
    int oneStep = climbStairs(n-1);
    int twoStep = climbStairs(n-2);

    // Total ways to reach n steps = ways by taking one step + ways by taking two steps.
    return oneStep + twoStep;
}

// Approach 2: Memoization (Top - Down Approach)
// Time Complexity: O(N)
// Space Complexity: O(N)

int climbStairs(int n, vector<int> &dp) {
    // Base case: If there are 0 or 1 steps, there's only one way to climb (no steps or one step).
    if (n <= 1) {
        return 1;
    }

    // If the result is already computed, return it.
    if (dp[n] != -1) {
        return dp[n];
    }

    // Recursive calls to climbStairs for taking one step or two steps.
    int oneStep = climbStairs(n-1, dp);
    int twoStep = climbStairs(n-2, dp);

    // Memoize the result and return.
    return dp[n] = oneStep + twoStep;
}

int climbStairs(int n) {
    vector<int> dp(n + 1, -1);

    return climbStairs(n, dp);
}

// Approach 3: Using DP (Bottom Up Approach)
// Time Complexity: O(N)
// Space Complexity: O(N)

int climbStairs(int n) {
    vector<int> dp(n + 1);
    dp[0] = 1; // Base case: There's one way to climb 0 steps.
    dp[1] = 1; // Base case: There's one way to climb 1 step.

    // Compute ways to climb for each step from 2 to n using previous steps' results.
    for (int i=2; i<=n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}

// Approach 4: Space Optimized Approach
// Time Complexity: O(N)
// Space Complexity: O(1)

int climbStairs(int n) {
    // Base case: If there are 0 or 1 steps, there's only one way to climb 
    // (no steps or one step).
    
    if (n <= 1) {
        return 1;
    }

    int prev = 1; // Initially, there's one way to climb 1 step.
    int beforePrev = 1; // Initially, there's one way to climb 0 steps.

    // Compute ways to climb for each step from 2 to n using two variables.
    for (int i=2; i<=n; i++) {
        int curr = prev + beforePrev;

        beforePrev = prev;
        prev = curr;
    }

    return prev; // The result after iterating through all steps.
}