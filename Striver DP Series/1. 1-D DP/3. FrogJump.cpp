#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Simple Recursive Solution
// Time Complexity: O(2^N)
// Space Complexity: O(2^N)

int frogJump(int index, vector<int> &heights) {
    if (index == 0) {
        return 0;
    }

    // Jumping one step
    int oneStepJump = frogJump(index - 1, heights) + abs(heights[index] - heights[index - 1]);

    int twoStepJump = INT_MAX;

    if (index > 1) {
        // Jumping two steps
        twoStepJump = frogJump(index - 2, heights) + abs(heights[index] - heights[index - 2]);
    }
    
    return min(oneStepJump, twoStepJump);
}

int frogJump(int n, vector<int> &heights) {
    return frogJump(n - 1, heights);
}

// Approach 2: Memoization (Top - Down)
// Time Complexity: O(N)
// Space Complexity: O(N)

int frogJump(int index, vector<int> &heights, vector<int> &dp) {
    if (index == 0) {
        return 0;
    }

    if (dp[index] != -1) {
        return dp[index];
    }

    // Jumping one step
    int oneStepJump = frogJump(index - 1, heights, dp) + abs(heights[index] - heights[index - 1]);

    int twoStepJump = INT_MAX;

    if (index > 1) {
        // Jumping two steps
        twoStepJump = frogJump(index - 2, heights, dp) + abs(heights[index] - heights[index - 2]);
    }
    
    return dp[index] = min(oneStepJump, twoStepJump);
}

int frogJump(int n, vector<int> &heights) {
    vector<int> dp(n, -1);

    return frogJump(n - 1, heights, dp);
}

// Approach 3: Iterative DP (Bottom Up)
// Time Complexity: O(N)
// Space Complexity: O(N)

int frogJump(int n, vector<int> &heights) {
    vector<int> dp(n);

    dp[0] = 0;

    for (int index = 1; index < n; index++) {
        // Jumping one step
        int oneStepJump = abs(heights[index] - heights[index-1]) + dp[index-1];

        int twoStepJump = INT_MAX;

        if (index > 1) {
            // Jumping two steps
            twoStepJump = abs(heights[index] - heights[index-2]) + dp[index-2];
        }

        dp[index] = min(oneStepJump, twoStepJump);
    }

    return dp[n-1];
}

// Approach 4: Space optimization
// Time Complexity: O(N)
// Space Complexity: O(1)

int frogJump(int n, vector<int> &heights) {
    int index = n - 1;
    
    if (index == 0) {
        return 0;
    }

    int prev = 0;
    int beforePrev = 0;

    for (int i = 1; i < n; i++) {
        // Jumping one step
        int oneStepJump = abs(heights[i] - heights[i-1]) + prev;
        
        int twoStepJump = INT_MAX;
        if (i > 1) {
            // Jumping two steps
            twoStepJump = abs(heights[i] - heights[i-2]) + beforePrev;
        }

        int curr = min(oneStepJump, twoStepJump);

        beforePrev = prev;
        prev = curr;
    }

    return prev;
}