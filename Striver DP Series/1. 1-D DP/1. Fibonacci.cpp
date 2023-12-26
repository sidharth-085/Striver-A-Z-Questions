#include <iostream>
#include <vector>
using namespace std;

// Basic Recursion Solution
// Time Complexity: O(2^N)
// Space Complexity: O(2^N)

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return fibonacci(n-1) + fibonacci(n-2);
}

// Memoization Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

int fibonacci(int n, vector<int> &dp) {
    if (n == 0) {
        return 0;
    }

    if (dp[n] != -1) {
        return dp[n];
    }

    if (n == 1) {
        return 1;
    }

    return dp[n] = fibonacci(n-1, dp) + fibonacci(n-2, dp);
}

int fibonacci(int n) {
    vector<int> dp(n + 1, -1);

    return fibonacci(n, dp);
}

// Tabulation DP Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

int fibonacci(int n) {
    vector<int> dp(n + 1, -1);
    
    dp[0] = 0;
    dp[1] = 1;

    for (int i=2; i<=n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}

// Space Optimized Approach
// Time Complexity: O(N)
// Space Complexity: O(1)

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } 

    int beforePrev = 0;
    int prev = 1;

    for (int i=2; i<=n; i++) {
        int curri = prev + beforePrev;

        beforePrev = prev;
        prev = curri;
    }

    return prev;
}