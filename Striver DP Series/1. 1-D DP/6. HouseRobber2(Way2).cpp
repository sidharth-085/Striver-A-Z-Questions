#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute force Recursive Solution
// Time Complexity: O(2^N)
// Space Complexity: O(2^N)

int robHelper(vector<int> &nums, int left, int right) {
    if (right == left) {
        return nums[left];
    }

    if (right < left) {
        return 0;
    }

    int robLastHouse = nums[right] + robHelper(nums, left, right - 2);

    int skipLastHouse = robHelper(nums, left, right - 1);

    return max(robLastHouse, skipLastHouse);
}

int rob(vector<int> &nums) {
    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    int skipLastHouse = robHelper(nums, 0, n-2);

    int skipFirstHouse = robHelper(nums, 1, n-1);

    return max(skipFirstHouse, skipLastHouse);
}

// Approach 2: Memoization Solution
// Time Complexity: O(N)
// Space Complexity: O(N)

int robHelper(vector<int> &nums, int left, int right, vector<int> &dp) {
    if (right == left) {
        return nums[left];
    }

    if (right < left) {
        return 0;
    }
    
    if (dp[right] != -1) {
        return dp[right];
    }

    int robLastHouse = nums[right] + robHelper(nums, left, right - 2);

    int skipLastHouse = robHelper(nums, left, right - 1);

    return dp[right] = max(robLastHouse, skipLastHouse);
}

int rob(vector<int> &nums) {
    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    vector<int> dp(n, -1);

    int skipLastHouse = robHelper(nums, 0, n-2);

    int skipFirstHouse = robHelper(nums, 1, n-1);

    return max(skipFirstHouse, skipLastHouse);
}

// Approach 3: Iterative DP (Bottom Up DP)
// Time Complexity: O(N)
// Space Complexity: O(N)

int robHelper(vector<int> &nums, int left, int right) {
    int n = right - left + 1;

    vector<int> dp(n);

    dp[0] = nums[left];

    for (int i=1; i<n; i++) {
        int robLastHouse = nums[left + i];

        if (i > 1) {
            robLastHouse = nums[left + i] + dp[i-2];
        }

        int skipLastHouse = dp[i-1];

        dp[i] = max(robLastHouse, skipLastHouse);
    }

    return dp[n];
}

int rob(vector<int> &nums) {
    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    int skipLastHouse = robHelper(nums, 0, n-2);

    int skipFirstHouse = robHelper(nums, 1, n-1);

    return max(skipFirstHouse, skipLastHouse);
}